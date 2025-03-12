// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/IconSystem.h>

#include <dtk/core/ImageIO.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>
#include <dtk/core/LRUCache.h>

#include <lunasvg/lunasvg.h>

#include <atomic>
#include <condition_variable>
#include <list>
#include <mutex>
#include <thread>

namespace dtk_resource
{
    extern std::vector<uint8_t> ArrowDown;
    extern std::vector<uint8_t> ArrowLeft;
    extern std::vector<uint8_t> ArrowRight;
    extern std::vector<uint8_t> ArrowUp;
    extern std::vector<uint8_t> Audio;
    extern std::vector<uint8_t> BellowsClosed;
    extern std::vector<uint8_t> BellowsOpen;
    extern std::vector<uint8_t> Clear;
    extern std::vector<uint8_t> Close;
    extern std::vector<uint8_t> Copy;
    extern std::vector<uint8_t> Decrement;
    extern std::vector<uint8_t> Directory;
    extern std::vector<uint8_t> DirectoryBack;
    extern std::vector<uint8_t> DirectoryForward;
    extern std::vector<uint8_t> DirectoryUp;
    extern std::vector<uint8_t> Edit;
    extern std::vector<uint8_t> Empty;
    extern std::vector<uint8_t> File;
    extern std::vector<uint8_t> FileBrowser;
    extern std::vector<uint8_t> FileClose;
    extern std::vector<uint8_t> FileCloseAll;
    extern std::vector<uint8_t> FileOpen;
    extern std::vector<uint8_t> FileReload;
    extern std::vector<uint8_t> FrameEnd;
    extern std::vector<uint8_t> FrameInOut;
    extern std::vector<uint8_t> FrameNext;
    extern std::vector<uint8_t> FramePrev;
    extern std::vector<uint8_t> FrameStart;
    extern std::vector<uint8_t> Increment;
    extern std::vector<uint8_t> MenuArrow;
    extern std::vector<uint8_t> MenuChecked;
    extern std::vector<uint8_t> Mute;
    extern std::vector<uint8_t> Next;
    extern std::vector<uint8_t> PanelBottom;
    extern std::vector<uint8_t> PanelLeft;
    extern std::vector<uint8_t> PanelRight;
    extern std::vector<uint8_t> PanelTop;
    extern std::vector<uint8_t> PlaybackForward;
    extern std::vector<uint8_t> PlaybackReverse;
    extern std::vector<uint8_t> PlaybackStop;
    extern std::vector<uint8_t> Prev;
    extern std::vector<uint8_t> Reload;
    extern std::vector<uint8_t> Reset;
    extern std::vector<uint8_t> ReverseSort;
    extern std::vector<uint8_t> Search;
    extern std::vector<uint8_t> Settings;
    extern std::vector<uint8_t> SubMenuArrow;
    extern std::vector<uint8_t> TimeEnd;
    extern std::vector<uint8_t> TimeStart;
    extern std::vector<uint8_t> ViewFrame;
    extern std::vector<uint8_t> ViewZoomIn;
    extern std::vector<uint8_t> ViewZoomOut;
    extern std::vector<uint8_t> ViewZoomReset;
    extern std::vector<uint8_t> Volume;
    extern std::vector<uint8_t> WindowFullScreen;
}

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

        p.iconData["ArrowDown"] = dtk_resource::ArrowDown;
        p.iconData["ArrowLeft"] = dtk_resource::ArrowLeft;
        p.iconData["ArrowRight"] = dtk_resource::ArrowRight;
        p.iconData["ArrowUp"] = dtk_resource::ArrowUp;
        p.iconData["Audio"] = dtk_resource::Audio;
        p.iconData["BellowsClosed"] = dtk_resource::BellowsClosed;
        p.iconData["BellowsOpen"] = dtk_resource::BellowsOpen;
        p.iconData["Clear"] = dtk_resource::Clear;
        p.iconData["Close"] = dtk_resource::Close;
        p.iconData["Copy"] = dtk_resource::Copy;
        p.iconData["Decrement"] = dtk_resource::Decrement;
        p.iconData["Directory"] = dtk_resource::Directory;
        p.iconData["DirectoryBack"] = dtk_resource::DirectoryBack;
        p.iconData["DirectoryForward"] = dtk_resource::DirectoryForward;
        p.iconData["DirectoryUp"] = dtk_resource::DirectoryUp;
        p.iconData["Edit"] = dtk_resource::Edit;
        p.iconData["Empty"] = dtk_resource::Empty;
        p.iconData["File"] = dtk_resource::File;
        p.iconData["FileBrowser"] = dtk_resource::FileBrowser;
        p.iconData["FileClose"] = dtk_resource::FileClose;
        p.iconData["FileCloseAll"] = dtk_resource::FileCloseAll;
        p.iconData["FileOpen"] = dtk_resource::FileOpen;
        p.iconData["FileReload"] = dtk_resource::FileReload;
        p.iconData["FrameEnd"] = dtk_resource::FrameEnd;
        p.iconData["FrameInOut"] = dtk_resource::FrameInOut;
        p.iconData["FrameNext"] = dtk_resource::FrameNext;
        p.iconData["FramePrev"] = dtk_resource::FramePrev;
        p.iconData["FrameStart"] = dtk_resource::FrameStart;
        p.iconData["Increment"] = dtk_resource::Increment;
        p.iconData["MenuArrow"] = dtk_resource::MenuArrow;
        p.iconData["MenuChecked"] = dtk_resource::MenuChecked;
        p.iconData["Mute"] = dtk_resource::Mute;
        p.iconData["Next"] = dtk_resource::Next;
        p.iconData["PanelBottom"] = dtk_resource::PanelBottom;
        p.iconData["PanelLeft"] = dtk_resource::PanelLeft;
        p.iconData["PanelRight"] = dtk_resource::PanelRight;
        p.iconData["PanelTop"] = dtk_resource::PanelTop;
        p.iconData["PlaybackForward"] = dtk_resource::PlaybackForward;
        p.iconData["PlaybackReverse"] = dtk_resource::PlaybackReverse;
        p.iconData["PlaybackStop"] = dtk_resource::PlaybackStop;
        p.iconData["Prev"] = dtk_resource::Prev;
        p.iconData["Reload"] = dtk_resource::Reload;
        p.iconData["Reset"] = dtk_resource::Reset;
        p.iconData["ReverseSort"] = dtk_resource::ReverseSort;
        p.iconData["Search"] = dtk_resource::Search;
        p.iconData["Settings"] = dtk_resource::Settings;
        p.iconData["SubMenuArrow"] = dtk_resource::SubMenuArrow;
        p.iconData["TimeEnd"] = dtk_resource::TimeEnd;
        p.iconData["TimeStart"] = dtk_resource::TimeStart;
        p.iconData["ViewFrame"] = dtk_resource::ViewFrame;
        p.iconData["ViewZoomIn"] = dtk_resource::ViewZoomIn;
        p.iconData["ViewZoomOut"] = dtk_resource::ViewZoomOut;
        p.iconData["ViewZoomReset"] = dtk_resource::ViewZoomReset;
        p.iconData["Volume"] = dtk_resource::Volume;
        p.iconData["WindowFullScreen"] = dtk_resource::WindowFullScreen;

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
