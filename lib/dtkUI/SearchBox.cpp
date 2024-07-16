// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUI/SearchBox.h>

#include <dtkUI/LineEdit.h>
#include <dtkUI/RowLayout.h>
#include <dtkUI/ToolButton.h>

using namespace dtk::core;

namespace dtk
{
    namespace ui
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
            IWidget::_init(context, "dtk::ui::SearchBox", parent);
            DTK_P();

            p.lineEdit = LineEdit::create(context);
            p.lineEdit->setHStretch(Stretch::Expanding);

            p.button = ToolButton::create(context);
            p.button->setIcon("Clear");

            p.layout = HorizontalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::SpacingSmall);
            p.lineEdit->setParent(p.layout);
            p.button->setParent(p.layout);

            _textUpdate();
            
            p.lineEdit->setTextChangedCallback(
                [this](const std::string& value)
                {
                    _textUpdate();
                    if (_p->callback)
                    {
                        _p->callback(value);
                    }
                });

            p.button->setClickedCallback(
                [this]
                {
                    _p->lineEdit->clearText();
                    _textUpdate();
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
            _textUpdate();
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
        
        void SearchBox::_textUpdate()
        {
            DTK_P();
            const std::string& text = p.lineEdit->getText();
            p.button->setEnabled(!text.empty());
       }
    }
}
