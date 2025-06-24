// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/FileBrowser.h>

#include <feather-tk/ui/RecentFilesModel.h>

#include <feather-tk/core/File.h>

#if defined(FEATHER_TK_NFD)
#include <nfd.hpp>
#endif // FEATHER_TK_NFD

#include <nlohmann/json.hpp>

#include <sstream>

namespace feather_tk
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
        ISystem(context, "feather_tk::FileBrowserSystem"),
        _p(new Private)
    {
        FEATHER_TK_P();

        p.path = std::filesystem::current_path();
        p.recentFilesModel = RecentFilesModel::create(context);

#if defined(FEATHER_TK_NFD)
        NFD::Init();
#endif // FEATHER_TK_NFD
    }

    FileBrowserSystem::~FileBrowserSystem()
    {
        FEATHER_TK_P();
#if defined(FEATHER_TK_NFD)
        NFD::Quit();
#endif // FEATHER_TK_NFD
    }

    std::shared_ptr<FileBrowserSystem> FileBrowserSystem::create(
        const std::shared_ptr<Context>& context)
    {
        return std::shared_ptr<FileBrowserSystem>(new FileBrowserSystem(context));
    }

    void FileBrowserSystem::open(
        const std::shared_ptr<IWindow>& window,
        const std::function<void(const std::filesystem::path&)>& callback,
        const std::filesystem::path& fileName,
        FileBrowserMode mode)
    {
        FEATHER_TK_P();
        bool native = p.native;
#if defined(FEATHER_TK_NFD)
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
            default: break;
            }
            if (outPath)
            {
                callback(outPath);
                NFD::FreePath(outPath);
            }
        }
#else  // FEATHER_TK_NFD
        native = false;
#endif  // FEATHER_TK_NFD
        if (!native)
        {
            if (auto context = _context.lock())
            {
                if (!p.fileBrowser)
                {
                    p.fileBrowser = FileBrowser::create(context, p.path, fileName, mode);
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
                        FEATHER_TK_P();
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
