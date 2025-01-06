// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/FileBrowserPrivate.h>

#include <dtk/ui/ComboBox.h>
#include <dtk/ui/Divider.h>
#include <dtk/ui/Label.h>
#include <dtk/ui/PushButton.h>
#include <dtk/ui/RecentFilesModel.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/SearchBox.h>
#include <dtk/ui/ScrollWidget.h>
#include <dtk/ui/Spacer.h>
#include <dtk/ui/Splitter.h>
#include <dtk/ui/ToolButton.h>

#include <dtk/core/Format.h>

#include <filesystem>
#include <sstream>

namespace dtk
{
    struct FileBrowserWidget::Private
    {
        std::vector<std::filesystem::path> paths;
        int currentPath = -1;
        std::shared_ptr<ObservableValue<FileBrowserOptions> > options;
        std::vector<std::string> extensions;
        std::shared_ptr<RecentFilesModel> recentFilesModel;

        std::shared_ptr<Label> titleLabel;
        std::shared_ptr<ToolButton> leftPanelButton;
        std::shared_ptr<ToolButton> upButton;
        std::shared_ptr<ToolButton> forwardButton;
        std::shared_ptr<ToolButton> backButton;
        std::shared_ptr<ToolButton> reloadButton;
        std::shared_ptr<FileBrowserPath> pathWidget;
        std::shared_ptr<FileBrowserShortcuts> shortcutsWidget;
        std::shared_ptr<ScrollWidget> shortcutsScrollWidget;
        std::shared_ptr<FileBrowserView> view;
        std::shared_ptr<ScrollWidget> viewScrollWidget;
        std::shared_ptr<SearchBox> searchBox;
        std::shared_ptr<ComboBox> extensionsComboBox;
        std::shared_ptr<ComboBox> sortComboBox;
        std::shared_ptr<ToolButton> reverseSortButton;
        std::shared_ptr<PushButton> okButton;
        std::shared_ptr<PushButton> cancelButton;
        std::shared_ptr<Splitter> splitter;
        std::shared_ptr<VerticalLayout> layout;

        std::function<void(const std::filesystem::path&)> callback;
        std::function<void(void)> cancelCallback;

        std::shared_ptr<ValueObserver<int> > currentObserver;
    };

    void FileBrowserWidget::_init(
        const std::shared_ptr<Context>& context,
        const std::filesystem::path& path,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::FileBrowserWidget", parent);
        DTK_P();

        setHStretch(Stretch::Expanding);
        setVStretch(Stretch::Expanding);
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);

        p.paths.push_back(path);
        p.currentPath = 0;
        p.options = ObservableValue<FileBrowserOptions>::create();

        p.titleLabel = Label::create(context, "File Browser");
        p.titleLabel->setMarginRole(SizeRole::MarginSmall);
        p.titleLabel->setBackgroundRole(ColorRole::Button);

        p.leftPanelButton = ToolButton::create(context);
        p.leftPanelButton->setCheckable(true);
        p.leftPanelButton->setIcon("PanelLeft");
        p.leftPanelButton->setTooltip("Toggle the left panel");

        p.upButton = ToolButton::create(context);
        p.upButton->setIcon("DirectoryUp");
        p.upButton->setRepeatClick(true);
        p.upButton->setTooltip("Go up a directory");

        p.backButton = ToolButton::create(context);
        p.backButton->setIcon("DirectoryBack");
        p.backButton->setRepeatClick(true);
        p.backButton->setTooltip("Go back a directory");

        p.forwardButton = ToolButton::create(context);
        p.forwardButton->setIcon("DirectoryForward");
        p.forwardButton->setRepeatClick(true);
        p.forwardButton->setTooltip("Go forward a directory");

        p.reloadButton = ToolButton::create(context);
        p.reloadButton->setIcon("Reload");
        p.reloadButton->setTooltip("Reload the current directory");

        p.pathWidget = FileBrowserPath::create(context);
        p.pathWidget->setTooltip("Current directory");

