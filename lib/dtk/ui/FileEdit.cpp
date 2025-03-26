// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/FileEdit.h>

#include <dtk/ui/LineEdit.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/ToolButton.h>

namespace dtk
{
    struct FileEdit::Private
    {
        FileBrowserMode mode = FileBrowserMode::File;
        std::filesystem::path path;
        FileBrowserOptions options;
        std::vector<std::string> extensions;
        std::string currentExtension;
        std::shared_ptr<RecentFilesModel> recentFilesModel;

        std::shared_ptr<LineEdit> lineEdit;
        std::shared_ptr<ToolButton> browseButton;
        std::shared_ptr<HorizontalLayout> layout;

        std::function<void(const std::filesystem::path&)> callback;
    };

    void FileEdit::_init(
        const std::shared_ptr<Context>& context,
        FileBrowserMode mode,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::FileEdit", parent);
        DTK_P();

        setHStretch(Stretch::Expanding);

        p.mode = mode;

        p.lineEdit = LineEdit::create(context);
        p.lineEdit->setHStretch(Stretch::Expanding);

        p.browseButton = ToolButton::create(context);
        p.browseButton->setIcon("FileBrowser");
        p.browseButton->setTooltip("Open the file browser");

        p.layout = HorizontalLayout::create(context, shared_from_this());
        p.layout->setSpacingRole(SizeRole::SpacingTool);
        p.lineEdit->setParent(p.layout);
        p.browseButton->setParent(p.layout);

        _widgetUpdate();

        p.lineEdit->setTextCallback(
            [this](const std::string& value)
            {
                _p->path = value;
                if (_p->callback)
                {
                    _p->callback(_p->path);
                }
            });
        p.lineEdit->setTextChangedCallback(
            [this](const std::string&)
            {
                _widgetUpdate();
            });

        p.browseButton->setClickedCallback(
            [this]
            {
                _openDialog();
            });
    }

    FileEdit::FileEdit() :
        _p(new Private)
    {}

    FileEdit::~FileEdit()
    {}

    std::shared_ptr<FileEdit> FileEdit::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<FileEdit>(new FileEdit);
        out->_init(context, FileBrowserMode::File, parent);
        return out;
    }

    std::shared_ptr<FileEdit> FileEdit::create(
        const std::shared_ptr<Context>& context,
        FileBrowserMode mode,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<FileEdit>(new FileEdit);
        out->_init(context, mode, parent);
        return out;
    }

    const std::filesystem::path& FileEdit::getPath() const
    {
        return _p->path;
    }

    void FileEdit::setPath(const std::filesystem::path& value)
    {
        DTK_P();
        if (value == p.path)
            return;
        p.path = value;
        p.lineEdit->setText(value.u8string());
        _widgetUpdate();
    }

    void FileEdit::setCallback(const std::function<void(const std::filesystem::path&)>& value)
    {
        _p->callback = value;
    }

    void FileEdit::setOptions(const FileBrowserOptions& value)
    {
        _p->options = value;
    }

    void FileEdit::setExtensions(
        const std::vector<std::string>& extensions,
        const std::string& current)
    {
        DTK_P();
        p.extensions = extensions;
        p.currentExtension = current;
    }

    void FileEdit::setRecentFilesModel(const std::shared_ptr<RecentFilesModel>& value)
    {
        _p->recentFilesModel = value;
    }

    void FileEdit::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->layout->setGeometry(value);
    }

    void FileEdit::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->layout->getSizeHint());
    }

    void FileEdit::_openDialog()
    {
        DTK_P();
        if (auto context = getContext())
        {
            if (auto fileBrowserSystem = context->getSystem<FileBrowserSystem>())
            {
                fileBrowserSystem->setOptions(p.options);
                fileBrowserSystem->setExtensions(p.extensions, p.currentExtension);
                fileBrowserSystem->open(
                    getWindow(),
                    [this](const std::filesystem::path& value)
                    {
                        DTK_P();
                        p.path = value;
                        p.lineEdit->setText(p.path.u8string());
                        _widgetUpdate();
                        if (p.callback)
                        {
                            p.callback(p.path);
                        }
                    },
                    p.mode,
                    p.recentFilesModel);
            }
        }
    }

    void FileEdit::_widgetUpdate()
    {
        DTK_P();
        const std::string& text = p.lineEdit->getText();
        p.lineEdit->setTooltip(text);
    }
}