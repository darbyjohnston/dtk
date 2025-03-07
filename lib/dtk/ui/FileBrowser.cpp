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
        FileBrowserMode,
        "File",
        "Dir");

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
            reverseSort == other.reverseSort &&
            bellows == other.bellows;
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
        FileBrowserMode mode,
        const std::shared_ptr<IWidget>& parent)
    {
        IDialog::_init(context, "dtk::FileBrowser", parent);
        DTK_P();

        p.widget = FileBrowserWidget::create(
            context,
            path,
            mode,
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
        FileBrowserMode mode,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<FileBrowser>(new FileBrowser);
        out->_init(context, path, mode, parent);
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
        json["LeftPanel"] = value.leftPanel;
        json["PathEdit"] = value.pathEdit;
        json["Sort"] = to_string(value.sort);
        json["ReverseSort"] = value.reverseSort;
        for (const auto& i : value.bellows)
        {
            json["Bellows"][i.first] = i.second;
        }
    }

    void from_json(const nlohmann::json& json, FileBrowserOptions& value)
    {
        json.at("LeftPanel").get_to(value.leftPanel);
        json.at("PathEdit").get_to(value.pathEdit);
        from_string(json.at("Sort").get<std::string>(), value.sort);
        json.at("ReverseSort").get_to(value.reverseSort);
        for (auto i = json.at("Bellows").begin(); i != json.at("Bellows").end(); ++i)
        {
            if (i->is_boolean())
            {
                i->get_to(value.bellows[i.key()]);
            }
        }
    }
}