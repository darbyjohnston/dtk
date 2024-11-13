// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/ConfirmDialog.h>

#include <dtk/ui/Divider.h>
#include <dtk/ui/Label.h>
#include <dtk/ui/PushButton.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/Spacer.h>

namespace dtk
{
    class ConfirmDialogWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent);

        ConfirmDialogWidget();

    public:
        virtual ~ConfirmDialogWidget();

        static std::shared_ptr<ConfirmDialogWidget> create(
            const std::shared_ptr<Context>&,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setCallback(const std::function<void(bool)>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        std::shared_ptr<Label> _titleLabel;
        std::shared_ptr<Label> _label;
        std::shared_ptr<PushButton> _okButton;
        std::shared_ptr<PushButton> _cancelButton;
        std::shared_ptr<VerticalLayout> _layout;
        std::function<void(bool)> _callback;
    };

    void ConfirmDialogWidget::_init(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::ConfirmDialogWidget", parent);

        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);

        _titleLabel = Label::create(context, title);
        _titleLabel->setMarginRole(SizeRole::MarginSmall);
        _titleLabel->setBackgroundRole(ColorRole::Button);

        _label = Label::create(context, text);
        _label->setMarginRole(SizeRole::MarginSmall);
        _label->setAlign(HAlign::Center, VAlign::Top);

        _okButton = PushButton::create(context, "OK");
        _cancelButton = PushButton::create(context, "Cancel");

        _layout = VerticalLayout::create(context, shared_from_this());
        _layout->setSpacingRole(SizeRole::None);
        _titleLabel->setParent(_layout);
        Divider::create(context, Orientation::Vertical, _layout);
        auto vLayout = VerticalLayout::create(context, _layout);
        vLayout->setMarginRole(SizeRole::MarginSmall);
        vLayout->setSpacingRole(SizeRole::SpacingSmall);
        _label->setParent(vLayout);
        auto hLayout = HorizontalLayout::create(context, vLayout);
        hLayout->setSpacingRole(SizeRole::None);
        auto spacer = Spacer::create(context, Orientation::Horizontal, hLayout);
        spacer->setHStretch(Stretch::Expanding);
        _okButton->setParent(hLayout);
        _cancelButton->setParent(hLayout);

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
        const int sa = event.style->getSizeRole(SizeRole::ScrollArea, event.displayScale);
        Size2I sizeHint = _layout->getSizeHint();
        sizeHint.w = std::max(sizeHint.w, sa);
        _setSizeHint(sizeHint);
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
}