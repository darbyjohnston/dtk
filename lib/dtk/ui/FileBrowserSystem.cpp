// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/FileBrowser.h>

#include <dtk/ui/RecentFilesModel.h>

#include <dtk/core/File.h>

#if defined(dtk_NFD)
#include <nfd.hpp>
#endif // dtk_NFD

#include <filesystem>

namespace dtk
{
    namespace ui
    {
        struct FileBrowserSystem::Private
        {
            bool native = true;
            std::filesystem::path path;
            FileBrowserOptions options;
            std::shared_ptr<FileBrowser> fileBrowser;
            std::shared_ptr<RecentFilesModel> recentFilesModel;
        };

        FileBrowserSystem::FileBrowserSystem(const std::shared_ptr<Context>& context) :
            ISystem(context, "dtk::ui::FileBrowserSystem"),
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
#if defined(dtk_NFD)
            NFD::Quit();
#endif // dtk_NFD
        }

        std::shared_ptr<FileBrowserSystem> FileBrowserSystem::create(const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FileBrowserSystem>(new FileBrowserSystem(context));
        }

        void FileBrowserSystem::open(
            const std::shared_ptr<IWindow>& window,
            const std::function<void(const std::filesystem::path&)>& callback)
        {
            DTK_P();
            bool native = p.native;
#if defined(dtk_NFD)
            if (native)
            {
                nfdu8char_t* outPath = nullptr;
                NFD::OpenDialog(outPath);
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
                        p.fileBrowser = FileBrowser::create(context, p.path);
                        p.fileBrowser->setRecentFilesModel(p.recentFilesModel);
                    }
                    p.fileBrowser->setOptions(p.options);
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

        const std::shared_ptr<RecentFilesModel>& FileBrowserSystem::getRecentFilesModel() const
        {
            return _p->recentFilesModel;
        }
    }
}
