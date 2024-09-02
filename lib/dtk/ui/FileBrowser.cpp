// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/FileBrowser.h>

#include <dtk/ui/FileBrowserPrivate.h>

#include <dtk/core/Error.h>
#include <dtk/core/String.h>

using namespace dtk::core;

namespace dtk
{
    namespace ui
    {
        DTK_ENUM_IMPL(
            FileBrowserSort,
            "Name",
            "Extension",
            "Size",
            "Time");

        bool FileBrowserOptions::operator == (const FileBrowserOptions& other) const
        {
            return
                search == other.search &&
                extension == other.extension &&
                sort == other.sort &&
                reverseSort == other.reverseSort;
        }

        bool FileBrowserOptions::operator != (const FileBrowserOptions& other) const
        {
            return !(*this == other);
        }

        struct FileBrowser::Private
        {
            std::shared_ptr<FileBrowserWidget> widget;
        };

        void FileBrowser::_init(
            const std::shared_ptr<Context>& context,
            const std::filesystem::path& path,
            const std::shared_ptr<IWidget>& parent)
        {
            IDialog::_init(context, "dtk::ui::FileBrowser", parent);
            DTK_P();

            p.widget = FileBrowserWidget::create(
                context,
                path,
                shared_from_this());

            p.widget->setCancelCallback(
                [this]
                {
                    close();
                });
        }

        FileBrowser::FileBrowser() :
            _p(new Private)
        {}

        FileBrowser::~FileBrowser()
        {}

        std::shared_ptr<FileBrowser> FileBrowser::create(
            const std::shared_ptr<Context>& context,
            const std::filesystem::path& path,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<FileBrowser>(new FileBrowser);
            out->_init(context, path, parent);
            return out;
        }

        void FileBrowser::setCallback(const std::function<void(const std::filesystem::path&)>& value)
        {
            _p->widget->setCallback(value);
        }

        std::filesystem::path FileBrowser::getPath() const
        {
            return _p->widget->getPath();
        }

        const FileBrowserOptions& FileBrowser::getOptions() const
        {
            return _p->widget->getOptions();
        }

        void FileBrowser::setOptions(const FileBrowserOptions& value)
        {
            _p->widget->setOptions(value);
        }

        const std::shared_ptr<RecentFilesModel>& FileBrowser::getRecentFilesModel() const
        {
            return _p->widget->getRecentFilesModel();
        }

        void FileBrowser::setRecentFilesModel(const std::shared_ptr<RecentFilesModel>& value)
        {
            _p->widget->setRecentFilesModel(value);
        }
    }
}
