// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/FileBrowser.h>

#include <dtk/ui/FileBrowserPrivate.h>

#include <dtk/core/Error.h>
#include <dtk/core/String.h>

#include <sstream>

namespace dtk
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
            leftPanel == other.leftPanel &&
            pathEdit == other.pathEdit &&
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
        IDialog::_init(context, "dtk::FileBrowser", parent);
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

    std::shared_ptr<IObservableValue<FileBrowserOptions> > FileBrowser::observeOptions() const
    {
        return _p->widget->observeOptions();
    }

    void FileBrowser::setOptions(const FileBrowserOptions& value)
    {
        _p->widget->setOptions(value);
    }

    void FileBrowser::setExtensions(
        const std::vector<std::string>& value,
        const std::string& current)
    {
        _p->widget->setExtensions(value, current);
    }

    const std::shared_ptr<RecentFilesModel>& FileBrowser::getRecentFilesModel() const
    {
        return _p->widget->getRecentFilesModel();
    }

    void FileBrowser::setRecentFilesModel(const std::shared_ptr<RecentFilesModel>& value)
    {
        _p->widget->setRecentFilesModel(value);
    }

    void to_json(nlohmann::json& json, const FileBrowserOptions& value)
    {
        json["leftPanel"] = value.leftPanel;
        json["pathEdit"] = value.pathEdit;
        json["sort"] = to_string(value.sort);
        json["reverseSort"] = value.reverseSort;
    }

    void from_json(const nlohmann::json& json, FileBrowserOptions& value)
    {
        json["leftPanel"].get_to(value.leftPanel);
        json["pathEdit"].get_to(value.pathEdit);
        from_string(json["sort"].get<std::string>(), value.sort);
        json["reverseSort"].get_to(value.reverseSort);
    }
}