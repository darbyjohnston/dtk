// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/IconLibrary.h>

#include <dtk/core/ImageIO.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>
#include <dtk/core/LRUCache.h>

namespace
{
#include <Icons/Audio_96.h>
#include <Icons/BellowsClosed_96.h>
#include <Icons/BellowsOpen_96.h>
#include <Icons/Clear_96.h>
#include <Icons/Close_96.h>
#include <Icons/Copy_96.h>
#include <Icons/Decrement_96.h>
#include <Icons/Directory_96.h>
#include <Icons/DirectoryBack_96.h>
#include <Icons/DirectoryForward_96.h>
#include <Icons/DirectoryUp_96.h>
#include <Icons/Empty_96.h>
#include <Icons/File_96.h>
#include <Icons/FileBrowser_96.h>
#include <Icons/FileClose_96.h>
#include <Icons/FileCloseAll_96.h>
#include <Icons/FileOpen_96.h>
#include <Icons/FrameEnd_96.h>
#include <Icons/FrameNext_96.h>
#include <Icons/FramePrev_96.h>
#include <Icons/FrameStart_96.h>
#include <Icons/Increment_96.h>
#include <Icons/MenuArrow_96.h>
#include <Icons/MenuChecked_96.h>
#include <Icons/Mute_96.h>
#include <Icons/Next_96.h>
#include <Icons/PlaybackForward_96.h>
#include <Icons/PlaybackReverse_96.h>
#include <Icons/PlaybackStop_96.h>
#include <Icons/Prev_96.h>
#include <Icons/Reload_96.h>
#include <Icons/Reset_96.h>
#include <Icons/ReverseSort_96.h>
#include <Icons/Search_96.h>
#include <Icons/Settings_96.h>
#include <Icons/SubMenuArrow_96.h>
#include <Icons/TimeEnd_96.h>
#include <Icons/TimeStart_96.h>
#include <Icons/Volume_96.h>
#include <Icons/WindowFullScreen_96.h>

#include <Icons/Audio_192.h>
#include <Icons/BellowsClosed_192.h>
#include <Icons/BellowsOpen_192.h>
#include <Icons/Clear_192.h>
#include <Icons/Close_192.h>
#include <Icons/Copy_192.h>
#include <Icons/Decrement_192.h>
#include <Icons/Directory_192.h>
#include <Icons/DirectoryBack_192.h>
#include <Icons/DirectoryForward_192.h>
#include <Icons/DirectoryUp_192.h>
#include <Icons/Empty_192.h>
#include <Icons/File_192.h>
#include <Icons/FileBrowser_192.h>
#include <Icons/FileClose_192.h>
#include <Icons/FileCloseAll_192.h>
#include <Icons/FileOpen_192.h>
#include <Icons/FrameEnd_192.h>
#include <Icons/FrameNext_192.h>
#include <Icons/FramePrev_192.h>
#include <Icons/FrameStart_192.h>
#include <Icons/Increment_192.h>
#include <Icons/MenuArrow_192.h>
#include <Icons/MenuChecked_192.h>
#include <Icons/Mute_192.h>
#include <Icons/Next_192.h>
#include <Icons/PlaybackForward_192.h>
#include <Icons/PlaybackReverse_192.h>
#include <Icons/PlaybackStop_192.h>
#include <Icons/Prev_192.h>
#include <Icons/Reload_192.h>
#include <Icons/Reset_192.h>
#include <Icons/ReverseSort_192.h>
#include <Icons/Search_192.h>
#include <Icons/Settings_192.h>
#include <Icons/SubMenuArrow_192.h>
#include <Icons/TimeEnd_192.h>
#include <Icons/TimeStart_192.h>
#include <Icons/Volume_192.h>
#include <Icons/WindowFullScreen_192.h>

#include <Icons/Audio_288.h>
#include <Icons/BellowsClosed_288.h>
#include <Icons/BellowsOpen_288.h>
#include <Icons/Clear_288.h>
#include <Icons/Close_288.h>
#include <Icons/Copy_288.h>
#include <Icons/Decrement_288.h>
#include <Icons/Directory_288.h>
#include <Icons/DirectoryBack_288.h>
#include <Icons/DirectoryForward_288.h>
#include <Icons/DirectoryUp_288.h>
#include <Icons/Empty_288.h>
#include <Icons/File_288.h>
#include <Icons/FileBrowser_288.h>
#include <Icons/FileClose_288.h>
#include <Icons/FileCloseAll_288.h>
#include <Icons/FileOpen_288.h>
#include <Icons/FrameEnd_288.h>
#include <Icons/FrameNext_288.h>
#include <Icons/FramePrev_288.h>
#include <Icons/FrameStart_288.h>
#include <Icons/Increment_288.h>
#include <Icons/MenuArrow_288.h>
#include <Icons/MenuChecked_288.h>
#include <Icons/Mute_288.h>
#include <Icons/Next_288.h>
#include <Icons/PlaybackForward_288.h>
#include <Icons/PlaybackReverse_288.h>
#include <Icons/PlaybackStop_288.h>
#include <Icons/Prev_288.h>
#include <Icons/Reload_288.h>
#include <Icons/Reset_288.h>
#include <Icons/ReverseSort_288.h>
#include <Icons/Search_288.h>
#include <Icons/Settings_288.h>
#include <Icons/SubMenuArrow_288.h>
#include <Icons/TimeEnd_288.h>
#include <Icons/TimeStart_288.h>
#include <Icons/Volume_288.h>
#include <Icons/WindowFullScreen_288.h>
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

