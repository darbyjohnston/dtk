// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/SearchBox.h>

#include <feather-tk/ui/LineEdit.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/ToolButton.h>

namespace feather_tk
{
    struct SearchBox::Private
    {
        std::shared_ptr<LineEdit> lineEdit;
        std::shared_ptr<ToolButton> button;
        std::shared_ptr<HorizontalLayout> layout;

        std::function<void(const std::string&)> callback;
    };

    void SearchBox::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "feather_tk::SearchBox", parent);
        FEATHER_TK_P();

        p.lineEdit = LineEdit::create(context);
        p.lineEdit->setHStretch(Stretch::Expanding);

        p.button = ToolButton::create(context);

        p.layout = HorizontalLayout::create(context, shared_from_this());
        p.layout->setSpacingRole(SizeRole::SpacingTool);
        p.lineEdit->setParent(p.layout);
        p.button->setParent(p.layout);

        _widgetUpdate();

        p.lineEdit->setTextChangedCallback(
            [this](const std::string& value)
            {
                _widgetUpdate();
                if (_p->callback)
                {
                    _p->callback(value);
                }
            });

        p.button->setClickedCallback(
            [this]
            {
                _p->lineEdit->clearText();
                _widgetUpdate();
                if (_p->callback)
                {
                    _p->callback(std::string());
                }
            });
    }

    SearchBox::SearchBox() :
        _p(new Private)
    {}

    SearchBox::~SearchBox()
    {}

    std::shared_ptr<SearchBox> SearchBox::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<SearchBox>(new SearchBox);
        out->_init(context, parent);
        return out;
    }

    const std::string& SearchBox::getText() const
    {
        return _p->lineEdit->getText();
    }

    void SearchBox::setText(const std::string& value)
    {
        _p->lineEdit->setText(value);
        _widgetUpdate();
    }

    void SearchBox::setCallback(const std::function<void(const std::string&)>& value)
    {
        _p->callback = value;
    }

    void SearchBox::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->layout->setGeometry(value);
    }

    void SearchBox::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->layout->getSizeHint());
    }

    void SearchBox::_widgetUpdate()
    {
        FEATHER_TK_P();
        const std::string& text = p.lineEdit->getText();
        p.button->setIcon(!text.empty() ? "Clear" : "Search");
        p.button->setEnabled(!text.empty());
    }
}