// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/FileBrowser.h>

#include <feather-tk/ui/FileBrowserPrivate.h>

#include <feather-tk/core/Error.h>
#include <feather-tk/core/String.h>

#include <sstream>

namespace feather_tk
{
    FEATHER_TK_ENUM_IMPL(
        FileBrowserMode,
        "File",
        "Dir");

    FEATHER_TK_ENUM_IMPL(
        FileBrowserSort,
        "Name",
        "Extension",
        "Size",
        "Time");

    bool FileBrowserOptions::operator == (const FileBrowserOptions& other) const
    {
        return
            panel == other.panel &&
            pathEdit == other.pathEdit &&
            sort == other.sort &&
            reverseSort == other.reverseSort &&
            hidden == other.hidden &&
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
        const std::filesystem::path& fileName,
        FileBrowserMode mode,
        const std::shared_ptr<FileBrowserModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        IDialog::_init(context, "feather_tk::FileBrowser", parent);
        FEATHER_TK_P();

        p.widget = FileBrowserWidget::create(
            context,
            fileName,
            mode,
            model,
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
        const std::filesystem::path& fileName,
        FileBrowserMode mode,
        const std::shared_ptr<FileBrowserModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<FileBrowser>(new FileBrowser);
        out->_init(context, fileName, mode, model, parent);
        return out;
    }

    void FileBrowser::setCallback(const std::function<void(const std::filesystem::path&)>& value)
    {
        _p->widget->setCallback(value);
    }

    const std::shared_ptr<FileBrowserModel>& FileBrowser::getModel() const
    {
        return _p->widget->getModel();
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
        json["Panel"] = value.panel;
        json["PathEdit"] = value.pathEdit;
        json["Sort"] = to_string(value.sort);
        json["ReverseSort"] = value.reverseSort;
        json["Hidden"] = value.hidden;
        for (const auto& i : value.bellows)
        {
            json["Bellows"][i.first] = i.second;
        }
    }

    void from_json(const nlohmann::json& json, FileBrowserOptions& value)
    {
        json.at("Panel").get_to(value.panel);
        json.at("PathEdit").get_to(value.pathEdit);
        from_string(json.at("Sort").get<std::string>(), value.sort);
        json.at("ReverseSort").get_to(value.reverseSort);
        json.at("Hidden").get_to(value.hidden);
        for (auto i = json.at("Bellows").begin(); i != json.at("Bellows").end(); ++i)
        {
            if (i->is_boolean())
            {
                i->get_to(value.bellows[i.key()]);
            }
        }
    }
}