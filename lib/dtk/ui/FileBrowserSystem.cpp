// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/FileBrowser.h>

#include <dtk/ui/RecentFilesModel.h>

#include <dtk/core/File.h>

#if defined(dtk_NFD)
#include <nfd.hpp>
#endif // dtk_NFD

#include <nlohmann/json.hpp>

#include <sstream>

namespace dtk
{
    struct FileBrowserSystem::Private
    {
        bool native = true;
        std::filesystem::path path;
        FileBrowserOptions options;
        std::shared_ptr<FileBrowser> fileBrowser;
        std::shared_ptr<ValueObserver<FileBrowserOptions> > optionsObserver;
    };

    FileBrowserSystem::FileBrowserSystem(const std::shared_ptr<Context>& context) :
        ISystem(context, "dtk::FileBrowserSystem"),
        _p(new Private)
    {
        DTK_P();

        p.path = std::filesystem::current_path();

#if defined(dtk_NFD)
        NFD::Init();
#endif // dtk_NFD
    }

    FileBrowserSystem::~FileBrowserSystem()
    {
        DTK_P();
#if defined(dtk_NFD)
        NFD::Quit();
#endif // dtk_NFD
    }

    std::shared_ptr<FileBrowserSystem> FileBrowserSystem::create(
        const std::shared_ptr<Context>& context)
    {
        return std::shared_ptr<FileBrowserSystem>(new FileBrowserSystem(context));
    }

    void FileBrowserSystem::open(
        const std::shared_ptr<IWindow>& window,
        const std::function<void(const std::filesystem::path&)>& callback,
        FileBrowserMode mode,
        const std::shared_ptr<RecentFilesModel>& recentFilesModel)
    {
        DTK_P();
        bool native = p.native;
#if defined(dtk_NFD)
        if (native)
        {
            nfdu8char_t* outPath = nullptr;
            switch (mode)
            {
            case FileBrowserMode::File:
                NFD::OpenDialog(outPath);
                break;
            case FileBrowserMode::Dir:
                NFD::PickFolder(outPath);
                break;
            }
            if (outPath)
            {
                callback(outPath);
                NFD::FreePath(outPath);
            }
        }
#else  // dtk_NFD
        native = false;
#endif  // dtk_NFD
        if (!native)
        {
            if (auto context = _context.lock())
            {
                if (!p.fileBrowser)
                {
                    p.fileBrowser = FileBrowser::create(context, p.path, mode);
                }
                p.fileBrowser->setOptions(p.options);
                p.fileBrowser->setRecentFilesModel(recentFilesModel);

                p.fileBrowser->open(window);

                p.fileBrowser->setCallback(
                    [this, callback](const std::filesystem::path& value)
                    {
                        callback(value);
                        _p->fileBrowser->close();
                    });
                p.fileBrowser->setCloseCallback(
                    [this]
                    {
                        _p->path = _p->fileBrowser->getPath();
                        _p->options = _p->fileBrowser->getOptions();
                        _p->fileBrowser.reset();
                    });

                p.optionsObserver = ValueObserver<FileBrowserOptions>::create(
                    p.fileBrowser->observeOptions(),
                    [this](const FileBrowserOptions& value)
                    {
                        _p->options = value;
                    });
            }
        }
    }

    bool FileBrowserSystem::isNativeFileDialog() const
    {
        return _p->native;
    }

    void FileBrowserSystem::setNativeFileDialog(bool value)
    {
        _p->native = value;
    }

    const std::filesystem::path& FileBrowserSystem::getPath() const
    {
        return _p->path;
    }

    void FileBrowserSystem::setPath(const std::filesystem::path& value)
    {
        _p->path = value;
    }

    const FileBrowserOptions& FileBrowserSystem::getOptions() const
    {
        return _p->options;
    }

    void FileBrowserSystem::setOptions(const FileBrowserOptions& options)
    {
        _p->options = options;
    }
}