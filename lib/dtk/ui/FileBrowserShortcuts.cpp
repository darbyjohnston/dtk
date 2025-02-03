// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/FileBrowserPrivate.h>

#include <dtk/ui/Bellows.h>
#include <dtk/ui/ButtonGroup.h>
#include <dtk/ui/DrivesModel.h>
#include <dtk/ui/ListItemsWidget.h>
#include <dtk/ui/RecentFilesModel.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/File.h>

#include <filesystem>

namespace dtk
{
    struct FileBrowserShortcuts::Private
    {
        std::shared_ptr<DrivesModel> drivesModel;
        std::vector<std::filesystem::path> drives;
        std::vector<std::filesystem::path> shortcuts;
        std::shared_ptr<RecentFilesModel> recentFilesModel;
        std::vector<std::filesystem::path> recent;
        std::map<std::string, std::shared_ptr<ListItemsWidget> > listWidgets;
        std::map<std::string, std::shared_ptr<Bellows> > bellows;
        std::shared_ptr<VerticalLayout> layout;
        std::function<void(const std::filesystem::path&)> callback;
        std::shared_ptr<ListObserver<std::filesystem::path> > drivesObserver;
        std::shared_ptr<ListObserver<std::filesystem::path> > recentObserver;
    };

    void FileBrowserShortcuts::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::FileBrowserShortcuts", parent);
        DTK_P();

        setBackgroundRole(ColorRole::Base);

        p.drivesModel = DrivesModel::create(context);

        p.layout = VerticalLayout::create(context, shared_from_this());
        p.layout->setSpacingRole(SizeRole::None);

        p.listWidgets["Drives"] = ListItemsWidget::create(context, ButtonGroupType::Click);
        p.bellows["Drives"] = Bellows::create(context, "Drives", p.layout);
        p.bellows["Drives"]->setOpen(true);
        p.bellows["Drives"]->setWidget(p.listWidgets["Drives"]);

        p.listWidgets["Shortcuts"] = ListItemsWidget::create(context, ButtonGroupType::Click);
        p.bellows["Shortcuts"] = Bellows::create(context, "Shortcuts", p.layout);
        p.bellows["Shortcuts"]->setOpen(true);
        p.bellows["Shortcuts"]->setWidget(p.listWidgets["Shortcuts"]);

        p.listWidgets["Recent"] = ListItemsWidget::create(context, ButtonGroupType::Click);
        p.bellows["Recent"] = Bellows::create(context, "Recent", p.layout);
        p.bellows["Recent"]->setOpen(true);
        p.bellows["Recent"]->setWidget(p.listWidgets["Recent"]);

        _widgetUpdate();

        p.listWidgets["Drives"]->setCallback(
            [this](int index, bool)
            {
                DTK_P();
                if (index >= 0 && index < p.drives.size() && p.callback)
                {
                    p.callback(p.drives[index]);
                }
            });

        p.listWidgets["Shortcuts"]->setCallback(
            [this](int index, bool)
            {
                DTK_P();
                if (index >= 0 && index < p.shortcuts.size() && p.callback)
                {
                    p.callback(p.shortcuts[index]);
                }
            });

        p.listWidgets["Recent"]->setCallback(
            [this](int index, bool)
            {
                DTK_P();
                if (index >= 0 && index < p.recent.size() && p.callback)
                {
                    p.callback(p.recent[index]);
                }
            });

        p.drivesObserver = ListObserver<std::filesystem::path>::create(
            p.drivesModel->observeDrives(),
            [this](const std::vector<std::filesystem::path>& value)
            {
                _p->drives = value;
                _widgetUpdate();
            });
    }

    FileBrowserShortcuts::FileBrowserShortcuts() :
        _p(new Private)
    {}

    FileBrowserShortcuts::~FileBrowserShortcuts()
    {}

    std::shared_ptr<FileBrowserShortcuts> FileBrowserShortcuts::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<FileBrowserShortcuts>(new FileBrowserShortcuts);
        out->_init(context, parent);
        return out;
    }

    void FileBrowserShortcuts::setCallback(const std::function<void(const std::filesystem::path&)>& value)
    {
        _p->callback = value;
    }

    void FileBrowserShortcuts::setRecentFilesModel(const std::shared_ptr<RecentFilesModel>& value)
    {
        DTK_P();
        p.recentObserver.reset();
        p.recentFilesModel = value;
        if (p.recentFilesModel)
        {
            p.recentObserver = ListObserver<std::filesystem::path>::create(
                p.recentFilesModel->observeRecent(),
                [this](const std::vector<std::filesystem::path>& paths)
                {
                    _p->recent.clear();
                    for (const auto& path : paths)
                    {
                        auto tmp = path;
                        if (!std::filesystem::is_directory(tmp))
                        {
                            tmp = tmp.parent_path();
                        }
                        const auto i = std::find(_p->recent.begin(), _p->recent.end(), tmp);
                        if (i == _p->recent.end())
                        {
                            _p->recent.push_back(tmp);
                        }
                    }
                    _widgetUpdate();
                });
        }
    }

    void FileBrowserShortcuts::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->layout->setGeometry(value);
    }

    void FileBrowserShortcuts::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->layout->getSizeHint());
    }

    void FileBrowserShortcuts::_widgetUpdate()
    {
        DTK_P();

        std::vector<ListItem> items;
        for (const auto& drive : p.drives)
        {
            items.push_back(ListItem(drive.u8string(), drive.u8string()));
        }
        p.listWidgets["Drives"]->setItems(items);

        p.shortcuts.clear();
        items.clear();
        std::filesystem::path path = std::filesystem::current_path();
        p.shortcuts.push_back(path);
        items.push_back(ListItem("Current", path.u8string()));
        for (auto userPath : getUserPathEnums())
        {
            path = getUserPath(userPath);
            p.shortcuts.push_back(path);
            items.push_back(ListItem(path.filename().u8string(), path.u8string()));
        }
        p.listWidgets["Shortcuts"]->setItems(items);

        items.clear();
        for (const auto& recent : p.recent)
        {
            items.push_back(ListItem(recent.filename().u8string(), recent.u8string()));
        }
        p.listWidgets["Recent"]->setItems(items);
    }
}