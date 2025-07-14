// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/BellowsPrivate.h>

#include <feather-tk/ui/Divider.h>
#include <feather-tk/ui/RowLayout.h>

namespace feather_tk
{
    struct Bellows::Private
    {
        std::shared_ptr<BellowsButton> button;
        std::shared_ptr<IWidget> widget;
        std::shared_ptr<IWidget> toolWidget;
        std::shared_ptr<HorizontalLayout> buttonLayout;
        std::shared_ptr<VerticalLayout> layout;
        std::function<void(bool)> openCallback;
    };

    void Bellows::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "feather_tk::Bellows", parent);
        FEATHER_TK_P();

        p.button = BellowsButton::create(context);
        p.button->setCheckable(true);
        p.button->setIcon("BellowsClosed");
        p.button->setCheckedIcon("BellowsOpen");
        p.button->setHStretch(Stretch::Expanding);

        p.buttonLayout = HorizontalLayout::create(context);
        p.buttonLayout->setSpacingRole(SizeRole::None);
        p.button->setParent(p.buttonLayout);

        p.layout = VerticalLayout::create(context, shared_from_this());
        p.layout->setSpacingRole(SizeRole::None);
        p.buttonLayout->setParent(p.layout);
        Divider::create(context, Orientation::Vertical, p.layout);

        p.button->setCheckedCallback(
            [this](bool value)
            {
                setOpen(value);
            });
    }

    Bellows::Bellows() :
        _p(new Private)
    {}

    Bellows::~Bellows()
    {}

    std::shared_ptr<Bellows> Bellows::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<Bellows>(new Bellows);
        out->_init(context, parent);
        return out;
    }

    std::shared_ptr<Bellows> Bellows::create(
        const std::shared_ptr<Context>& context,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = create(context, parent);
        out->setText(text);
        return out;
    }

    const std::string& Bellows::getText() const
    {
        return _p->button->getText();
    }

    void Bellows::setText(const std::string& value)
    {
        _p->button->setText(value);
    }

    const std::shared_ptr<IWidget>& Bellows::getWidget() const
    {
        return _p->widget;
    }

    void Bellows::setWidget(const std::shared_ptr<IWidget>& value)
    {
        FEATHER_TK_P();
        if (value == p.widget)
            return;
        if (p.widget)
        {
            p.widget->setParent(nullptr);
        }
        p.widget = value;
        if (p.widget)
        {
            p.widget->setParent(_p->layout);
            p.widget->setVisible(p.button->isChecked());
        }
        _setSizeUpdate();
        _setDrawUpdate();
    }

    bool Bellows::isOpen() const
    {
        return _p->button->isChecked();
    }

    void Bellows::setOpen(bool value)
    {
        FEATHER_TK_P();
        p.button->setChecked(value);
        if (p.widget)
        {
            p.widget->setVisible(value);
            if (p.openCallback)
            {
                p.openCallback(value);
            }
        }
    }

    void Bellows::setOpenCallback(const std::function<void(bool)>& value)
    {
        _p->openCallback = value;
    }

    const std::shared_ptr<IWidget>& Bellows::getToolWidget() const
    {
        return _p->toolWidget;
    }

    void Bellows::setToolWidget(const std::shared_ptr<IWidget>& value)
    {
        FEATHER_TK_P();
        if (p.toolWidget)
        {
            p.toolWidget->setParent(nullptr);
        }
        p.toolWidget = value;
        if (p.toolWidget)
        {
            p.toolWidget->setParent(p.buttonLayout);
        }
    }

    void Bellows::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->layout->setGeometry(value);
    }

    void Bellows::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->layout->getSizeHint());
    }
}