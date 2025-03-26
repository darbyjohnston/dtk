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
        std::vector<std::string> extensions;
        std::string extension;
        std::shared_ptr<RecentFilesModel> recentFilesModel;

        std::shared_ptr<FileBrowser> fileBrowser;
    };

    FileBrowserSystem::FileBrowserSystem(const std::shared_ptr<Context>& context) :
        ISystem(context, "dtk::FileBrowserSystem"),
        _p(new Private)
    {
        DTK_P();

        p.path = std::filesystem::current_path();
        p.recentFilesModel = RecentFilesModel::create(context);

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
        FileBrowserMode mode)
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
                p.fileBrowser->setExtensions(p.extensions);
                p.fileBrowser->setExtension(p.extension);
                p.fileBrowser->setRecentFilesModel(p.recentFilesModel);

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
                        DTK_P();
                        p.path = p.fileBrowser->getPath();
                        p.options = p.fileBrowser->getOptions();
                        p.extension = p.fileBrowser->getExtension();
                        p.fileBrowser.reset();
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

    const std::vector<std::string>& FileBrowserSystem::getExtensions() const
    {
        return _p->extensions;
    }

    void FileBrowserSystem::setExtensions(const std::vector<std::string>& value)
    {
        _p->extensions = value;
    }

    const std::string& FileBrowserSystem::getExtension() const
    {
        return _p->extension;
    }

    void FileBrowserSystem::setExtension(const std::string& value)
    {
        _p->extension = value;
    }

    const std::shared_ptr<RecentFilesModel>& FileBrowserSystem::getRecentFilesModel() const
    {
        return _p->recentFilesModel;
    }

    void FileBrowserSystem::setRecentFilesModel(const std::shared_ptr<RecentFilesModel>& value)
    {
        _p->recentFilesModel = value;
    }
}