        p.shortcutsWidget = FileBrowserShortcuts::create(context);
        p.shortcutsScrollWidget = ScrollWidget::create(context);
        p.shortcutsScrollWidget->setWidget(p.shortcutsWidget);
        p.shortcutsScrollWidget->setVStretch(Stretch::Expanding);

        p.view = FileBrowserView::create(context);
        p.viewScrollWidget = ScrollWidget::create(context);
        p.viewScrollWidget->setWidget(p.view);
        p.viewScrollWidget->setVStretch(Stretch::Expanding);

        p.searchBox = SearchBox::create(context);
        p.searchBox->setTooltip("Filter");

        p.extensionsComboBox = ComboBox::create(context);
        p.extensionsComboBox->setTooltip("Filter by extension");

        p.sortComboBox = ComboBox::create(context, getFileBrowserSortLabels());
        p.sortComboBox->setTooltip("Sorting");

        p.reverseSortButton = ToolButton::create(context);
        p.reverseSortButton->setCheckable(true);
        p.reverseSortButton->setIcon("ReverseSort");
        p.reverseSortButton->setTooltip("Reverse sorting");

        p.okButton = PushButton::create(context);
        p.okButton->setText("Ok");

        p.cancelButton = PushButton::create(context);
        p.cancelButton->setText("Cancel");

        p.layout = VerticalLayout::create(context, shared_from_this());
        p.layout->setSpacingRole(SizeRole::None);
        p.titleLabel->setParent(p.layout);
        Divider::create(context, Orientation::Vertical, p.layout);
        auto vLayout = VerticalLayout::create(context, p.layout);
        vLayout->setSpacingRole(SizeRole::SpacingSmall);
        vLayout->setMarginRole(SizeRole::MarginSmall);
        vLayout->setVStretch(Stretch::Expanding);
        auto hLayout = HorizontalLayout::create(context, vLayout);
        hLayout->setSpacingRole(SizeRole::SpacingTool);
        hLayout->setVAlign(VAlign::Center);
        p.leftPanelButton->setParent(hLayout);
        p.upButton->setParent(hLayout);
        p.backButton->setParent(hLayout);
        p.forwardButton->setParent(hLayout);
        p.reloadButton->setParent(hLayout);
        p.pathWidget->setParent(hLayout);
        p.splitter = Splitter::create(context, Orientation::Horizontal, vLayout);
        p.splitter->setSplit({ 0.2 });
        p.shortcutsScrollWidget->setParent(p.splitter);
        p.viewScrollWidget->setParent(p.splitter);
        hLayout = HorizontalLayout::create(context, vLayout);
        hLayout->setSpacingRole(SizeRole::SpacingSmall);
        p.searchBox->setParent(hLayout);
        p.extensionsComboBox->setParent(hLayout);
        p.sortComboBox->setParent(hLayout);
        p.reverseSortButton->setParent(hLayout);
        auto spacer = Spacer::create(context, Orientation::Horizontal, hLayout);
        spacer->setSpacingRole(SizeRole::None);
        spacer->setHStretch(Stretch::Expanding);
        p.okButton->setParent(hLayout);
        p.cancelButton->setParent(hLayout);

        _pathUpdate();
        _optionsUpdate();

        p.leftPanelButton->setCheckedCallback(
            [this](bool value)
            {
                DTK_P();
                FileBrowserOptions options = p.options->get();
                options.leftPanel = value;
                if (p.options->setIfChanged(options))
                {
                    p.view->setOptions(options);
                    _optionsUpdate();
                }
            });

        p.upButton->setClickedCallback(
            [this]
            {
                if (_p->currentPath >= 0 && _p->currentPath < _p->paths.size())
                {

                    const std::filesystem::path path(_p->paths[_p->currentPath]);
                    const std::filesystem::path parentPath(path.parent_path());
                    if (parentPath != path)
                    {
                        _setPath(parentPath.string());
                    }
                }
            });

