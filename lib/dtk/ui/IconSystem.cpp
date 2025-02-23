// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/IconSystem.h>

#include <dtk/core/ImageIO.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>
#include <dtk/core/LRUCache.h>

#include <dtk/resource/ArrowDown.h>
#include <dtk/resource/ArrowLeft.h>
#include <dtk/resource/ArrowRight.h>
#include <dtk/resource/ArrowUp.h>
#include <dtk/resource/Audio.h>
#include <dtk/resource/BellowsClosed.h>
#include <dtk/resource/BellowsOpen.h>
#include <dtk/resource/Clear.h>
#include <dtk/resource/Close.h>
#include <dtk/resource/Copy.h>
#include <dtk/resource/Decrement.h>
#include <dtk/resource/Directory.h>
#include <dtk/resource/DirectoryBack.h>
#include <dtk/resource/DirectoryForward.h>
#include <dtk/resource/DirectoryUp.h>
#include <dtk/resource/Edit.h>
#include <dtk/resource/Empty.h>
#include <dtk/resource/File.h>
#include <dtk/resource/FileBrowser.h>
#include <dtk/resource/FileClose.h>
#include <dtk/resource/FileCloseAll.h>
#include <dtk/resource/FileOpen.h>
#include <dtk/resource/FrameEnd.h>
#include <dtk/resource/FrameInOut.h>
#include <dtk/resource/FrameNext.h>
#include <dtk/resource/FramePrev.h>
#include <dtk/resource/FrameStart.h>
#include <dtk/resource/Increment.h>
#include <dtk/resource/MenuArrow.h>
#include <dtk/resource/MenuChecked.h>
#include <dtk/resource/Mute.h>
#include <dtk/resource/Next.h>
#include <dtk/resource/PanelBottom.h>
#include <dtk/resource/PanelLeft.h>
#include <dtk/resource/PanelRight.h>
#include <dtk/resource/PanelTop.h>
#include <dtk/resource/PlaybackForward.h>
#include <dtk/resource/PlaybackReverse.h>
#include <dtk/resource/PlaybackStop.h>
#include <dtk/resource/Prev.h>
#include <dtk/resource/Reload.h>
#include <dtk/resource/Reset.h>
#include <dtk/resource/ReverseSort.h>
#include <dtk/resource/Search.h>
#include <dtk/resource/Settings.h>
#include <dtk/resource/SubMenuArrow.h>
#include <dtk/resource/TimeEnd.h>
#include <dtk/resource/TimeStart.h>
#include <dtk/resource/ViewFrame.h>
#include <dtk/resource/ViewZoomIn.h>
#include <dtk/resource/ViewZoomOut.h>
#include <dtk/resource/ViewZoomReset.h>
#include <dtk/resource/Volume.h>
#include <dtk/resource/WindowFullScreen.h>

#include <lunasvg/lunasvg.h>

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

        p.iconData["ArrowDown"] = getArrowDown();
        p.iconData["ArrowLeft"] = getArrowLeft();
        p.iconData["ArrowRight"] = getArrowRight();
        p.iconData["ArrowUp"] = getArrowUp();
        p.iconData["Audio"] = getAudio();
        p.iconData["BellowsClosed"] = getBellowsClosed();
        p.iconData["BellowsOpen"] = getBellowsOpen();
        p.iconData["Clear"] = getClear();
        p.iconData["Close"] = getClose();
        p.iconData["Copy"] = getCopy();
        p.iconData["Decrement"] = getDecrement();
        p.iconData["Directory"] = getDirectory();
        p.iconData["DirectoryBack"] = getDirectoryBack();
        p.iconData["DirectoryForward"] = getDirectoryForward();
        p.iconData["DirectoryUp"] = getDirectoryUp();
        p.iconData["Edit"] = getEdit();
        p.iconData["Empty"] = getEmpty();
        p.iconData["File"] = getFile();
        p.iconData["FileBrowser"] = getFileBrowser();
        p.iconData["FileClose"] = getFileClose();
        p.iconData["FileCloseAll"] = getFileCloseAll();
        p.iconData["FileOpen"] = getFileOpen();
        p.iconData["FrameEnd"] = getFrameEnd();
        p.iconData["FrameInOut"] = getFrameInOut();
        p.iconData["FrameNext"] = getFrameNext();
        p.iconData["FramePrev"] = getFramePrev();
        p.iconData["FrameStart"] = getFrameStart();
        p.iconData["Increment"] = getIncrement();
        p.iconData["MenuArrow"] = getMenuArrow();
        p.iconData["MenuChecked"] = getMenuChecked();
        p.iconData["Mute"] = getMute();
        p.iconData["Next"] = getNext();
        p.iconData["PanelBottom"] = getPanelBottom();
        p.iconData["PanelLeft"] = getPanelLeft();
        p.iconData["PanelRight"] = getPanelRight();
        p.iconData["PanelTop"] = getPanelTop();
        p.iconData["PlaybackForward"] = getPlaybackForward();
        p.iconData["PlaybackReverse"] = getPlaybackReverse();
        p.iconData["PlaybackStop"] = getPlaybackStop();
        p.iconData["Prev"] = getPrev();
        p.iconData["Reload"] = getReload();
        p.iconData["Reset"] = getReset();
        p.iconData["ReverseSort"] = getReverseSort();
        p.iconData["Search"] = getSearch();
        p.iconData["Settings"] = getSettings();
        p.iconData["SubMenuArrow"] = getSubMenuArrow();
        p.iconData["TimeEnd"] = getTimeEnd();
        p.iconData["TimeStart"] = getTimeStart();
        p.iconData["ViewFrame"] = getViewFrame();
        p.iconData["ViewZoomIn"] = getViewZoomIn();
        p.iconData["ViewZoomOut"] = getViewZoomOut();
        p.iconData["ViewZoomReset"] = getViewZoomReset();
        p.iconData["Volume"] = getVolume();
        p.iconData["WindowFullScreen"] = getWindowFullScreen();

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
                            std::vector<uint8_t> resource;
                            if (resource.empty())
                            {
                                const auto i = p.iconData.find(request->name);
                                if (i != p.iconData.end())
                                {
                                    resource = i->second;
                                }
                            }
                            if (!resource.empty())
                            {
                                if (auto context = p.context.lock())
                                {
                                    const std::string s(resource.begin(), resource.end());
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
