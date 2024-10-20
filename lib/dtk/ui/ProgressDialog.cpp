// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/ProgressDialog.h>

#include <dtk/ui/Divider.h>
#include <dtk/ui/Label.h>
#include <dtk/ui/PushButton.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/Spacer.h>

namespace dtk
{
    class ProgressDialogWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent);

        ProgressDialogWidget();

    public:
        virtual ~ProgressDialogWidget();

        static std::shared_ptr<ProgressDialogWidget> create(
            const std::shared_ptr<Context>&,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

        void setCancelCallback(const std::function<void(void)>&);

    private:
        std::shared_ptr<Label> _titleLabel;
        std::shared_ptr<Label> _label;
        std::shared_ptr<PushButton> _cancelButton;
        std::shared_ptr<VerticalLayout> _layout;
        std::function<void(void)> _cancelCallback;
    };

    void ProgressDialogWidget::_init(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::ProgressDialogWidget", parent);

        setHStretch(Stretch::Expanding);
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);

        _titleLabel = Label::create(context, title);
        _titleLabel->setMarginRole(SizeRole::MarginSmall);
        _titleLabel->setBackgroundRole(ColorRole::Button);

        _label = Label::create(context, text);
        _label->setMarginRole(SizeRole::MarginSmall);
        _label->setVAlign(VAlign::Top);

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
        _cancelButton->setParent(hLayout);

        _cancelButton->setClickedCallback(
            [this]
            {
                if (_cancelCallback)
                {
                    _cancelCallback();
                }
            });
    }

    ProgressDialogWidget::ProgressDialogWidget()
    {}

    ProgressDialogWidget::~ProgressDialogWidget()
    {}

    std::shared_ptr<ProgressDialogWidget> ProgressDialogWidget::create(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ProgressDialogWidget>(new ProgressDialogWidget);
        out->_init(context, title, text, parent);
        return out;
    }

    void ProgressDialogWidget::setCancelCallback(const std::function<void(void)>& value)
    {
        _cancelCallback = value;
    }

    void ProgressDialogWidget::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _layout->setGeometry(value);
    }

    void ProgressDialogWidget::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_layout->getSizeHint());
    }

    struct ProgressDialog::Private
    {
        std::shared_ptr<ProgressDialogWidget> widget;

        std::function<void(void)> cancelCallback;
    };

    void ProgressDialog::_init(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        IDialog::_init(context, "dtk::ProgressDialog", parent);
        DTK_P();

        p.widget = ProgressDialogWidget::create(context, title, text, shared_from_this());

        p.widget->setCancelCallback(
            [this]
            {
                if (_p->cancelCallback)
                {
                    _p->cancelCallback();
                }
            });
    }

    ProgressDialog::ProgressDialog() :
        _p(new Private)
    {}

    ProgressDialog::~ProgressDialog()
    {}

    std::shared_ptr<ProgressDialog> ProgressDialog::create(
        const std::shared_ptr<Context>& context,
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ProgressDialog>(new ProgressDialog);
        out->_init(context, title, text, parent);
        return out;
    }

    void ProgressDialog::setCancelCallback(const std::function<void(void)>& value)
    {
        _p->cancelCallback = value;
    }
}