        p.backButton->setClickedCallback(
            [this]
            {
                if (_p->currentPath >= 1)
                {
                    --_p->currentPath;
                    _pathUpdate();
                }
            });

        p.forwardButton->setClickedCallback(
            [this]
            {
                if (_p->currentPath < static_cast<int>(_p->paths.size()) - 1)
                {
                    ++_p->currentPath;
                    _pathUpdate();
                }
            });

        p.reloadButton->setClickedCallback(
            [this]
            {
                _p->view->reload();
            });

        p.pathWidget->setCallback(
            [this](const std::filesystem::path& value)
            {
                _setPath(value);
            });
        p.pathWidget->setEditCallback(
            [this](bool value)
            {
                DTK_P();
                FileBrowserOptions options = p.options->get();
                options.pathEdit = value;
                if (p.options->setIfChanged(options))
                {
                    p.view->setOptions(options);
                    _optionsUpdate();
                }
            });

        p.shortcutsWidget->setCallback(
            [this](const std::filesystem::path& value)
            {
                _setPath(value);
            });

        p.view->setCallback(
            [this](const std::filesystem::path& value)
            {
                DTK_P();
                if (std::filesystem::is_directory(value))
                {
                    _setPath(value);
                }
                else
                {
                    if (p.recentFilesModel)
                    {
                        p.recentFilesModel->addRecent(value);
                    }
                    if (p.callback)
                    {
                        p.callback(value);
                    }
                }
            });

        p.searchBox->setCallback(
            [this](const std::string& value)
            {
                DTK_P();
                FileBrowserOptions options = p.options->get();
                options.search = value;
                if (p.options->setIfChanged(options))
                {
                    p.view->setOptions(options);
                    _optionsUpdate();
                }
            });

        p.extensionsComboBox->setIndexCallback(
            [this](int value)
            {
                DTK_P();
                if (value >= 0 && value < p.extensions.size())
                {
                    FileBrowserOptions options = p.options->get();
                    options.extension = p.extensions[value];
                    if (p.options->setIfChanged(options))
                    {
                        p.view->setOptions(options);
                        _optionsUpdate();
                    }
                }
            });

        p.sortComboBox->setIndexCallback(
            [this](int value)
            {
                DTK_P();
                FileBrowserOptions options = p.options->get();
                options.sort = static_cast<FileBrowserSort>(value);
                if (p.options->setIfChanged(options))
                {
                    p.view->setOptions(options);
                    _optionsUpdate();
                }
            });

        p.reverseSortButton->setCheckedCallback(
            [this](bool value)
            {
                DTK_P();
                FileBrowserOptions options = p.options->get();
                options.reverseSort = value;
                if (p.options->setIfChanged(options))
                {
                    p.view->setOptions(options);
                    _optionsUpdate();
                }
            });

        p.okButton->setClickedCallback(
            [this]
            {
                DTK_P();
                if (p.currentPath >= 0 && p.currentPath < p.paths.size())
                {
                    if (p.recentFilesModel)
                    {
                        p.recentFilesModel->addRecent(p.paths[p.currentPath]);
                    }
                    if (p.callback)
                    {
                        p.callback(p.paths[p.currentPath]);
                    }
                }
            });

        p.cancelButton->setClickedCallback(
            [this]
            {
                DTK_P();
                if (p.cancelCallback)
                {
                    p.cancelCallback();
                }
            });

