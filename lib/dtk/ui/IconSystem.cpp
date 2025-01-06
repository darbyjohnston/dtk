// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/IconSystem.h>

#include <dtk/core/ImageIO.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>
#include <dtk/core/LRUCache.h>

#include <lunasvg/lunasvg.h>

namespace
{
#include <Icons/ArrowDown.h>
#include <Icons/ArrowLeft.h>
#include <Icons/ArrowRight.h>
#include <Icons/ArrowUp.h>
#include <Icons/Audio.h>
#include <Icons/BellowsClosed.h>
#include <Icons/BellowsOpen.h>
#include <Icons/Clear.h>
#include <Icons/Close.h>
#include <Icons/Copy.h>
#include <Icons/Decrement.h>
#include <Icons/Directory.h>
#include <Icons/DirectoryBack.h>
#include <Icons/DirectoryForward.h>
#include <Icons/DirectoryUp.h>
#include <Icons/Edit.h>
#include <Icons/Empty.h>
#include <Icons/File.h>
#include <Icons/FileBrowser.h>
#include <Icons/FileClose.h>
#include <Icons/FileCloseAll.h>
#include <Icons/FileOpen.h>
#include <Icons/FrameEnd.h>
#include <Icons/FrameInOut.h>
#include <Icons/FrameNext.h>
#include <Icons/FramePrev.h>
#include <Icons/FrameStart.h>
#include <Icons/Increment.h>
#include <Icons/MenuArrow.h>
#include <Icons/MenuChecked.h>
#include <Icons/Mute.h>
#include <Icons/Next.h>
#include <Icons/PanelBottom.h>
#include <Icons/PanelLeft.h>
#include <Icons/PanelRight.h>
#include <Icons/PanelTop.h>
#include <Icons/PlaybackForward.h>
#include <Icons/PlaybackReverse.h>
#include <Icons/PlaybackStop.h>
#include <Icons/Prev.h>
#include <Icons/Reload.h>
#include <Icons/Reset.h>
#include <Icons/ReverseSort.h>
#include <Icons/Search.h>
#include <Icons/Settings.h>
#include <Icons/SubMenuArrow.h>
#include <Icons/TimeEnd.h>
#include <Icons/TimeStart.h>
#include <Icons/ViewZoomIn.h>
#include <Icons/ViewZoomOut.h>
#include <Icons/ViewZoomReset.h>
#include <Icons/ViewFrame.h>
#include <Icons/Volume.h>
#include <Icons/WindowFullScreen.h>
}

#include <atomic>
#include <condition_variable>
#include <list>
#include <mutex>
#include <thread>

namespace dtk
{
    namespace
    {
        const size_t requestCount = 1;
    }

    struct IconSystem::Private
    {
        std::weak_ptr<Context> context;

        std::map<std::string, std::vector<uint8_t> > iconData;

        uint64_t id = 0;

        struct Request
        {
            uint64_t id = 0;
            std::string name;
            float displayScale = 1.F;
            std::promise<std::shared_ptr<Image> > promise;
        };
        const size_t requestTimeout = 5;

        typedef std::pair<std::string, float> CacheKey;

        struct Mutex
        {
            std::list<std::shared_ptr<Request> > requests;
            LRUCache<CacheKey, std::shared_ptr<Image> > cache;
            bool stopped = false;
            std::mutex mutex;
        };
        Mutex mutex;

        struct Thread
        {
            std::condition_variable cv;
            std::thread thread;
            std::atomic<bool> running;
        };
        Thread thread;

        void _cancelRequests();
    };

