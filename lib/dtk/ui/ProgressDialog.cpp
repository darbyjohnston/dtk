// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/ProgressDialog.h>

#include <dtk/ui/Divider.h>
#include <dtk/ui/DrawUtil.h>
#include <dtk/ui/Label.h>
#include <dtk/ui/PushButton.h>
#include <dtk/ui/RowLayout.h>

namespace dtk
{
    class ProgressWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        ProgressWidget();

    public:
        virtual ~ProgressWidget();

        static std::shared_ptr<ProgressWidget> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        const RangeD& getRange() const;
        void setRange(const RangeD&);

        double getValue() const;
        void setValue(double);

        void sizeHintEvent(const SizeHintEvent&) override;
        void drawEvent(const Box2I&, const DrawEvent&) override;

    private:
        RangeD _range = RangeD(0.0, 1.0);
        double _value = 0.0;

        struct SizeData
        {
            int border = 0;
            int width = 0;
            int height = 0;
        };
        SizeData _size;
    };

    void ProgressWidget::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::ProgressWidget", parent);
        setHStretch(Stretch::Expanding);
    }

    ProgressWidget::ProgressWidget()
    {}

    ProgressWidget::~ProgressWidget()
    {}

    std::shared_ptr<ProgressWidget> ProgressWidget::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ProgressWidget>(new ProgressWidget);
        out->_init(context, parent);
        return out;
    }

    const RangeD& ProgressWidget::getRange() const
    {
        return _range;
    }

    void ProgressWidget::setRange(const RangeD& range)
    {
        if (_range == range)
            return;
        _range = range;
        _value = _range.min();
        _setDrawUpdate();
    }

    double ProgressWidget::getValue() const
    {
        return _value;
    }

    void ProgressWidget::setValue(double value)
    {
        if (_value == value)
            return;
        _value = value;
        _setDrawUpdate();
    }

    void ProgressWidget::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);

        _size.border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
        _size.width = event.style->getSizeRole(SizeRole::ScrollArea, event.displayScale);
        const FontInfo fontInfo = event.style->getFontRole(FontRole::Label, event.displayScale);
        const FontMetrics fontMetrics = event.fontSystem->getMetrics(fontInfo);
        _size.height = fontMetrics.lineHeight * .75F;

        _setSizeHint(Size2I(
            _size.width + _size.border * 2,
            _size.height + _size.border * 2));
    }

    void ProgressWidget::drawEvent(const Box2I& drawRect, const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);

        const Box2I& g = getGeometry();
        const int h = _size.height + _size.border * 2;
        const Box2I g2(
            g.min.x,
            g.min.y + std::roundf(g.h() / 2.F - h / 2.F),
            g.w(),
            h);
        event.render->drawMesh(
            border(g2, _size.border),
            event.style->getColorRole(ColorRole::Border));

        const Box2I g3 = margin(g2, -_size.border);
        event.render->drawRect(
            g3,
            event.style->getColorRole(ColorRole::Base));

        const double r = _range.max() - _range.min();
        const double v = r > 0.0 ? ((_value - _range.min()) / r) : 0.0;
        const Box2I g4(
            g3.min.x,
            g3.min.y,
            v * g3.w(),
            g3.h());
        event.render->drawRect(
            g4,
            event.style->getColorRole(ColorRole::Checked));
    }

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

        const std::string& getText() const;
        void setText(const std::string&);

        const std::string& getMessage() const;
        void setMessage(const std::string&);

        const RangeD& getRange() const;
        void setRange(const RangeD&);

        double getValue() const;
        void setValue(double);

        void setCancelCallback(const std::function<void(void)>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        std::shared_ptr<Label> _titleLabel;
        std::shared_ptr<Label> _label;
        std::shared_ptr<ProgressWidget> _progressWidget;
        std::shared_ptr<Label> _messageLabel;
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

        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);

        _titleLabel = Label::create(context, title);
        _titleLabel->setMarginRole(SizeRole::MarginSmall);
        _titleLabel->setBackgroundRole(ColorRole::Button);

        _label = Label::create(context, text);
        _label->setMarginRole(SizeRole::MarginInside);
        _label->setVAlign(VAlign::Top);

        _progressWidget = ProgressWidget::create(context);

        _messageLabel = Label::create(context, text);
        _messageLabel->setMarginRole(SizeRole::MarginInside);
        _messageLabel->setHAlign(HAlign::Center);
        _messageLabel->hide();

        _cancelButton = PushButton::create(context, "Cancel");

        _layout = VerticalLayout::create(context, shared_from_this());
        _layout->setSpacingRole(SizeRole::None);
        _titleLabel->setParent(_layout);
        Divider::create(context, Orientation::Vertical, _layout);
        auto vLayout = VerticalLayout::create(context, _layout);
        vLayout->setMarginRole(SizeRole::Margin);
        vLayout->setSpacingRole(SizeRole::SpacingSmall);
        auto hLayout = HorizontalLayout::create(context, vLayout);
        hLayout->setSpacingRole(SizeRole::SpacingSmall);
        _label->setParent(hLayout);
        _progressWidget->setParent(hLayout);
        _messageLabel->setParent(vLayout);
        Divider::create(context, Orientation::Vertical, _layout);
        hLayout = HorizontalLayout::create(context, _layout);
        hLayout->setMarginRole(SizeRole::MarginSmall);
        hLayout->setSpacingRole(SizeRole::None);
        hLayout->addSpacer(SizeRole::None, Stretch::Expanding);
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

    const std::string& ProgressDialogWidget::getText() const
    {
        return _label->getText();
    }

    void ProgressDialogWidget::setText(const std::string& value)
    {
        _label->setText(value);
    }

    const std::string& ProgressDialogWidget::getMessage() const
    {
        return _messageLabel->getText();
    }

    void ProgressDialogWidget::setMessage(const std::string& value)
    {
        _messageLabel->setText(value);
        _messageLabel->setVisible(!value.empty());
    }

    const RangeD& ProgressDialogWidget::getRange() const
    {
        return _progressWidget->getRange();
    }

    void ProgressDialogWidget::setRange(const RangeD& range)
    {
        _progressWidget->setRange(range);
    }

    double ProgressDialogWidget::getValue() const
    {
        return _progressWidget->getValue();
    }

    void ProgressDialogWidget::setValue(double value)
    {
        _progressWidget->setValue(value);
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
                close();
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

    const std::string& ProgressDialog::getText() const
    {
        return _p->widget->getText();
    }

    void ProgressDialog::setText(const std::string& value)
    {
        _p->widget->setText(value);
    }

    const std::string& ProgressDialog::getMessage() const
    {
        return _p->widget->getMessage();
    }

    void ProgressDialog::setMessage(const std::string& value)
    {
        _p->widget->setMessage(value);
    }

    const RangeD& ProgressDialog::getRange() const
    {
        return _p->widget->getRange();
    }

    void ProgressDialog::setRange(const RangeD& range)
    {
        _p->widget->setRange(range);
    }

    double ProgressDialog::getValue() const
    {
        return _p->widget->getValue();
    }

    void ProgressDialog::setValue(double value)
    {
        _p->widget->setValue(value);
    }
}