        p.currentObserver = ValueObserver<int>::create(
            p.view->observeCurrent(),
            [this](int value)
            {
                if (value >= 0)
                {
                    const Box2I r = _p->view->getRect(value);
                    _p->viewScrollWidget->scrollTo(r);
                }
            });
    }

    FileBrowserWidget::FileBrowserWidget() :
        _p(new Private)
    {}

    FileBrowserWidget::~FileBrowserWidget()
    {
        DTK_P();
    }

    std::shared_ptr<FileBrowserWidget> FileBrowserWidget::create(
        const std::shared_ptr<Context>& context,
        const std::filesystem::path& path,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<FileBrowserWidget>(new FileBrowserWidget);
        out->_init(context, path, parent);
        return out;
    }

    void FileBrowserWidget::setCallback(const std::function<void(const std::filesystem::path&)>& value)
    {
        _p->callback = value;
    }

    void FileBrowserWidget::setCancelCallback(const std::function<void(void)>& value)
    {
        _p->cancelCallback = value;
    }

    std::filesystem::path FileBrowserWidget::getPath() const
    {
        DTK_P();
        return p.currentPath >= 0 && p.currentPath < p.paths.size() ?
            p.paths[p.currentPath] :
            std::filesystem::path();
    }

    const FileBrowserOptions& FileBrowserWidget::getOptions() const
    {
        return _p->options->get();
    }

    std::shared_ptr<IObservableValue<FileBrowserOptions> > FileBrowserWidget::observeOptions() const
    {
        return _p->options;
    }

    void FileBrowserWidget::setOptions(const FileBrowserOptions& value)
    {
        DTK_P();
        if (p.options->setIfChanged(value))
        {
            _optionsUpdate();
        }
    }

    const std::shared_ptr<RecentFilesModel>& FileBrowserWidget::getRecentFilesModel() const
    {
        return _p->recentFilesModel;
    }

    void FileBrowserWidget::setRecentFilesModel(const std::shared_ptr<RecentFilesModel>& value)
    {
        DTK_P();
        p.recentFilesModel = value;
        p.shortcutsWidget->setRecentFilesModel(value);
    }

    void FileBrowserWidget::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->layout->setGeometry(value);
    }

    void FileBrowserWidget::sizeHintEvent(const SizeHintEvent& value)
    {
        IWidget::sizeHintEvent(value);
        _setSizeHint(_p->layout->getSizeHint());
    }

    void FileBrowserWidget::_setPath(const std::filesystem::path& value)
    {
        DTK_P();
        while (p.currentPath < static_cast<int>(p.paths.size()) - 1)
        {
            p.paths.pop_back();
        }
        if (p.paths.empty() ||
            (!p.paths.empty() && value != p.paths[p.paths.size() - 1]))
        {
            p.paths.push_back(value);
            p.currentPath++;
            _pathUpdate();
        }
    }

    void FileBrowserWidget::_pathUpdate()
    {
        DTK_P();
        p.backButton->setEnabled(p.currentPath > 0);
        p.forwardButton->setEnabled(p.currentPath < static_cast<int>(p.paths.size()) - 1);
        const std::filesystem::path path = getPath();
        p.pathWidget->setPath(path);
        p.view->setPath(path);
        p.viewScrollWidget->setScrollPos(V2I());
    }

    void FileBrowserWidget::_optionsUpdate()
    {
        DTK_P();
        const FileBrowserOptions options = p.options->get();

        p.leftPanelButton->setChecked(options.leftPanel);
        p.shortcutsScrollWidget->setVisible(options.leftPanel);

        p.pathWidget->setEdit(options.pathEdit);

        p.view->setOptions(options);
        p.searchBox->setText(options.search);

        std::vector<std::string> extensionsLabels;
        p.extensions.clear();
        p.extensions.push_back(std::string());
        extensionsLabels.push_back("*.*");
        for (const auto& extension : options.extensions)
        {
            p.extensions.push_back(extension);
            extensionsLabels.push_back("*" + extension);
        }
        p.extensionsComboBox->setItems(extensionsLabels);
        const auto i = std::find(
            p.extensions.begin(),
            p.extensions.end(),
            options.extension);
        if (i != p.extensions.end())
        {
            p.extensionsComboBox->setCurrentIndex(i - p.extensions.begin());
        }

        p.sortComboBox->setCurrentIndex(static_cast<int>(options.sort));
        p.reverseSortButton->setChecked(options.reverseSort);
    }
}