    void IconSystem::_init(const std::shared_ptr<Context>& context)
    {
        DTK_P();
        p.context = context;

        p.iconData["Audio"] = Audio_svg;
        p.iconData["ArrowDown"] = ArrowDown_svg;
        p.iconData["ArrowLeft"] = ArrowLeft_svg;
        p.iconData["ArrowRight"] = ArrowRight_svg;
        p.iconData["ArrowUp"] = ArrowUp_svg;
        p.iconData["BellowsClosed"] = BellowsClosed_svg;
        p.iconData["BellowsOpen"] = BellowsOpen_svg;
        p.iconData["Clear"] = Clear_svg;
        p.iconData["Close"] = Close_svg;
        p.iconData["Copy"] = Copy_svg;
        p.iconData["Decrement"] = Decrement_svg;
        p.iconData["Directory"] = Directory_svg;
        p.iconData["DirectoryBack"] = DirectoryBack_svg;
        p.iconData["DirectoryForward"] = DirectoryForward_svg;
        p.iconData["DirectoryUp"] = DirectoryUp_svg;
        p.iconData["Edit"] = Edit_svg;
        p.iconData["Empty"] = Empty_svg;
        p.iconData["File"] = File_svg;
        p.iconData["FileBrowser"] = FileBrowser_svg;
        p.iconData["FileClose"] = FileClose_svg;
        p.iconData["FileCloseAll"] = FileCloseAll_svg;
        p.iconData["FileOpen"] = FileOpen_svg;
        p.iconData["FrameEnd"] = FrameEnd_svg;
        p.iconData["FrameInOut"] = FrameInOut_svg;
        p.iconData["FrameNext"] = FrameNext_svg;
        p.iconData["FramePrev"] = FramePrev_svg;
        p.iconData["FrameStart"] = FrameStart_svg;
        p.iconData["Increment"] = Increment_svg;
        p.iconData["MenuArrow"] = MenuArrow_svg;
        p.iconData["MenuChecked"] = MenuChecked_svg;
        p.iconData["Mute"] = Mute_svg;
        p.iconData["Next"] = Next_svg;
        p.iconData["PanelBottom"] = PanelBottom_svg;
        p.iconData["PanelLeft"] = PanelLeft_svg;
        p.iconData["PanelRight"] = PanelRight_svg;
        p.iconData["PanelTop"] = PanelTop_svg;
        p.iconData["PlaybackForward"] = PlaybackForward_svg;
        p.iconData["PlaybackReverse"] = PlaybackReverse_svg;
        p.iconData["PlaybackStop"] = PlaybackStop_svg;
        p.iconData["Prev"] = Prev_svg;
        p.iconData["Reset"] = Reset_svg;
        p.iconData["ReverseSort"] = ReverseSort_svg;
        p.iconData["Reload"] = Reload_svg;
        p.iconData["Search"] = Search_svg;
        p.iconData["Settings"] = Settings_svg;
        p.iconData["SubMenuArrow"] = SubMenuArrow_svg;
        p.iconData["TimeEnd"] = TimeEnd_svg;
        p.iconData["TimeStart"] = TimeStart_svg;
        p.iconData["ViewZoomIn"] = ViewZoomIn_svg;
        p.iconData["ViewZoomOut"] = ViewZoomOut_svg;
        p.iconData["ViewZoomReset"] = ViewZoomReset_svg;
        p.iconData["ViewFrame"] = ViewFrame_svg;
        p.iconData["Volume"] = Volume_svg;
        p.iconData["WindowFullScreen"] = WindowFullScreen_svg;

        p.mutex.cache.setMax(1000);
        p.thread.running = true;
        p.thread.thread = std::thread(
            [this]
            {
                DTK_P();
                while (p.thread.running)
                {
                    std::list<std::shared_ptr<Private::Request> > requests;
                    {
                        std::unique_lock<std::mutex> lock(p.mutex.mutex);
                        if (p.thread.cv.wait_for(
                            lock,
                            std::chrono::milliseconds(p.requestTimeout),
                            [this]
                            {
                                return !_p->mutex.requests.empty();
                            }))
                        {
                            for (
                                size_t i = 0;
                                i < requestCount && !p.mutex.requests.empty();
                                ++i)
                            {
                                requests.push_back(p.mutex.requests.front());
                                p.mutex.requests.pop_front();
                            }
                        }
                    }

                    for (const auto& request : requests)
                    {
                        //std::cout << "icon request: " << request->name << " " << request->displayScale << std::endl;
                        std::shared_ptr<Image> image;
                        bool cached = false;
                        {
                            std::unique_lock<std::mutex> lock(p.mutex.mutex);
                            cached = p.mutex.cache.get(
                                std::make_pair(request->name, request->displayScale),
                                image);
                        }
                        if (!cached)
                        {
                            const auto j = p.iconData.find(request->name);
                            if (j != p.iconData.end())
                            {
                                if (auto context = p.context.lock())
                                {
                                    const std::string s(j->second.begin(), j->second.end());
                                    if (auto doc = lunasvg::Document::loadFromData(s))
                                    {
                                        const int w = doc->width() * request->displayScale;
                                        const int h = doc->height() * request->displayScale;
                                        auto bitmap = doc->renderToBitmap(w, h, 0x00000000);
                                        if (!bitmap.isNull())
                                        {
                                            image = Image::create(w, h, ImageType::RGBA_U8);
                                            for (int y = 0; y < h; ++y)
                                            {
                                                uint8_t* imageP = image->getData() + y * w * 4;
                                                const uint8_t* bitmapP = bitmap.data() + (h - 1 - y) * w * 4;
                                                for (int x = 0; x < w; ++x, imageP += 4, bitmapP += 4)
                                                {
                                                    imageP[0] = bitmapP[0];
                                                    imageP[1] = bitmapP[1];
                                                    imageP[2] = bitmapP[2];
                                                    imageP[3] = bitmapP[3];
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        request->promise.set_value(image);
                        {
                            std::unique_lock<std::mutex> lock(p.mutex.mutex);
                            p.mutex.cache.add(
                                std::make_pair(request->name, request->displayScale),
                                image);
                        }
                    }
                }
                {
                    std::unique_lock<std::mutex> lock(p.mutex.mutex);
                    p.mutex.stopped = true;
                }
                p._cancelRequests();
            });
    }

    IconSystem::IconSystem(const std::shared_ptr<Context>& context) :
        ISystem(context, "dtk::IconSystem"),
        _p(new Private)
    {}

    IconSystem::~IconSystem()
    {
        DTK_P();
        p.thread.running = false;
        if (p.thread.thread.joinable())
        {
            p.thread.thread.join();
        }
    }

    std::shared_ptr<IconSystem> IconSystem::create(
        const std::shared_ptr<Context>& context)
    {
        auto out = std::shared_ptr<IconSystem>(new IconSystem(context));
        out->_init(context);
        return out;
    }

    std::vector<std::string> IconSystem::getNames() const
    {
        DTK_P();
        std::vector<std::string> out;
        for (const auto& i : p.iconData)
        {
            out.push_back(i.first);
        }
        return out;
    }
    
    void IconSystem::add(const std::string& name, const std::vector<uint8_t>& svg)
    {
        DTK_P();
        p.iconData[name] = svg;
    }

    std::shared_ptr<Image> IconSystem::get(
        const std::string& name,
        float displayScale)
    {
        return request(name, displayScale).future.get();
    }

    IconRequest IconSystem::request(
        const std::string& name,
        float displayScale)
    {
        DTK_P();
        IconRequest out;
        out.id = p.id++;
        auto request = std::make_shared<Private::Request>();
        request->id = out.id;
        request->name = name;
        request->displayScale = displayScale;
        out.future = request->promise.get_future();
        std::shared_ptr<Image> image;
        bool cached = false;
        {
            std::unique_lock<std::mutex> lock(p.mutex.mutex);
            cached = p.mutex.cache.get(
                std::make_pair(name, displayScale),
                image);
        }
        if (cached)
        {
            request->promise.set_value(image);
        }
        else
        {
            bool valid = false;
            {
                std::unique_lock<std::mutex> lock(p.mutex.mutex);
                if (!p.mutex.stopped)
                {
                    valid = true;
                    p.mutex.requests.push_back(request);
                }
            }
            if (valid)
            {
                p.thread.cv.notify_one();
            }
            else
            {
                request->promise.set_value(nullptr);
            }
        }
        return out;
    }

    void IconSystem::cancelRequests(const std::vector<uint64_t>& ids)
    {
        DTK_P();
        std::list<std::shared_ptr<Private::Request> > requests;
        {
            std::unique_lock<std::mutex> lock(p.mutex.mutex);
            auto i = p.mutex.requests.begin();
            while (i != p.mutex.requests.end())
            {
                const auto j = std::find(ids.begin(), ids.end(), (*i)->id);
                if (j != ids.end())
                {
                    i = p.mutex.requests.erase(i);
                }
                else
                {
                    ++i;
                }
            }
        }
    }

    void IconSystem::Private::_cancelRequests()
    {
        std::list<std::shared_ptr<Private::Request> > requests;
        {
            std::unique_lock<std::mutex> lock(mutex.mutex);
            requests = std::move(mutex.requests);
        }
        for (auto& request : requests)
        {
            request->promise.set_value(nullptr);
        }
    }
}
