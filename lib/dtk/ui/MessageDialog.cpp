// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/MessageDialogPrivate.h>

#include <dtk/ui/Divider.h>
#include <dtk/ui/Spacer.h>
#include <dtk/ui/ScrollWidget.h>

namespace dtk
{
    void MessageDialogWidget::_init(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::MessageDialogWidget", parent);

        setHStretch(Stretch::Expanding);
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);

        _titleLabel = Label::create(context, title);
        _titleLabel->setMarginRole(SizeRole::MarginSmall);
        _titleLabel->setBackgroundRole(ColorRole::Button);

        _label = Label::create(context, text);
        _label->setMarginRole(SizeRole::MarginSmall);

        _okButton = PushButton::create(context, "OK");

        _layout = VerticalLayout::create(context, shared_from_this());
        _layout->setSpacingRole(SizeRole::None);
        _titleLabel->setParent(_layout);
        Divider::create(context, Orientation::Vertical, _layout);
        auto vLayout = VerticalLayout::create(context, _layout);
        vLayout->setMarginRole(SizeRole::MarginSmall);
        vLayout->setSpacingRole(SizeRole::SpacingSmall);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Horizontal, vLayout);
        scrollWidget->setWidget(_label);
        auto hLayout = HorizontalLayout::create(context, vLayout);
        hLayout->setSpacingRole(SizeRole::None);
        auto spacer = Spacer::create(context, Orientation::Horizontal, hLayout);
        spacer->setHStretch(Stretch::Expanding);
        _okButton->setParent(hLayout);

        _okButton->setClickedCallback(
            [this]
            {
                if (_callback)
                {
                    _callback();
                }
            });
    }

    MessageDialogWidget::MessageDialogWidget()
    {}

    MessageDialogWidget::~MessageDialogWidget()
    {}

    std::shared_ptr<MessageDialogWidget> MessageDialogWidget::create(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<MessageDialogWidget>(new MessageDialogWidget);
        out->_init(context, title, text, parent);
        return out;
    }

    void MessageDialogWidget::setCallback(const std::function<void(void)>& value)
    {
        _callback = value;
    }

    void MessageDialogWidget::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _layout->setGeometry(value);
    }

    void MessageDialogWidget::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_layout->getSizeHint());
    }

    void ConfirmDialogWidget::_init(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::ConfirmDialogWidget", parent);

        setHStretch(Stretch::Expanding);
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);

        _titleLabel = Label::create(context, title);
        _titleLabel->setMarginRole(SizeRole::MarginSmall);
        _titleLabel->setBackgroundRole(ColorRole::Button);

        _label = Label::create(context, text);
        _label->setMarginRole(SizeRole::MarginSmall);

        _okButton = PushButton::create(context, "OK");
        _cancelButton = PushButton::create(context, "Cancel");

        _layout = VerticalLayout::create(context, shared_from_this());
        _layout->setSpacingRole(SizeRole::None);
        _titleLabel->setParent(_layout);
        Divider::create(context, Orientation::Vertical, _layout);
        auto vLayout = VerticalLayout::create(context, _layout);
        vLayout->setMarginRole(SizeRole::MarginSmall);
        vLayout->setSpacingRole(SizeRole::SpacingSmall);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Horizontal, vLayout);
        scrollWidget->setWidget(_label);
        auto hLayout = HorizontalLayout::create(context, vLayout);
        hLayout->setSpacingRole(SizeRole::None);
        _cancelButton->setParent(hLayout);
        auto spacer = Spacer::create(context, Orientation::Horizontal, hLayout);
        spacer->setHStretch(Stretch::Expanding);
        _okButton->setParent(hLayout);

        _okButton->setClickedCallback(
            [this]
            {
                if (_callback)
                {
                    _callback(true);
                }
            });

        _cancelButton->setClickedCallback(
            [this]
            {
                if (_callback)
                {
                    _callback(false);
                }
            });
    }

    ConfirmDialogWidget::ConfirmDialogWidget()
    {}

    ConfirmDialogWidget::~ConfirmDialogWidget()
    {}

    std::shared_ptr<ConfirmDialogWidget> ConfirmDialogWidget::create(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ConfirmDialogWidget>(new ConfirmDialogWidget);
        out->_init(context, title, text, parent);
        return out;
    }

    void ConfirmDialogWidget::setCallback(const std::function<void(bool)>& value)
    {
        _callback = value;
    }

    void ConfirmDialogWidget::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _layout->setGeometry(value);
    }

    void ConfirmDialogWidget::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_layout->getSizeHint());
    }

    struct MessageDialog::Private
    {
        std::shared_ptr<MessageDialogWidget> widget;

        std::function<void(void)> callback;
    };

    void MessageDialog::_init(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        IDialog::_init(context, "dtk::MessageDialog", parent);
        DTK_P();

        p.widget = MessageDialogWidget::create(context, title, text, shared_from_this());

        p.widget->setCallback(
            [this]
            {
                if (_p->callback)
                {
                    _p->callback();
                }
            });
    }

    MessageDialog::MessageDialog() :
        _p(new Private)
    {}

    MessageDialog::~MessageDialog()
    {}

    std::shared_ptr<MessageDialog> MessageDialog::create(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<MessageDialog>(new MessageDialog);
        out->_init(context, title, text, parent);
        return out;
    }

    void MessageDialog::setCallback(const std::function<void(void)>& value)
    {
        _p->callback = value;
    }

    struct ConfirmDialog::Private
    {
        std::shared_ptr<ConfirmDialogWidget> widget;

        std::function<void(bool)> callback;
    };

    void ConfirmDialog::_init(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        IDialog::_init(context, "dtk::ConfirmDialog", parent);
        DTK_P();

        p.widget = ConfirmDialogWidget::create(context, title, text, shared_from_this());

        p.widget->setCallback(
            [this](bool value)
            {
                if (_p->callback)
                {
                    _p->callback(value);
                }
            });
    }

    ConfirmDialog::ConfirmDialog() :
        _p(new Private)
    {}

    ConfirmDialog::~ConfirmDialog()
    {}

    std::shared_ptr<ConfirmDialog> ConfirmDialog::create(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ConfirmDialog>(new ConfirmDialog);
        out->_init(context, title, text, parent);
        return out;
    }

    void ConfirmDialog::setCallback(const std::function<void(bool)>& value)
    {
        _p->callback = value;
    }

    struct MessageDialogSystem::Private
    {
        std::shared_ptr<MessageDialog> messageDialog;
        std::shared_ptr<ConfirmDialog> confirmDialog;
    };

    MessageDialogSystem::MessageDialogSystem(const std::shared_ptr<Context>& context) :
        ISystem(context, "dtk::MessageDialogSystem"),
        _p(new Private)
    {}

    MessageDialogSystem::~MessageDialogSystem()
    {}

    std::shared_ptr<MessageDialogSystem> MessageDialogSystem::create(const std::shared_ptr<Context>& context)
    {
        return std::shared_ptr<MessageDialogSystem>(new MessageDialogSystem(context));
    }

    void MessageDialogSystem::message(
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWindow>& window)
    {
        DTK_P();
        if (auto context = _context.lock())
        {
            p.messageDialog = MessageDialog::create(context, title, text);
            p.messageDialog->open(window);
            p.messageDialog->setCallback(
                [this]
                {
                    _p->messageDialog->close();
                });
            p.messageDialog->setCloseCallback(
                [this]
                {
                    _p->messageDialog.reset();
                });
        }
    }

    void MessageDialogSystem::confirm(
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWindow>& window,
        const std::function<void(bool)>& callback)
    {
        DTK_P();
        if (auto context = _context.lock())
        {
            p.confirmDialog = ConfirmDialog::create(context, title, text);
            p.confirmDialog->open(window);
            p.confirmDialog->setCallback(
                [this, callback](bool value)
                {
                    callback(value);
                    _p->confirmDialog->close();
                });
            p.confirmDialog->setCloseCallback(
                [this]
                {
                    _p->confirmDialog.reset();
                });
        }
    }
}