    struct IconLibrary::Private
    {
        std::weak_ptr<Context> context;

        std::map<std::pair<std::string, int>, std::vector<uint8_t> > iconData;

        struct Request
        {
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
    };

    void IconLibrary::_init(const std::shared_ptr<Context>& context)
    {
        DTK_P();
        p.context = context;

        p.iconData[std::make_pair("Audio", 96)] = Audio_96_png;
        p.iconData[std::make_pair("BellowsClosed", 96)] = BellowsClosed_96_png;
        p.iconData[std::make_pair("BellowsOpen", 96)] = BellowsOpen_96_png;
        p.iconData[std::make_pair("Clear", 96)] = Clear_96_png;
        p.iconData[std::make_pair("Close", 96)] = Close_96_png;
        p.iconData[std::make_pair("Copy", 96)] = Copy_96_png;
        p.iconData[std::make_pair("Decrement", 96)] = Decrement_96_png;
        p.iconData[std::make_pair("Directory", 96)] = Directory_96_png;
        p.iconData[std::make_pair("DirectoryBack", 96)] = DirectoryBack_96_png;
        p.iconData[std::make_pair("DirectoryForward", 96)] = DirectoryForward_96_png;
        p.iconData[std::make_pair("DirectoryUp", 96)] = DirectoryUp_96_png;
        p.iconData[std::make_pair("Empty", 96)] = Empty_96_png;
        p.iconData[std::make_pair("File", 96)] = File_96_png;
        p.iconData[std::make_pair("FileBrowser", 96)] = FileBrowser_96_png;
        p.iconData[std::make_pair("FileClose", 96)] = FileClose_96_png;
        p.iconData[std::make_pair("FileCloseAll", 96)] = FileCloseAll_96_png;
        p.iconData[std::make_pair("FileOpen", 96)] = FileOpen_96_png;
        p.iconData[std::make_pair("FrameEnd", 96)] = FrameEnd_96_png;
        p.iconData[std::make_pair("FrameNext", 96)] = FrameNext_96_png;
        p.iconData[std::make_pair("FramePrev", 96)] = FramePrev_96_png;
        p.iconData[std::make_pair("FrameStart", 96)] = FrameStart_96_png;
        p.iconData[std::make_pair("Increment", 96)] = Increment_96_png;
        p.iconData[std::make_pair("MenuArrow", 96)] = MenuArrow_96_png;
        p.iconData[std::make_pair("MenuChecked", 96)] = MenuChecked_96_png;
        p.iconData[std::make_pair("Mute", 96)] = Mute_96_png;
        p.iconData[std::make_pair("Next", 96)] = Next_96_png;
        p.iconData[std::make_pair("PlaybackForward", 96)] = PlaybackForward_96_png;
        p.iconData[std::make_pair("PlaybackReverse", 96)] = PlaybackReverse_96_png;
        p.iconData[std::make_pair("PlaybackStop", 96)] = PlaybackStop_96_png;
        p.iconData[std::make_pair("Prev", 96)] = Prev_96_png;
        p.iconData[std::make_pair("Reset", 96)] = Reset_96_png;
        p.iconData[std::make_pair("ReverseSort", 96)] = Reset_96_png;
        p.iconData[std::make_pair("Reload", 96)] = Reload_96_png;
        p.iconData[std::make_pair("Search", 96)] = Search_96_png;
        p.iconData[std::make_pair("Settings", 96)] = Settings_96_png;
        p.iconData[std::make_pair("SubMenuArrow", 96)] = SubMenuArrow_96_png;
        p.iconData[std::make_pair("TimeEnd", 96)] = TimeEnd_96_png;
        p.iconData[std::make_pair("TimeStart", 96)] = TimeStart_96_png;
        p.iconData[std::make_pair("Volume", 96)] = Volume_96_png;
        p.iconData[std::make_pair("WindowFullScreen", 96)] = WindowFullScreen_96_png;

        p.iconData[std::make_pair("Audio", 192)] = Audio_192_png;
        p.iconData[std::make_pair("BellowsClosed", 192)] = BellowsClosed_192_png;
        p.iconData[std::make_pair("BellowsOpen", 192)] = BellowsOpen_192_png;
        p.iconData[std::make_pair("Clear", 192)] = Clear_192_png;
        p.iconData[std::make_pair("Close", 192)] = Close_192_png;
        p.iconData[std::make_pair("Copy", 192)] = Copy_192_png;
        p.iconData[std::make_pair("Decrement", 192)] = Decrement_192_png;
        p.iconData[std::make_pair("Directory", 192)] = Directory_192_png;
        p.iconData[std::make_pair("DirectoryBack", 192)] = DirectoryBack_192_png;
        p.iconData[std::make_pair("DirectoryForward", 192)] = DirectoryForward_192_png;
        p.iconData[std::make_pair("DirectoryUp", 192)] = DirectoryUp_192_png;
        p.iconData[std::make_pair("Empty", 192)] = Empty_192_png;
        p.iconData[std::make_pair("File", 192)] = File_192_png;
        p.iconData[std::make_pair("FileBrowser", 192)] = FileBrowser_192_png;
        p.iconData[std::make_pair("FileClose", 192)] = FileClose_192_png;
        p.iconData[std::make_pair("FileCloseAll", 192)] = FileCloseAll_192_png;
        p.iconData[std::make_pair("FileOpen", 192)] = FileOpen_192_png;
        p.iconData[std::make_pair("FrameEnd", 192)] = FrameEnd_192_png;
        p.iconData[std::make_pair("FrameNext", 192)] = FrameNext_192_png;
        p.iconData[std::make_pair("FramePrev", 192)] = FramePrev_192_png;
        p.iconData[std::make_pair("FrameStart", 192)] = FrameStart_192_png;
        p.iconData[std::make_pair("Increment", 192)] = Increment_192_png;
        p.iconData[std::make_pair("MenuArrow", 192)] = MenuArrow_192_png;
        p.iconData[std::make_pair("MenuChecked", 192)] = MenuChecked_192_png;
        p.iconData[std::make_pair("Mute", 192)] = Mute_192_png;
        p.iconData[std::make_pair("Next", 192)] = Next_192_png;
        p.iconData[std::make_pair("PlaybackForward", 192)] = PlaybackForward_192_png;
        p.iconData[std::make_pair("PlaybackReverse", 192)] = PlaybackReverse_192_png;
        p.iconData[std::make_pair("PlaybackStop", 192)] = PlaybackStop_192_png;
        p.iconData[std::make_pair("Prev", 192)] = Prev_192_png;
        p.iconData[std::make_pair("Reset", 192)] = Reset_192_png;
        p.iconData[std::make_pair("ReverseSort", 192)] = ReverseSort_192_png;
        p.iconData[std::make_pair("Reload", 192)] = Reload_192_png;
        p.iconData[std::make_pair("Search", 192)] = Search_192_png;
        p.iconData[std::make_pair("Settings", 192)] = Settings_192_png;
        p.iconData[std::make_pair("SubMenuArrow", 192)] = SubMenuArrow_192_png;
        p.iconData[std::make_pair("TimeEnd", 192)] = TimeEnd_192_png;
        p.iconData[std::make_pair("TimeStart", 192)] = TimeStart_192_png;
        p.iconData[std::make_pair("Volume", 192)] = Volume_192_png;
        p.iconData[std::make_pair("WindowFullScreen", 192)] = WindowFullScreen_192_png;

        p.iconData[std::make_pair("Audio", 288)] = Audio_288_png;
        p.iconData[std::make_pair("BellowsClosed", 288)] = BellowsClosed_288_png;
        p.iconData[std::make_pair("BellowsOpen", 288)] = BellowsOpen_288_png;
        p.iconData[std::make_pair("Clear", 288)] = Clear_288_png;
        p.iconData[std::make_pair("Close", 288)] = Close_288_png;
        p.iconData[std::make_pair("Copy", 288)] = Copy_288_png;
        p.iconData[std::make_pair("Decrement", 288)] = Decrement_288_png;
        p.iconData[std::make_pair("Directory", 288)] = Directory_288_png;
        p.iconData[std::make_pair("DirectoryBack", 288)] = DirectoryBack_288_png;
        p.iconData[std::make_pair("DirectoryForward", 288)] = DirectoryForward_288_png;
        p.iconData[std::make_pair("DirectoryUp", 288)] = DirectoryUp_288_png;
        p.iconData[std::make_pair("Empty", 288)] = Empty_288_png;
        p.iconData[std::make_pair("File", 288)] = File_288_png;
        p.iconData[std::make_pair("FileBrowser", 288)] = FileBrowser_288_png;
        p.iconData[std::make_pair("FileClose", 288)] = FileClose_288_png;
        p.iconData[std::make_pair("FileCloseAll", 288)] = FileCloseAll_288_png;
        p.iconData[std::make_pair("FileOpen", 288)] = FileOpen_288_png;
        p.iconData[std::make_pair("FrameEnd", 288)] = FrameEnd_288_png;
        p.iconData[std::make_pair("FrameNext", 288)] = FrameNext_288_png;
        p.iconData[std::make_pair("FramePrev", 288)] = FramePrev_288_png;
        p.iconData[std::make_pair("FrameStart", 288)] = FrameStart_288_png;
        p.iconData[std::make_pair("Increment", 288)] = Increment_288_png;
        p.iconData[std::make_pair("MenuArrow", 288)] = MenuArrow_288_png;
        p.iconData[std::make_pair("MenuChecked", 288)] = MenuChecked_288_png;
        p.iconData[std::make_pair("Mute", 288)] = Mute_288_png;
        p.iconData[std::make_pair("Next", 288)] = Next_288_png;
        p.iconData[std::make_pair("PlaybackForward", 288)] = PlaybackForward_288_png;
        p.iconData[std::make_pair("PlaybackReverse", 288)] = PlaybackReverse_288_png;
        p.iconData[std::make_pair("PlaybackStop", 288)] = PlaybackStop_288_png;
        p.iconData[std::make_pair("Prev", 288)] = Prev_288_png;
        p.iconData[std::make_pair("Reset", 288)] = Reset_288_png;
        p.iconData[std::make_pair("ReverseSort", 288)] = ReverseSort_288_png;
        p.iconData[std::make_pair("Reload", 288)] = Reload_288_png;
        p.iconData[std::make_pair("Search", 288)] = Search_288_png;
        p.iconData[std::make_pair("Settings", 288)] = Settings_288_png;
        p.iconData[std::make_pair("SubMenuArrow", 288)] = SubMenuArrow_288_png;
        p.iconData[std::make_pair("TimeEnd", 288)] = TimeEnd_288_png;
        p.iconData[std::make_pair("TimeStart", 288)] = TimeStart_288_png;
        p.iconData[std::make_pair("Volume", 288)] = Volume_288_png;
        p.iconData[std::make_pair("WindowFullScreen", 288)] = WindowFullScreen_288_png;

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
                        int dpi = 96;
                        if (request->displayScale >= 3.F)
                        {
                            dpi = 288;
                        }
                        else if (request->displayScale >= 2.F)
                        {
                            dpi = 192;
                        }
                        //std::cout << "icon request: " << request->name << " " << dpi << std::endl;
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
                            const auto j = p.iconData.find(std::make_pair(request->name, dpi));
                            if (j != p.iconData.end())
                            {
                                if (auto context = p.context.lock())
                                {
                                    try
                                    {
                                        const std::string name = Format("{0}_{1}.png").
                                            arg(request->name).
                                            arg(dpi);
                                        auto reader = context->getSystem<ImageIO>()->read(
                                            name,
                                            InMemoryFile(j->second.data(), j->second.size()));
                                        if (reader)
                                        {
                                            image = reader->read();
                                        }
                                    }
                                    catch (const std::exception&)
                                    {
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
                cancelRequests();
            });
    }

    IconLibrary::IconLibrary() :
        _p(new Private)
    {}

    IconLibrary::~IconLibrary()
    {
        DTK_P();
        p.thread.running = false;
        if (p.thread.thread.joinable())
        {
            p.thread.thread.join();
        }
    }

    std::shared_ptr<IconLibrary> IconLibrary::create(
        const std::shared_ptr<Context>& context)
    {
        auto out = std::shared_ptr<IconLibrary>(new IconLibrary);
        out->_init(context);
        return out;
    }

    std::future<std::shared_ptr<Image> > IconLibrary::request(
        const std::string& name,
        float displayScale)
    {
        DTK_P();
        auto request = std::make_shared<Private::Request>();
        request->name = name;
        request->displayScale = displayScale;
        auto future = request->promise.get_future();
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
        return future;
    }

    void IconLibrary::cancelRequests()
    {
        DTK_P();
        std::list<std::shared_ptr<Private::Request> > requests;
        {
            std::unique_lock<std::mutex> lock(p.mutex.mutex);
            requests = std::move(p.mutex.requests);
        }
        for (auto& request : requests)
        {
            request->promise.set_value(nullptr);
        }
    }
}