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
        std::shared_ptr<FileBrowserModel> model;
        std::shared_ptr<RecentFilesModel> recentFilesModel;

        std::shared_ptr<FileBrowser> fileBrowser;
    };

    FileBrowserSystem::FileBrowserSystem(const std::shared_ptr<Context>& context) :
        ISystem(context, "feather_tk::FileBrowserSystem"),
        _p(new Private)
    {
        FEATHER_TK_P();

        p.model = FileBrowserModel::create(context);
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
                    p.fileBrowser = FileBrowser::create(
                        context,
                        fileName,
                        mode,
                        p.model);
                }
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
                        _p->fileBrowser.reset();
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

    const std::shared_ptr<FileBrowserModel>& FileBrowserSystem::getModel() const
    {
        return _p->model;
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
