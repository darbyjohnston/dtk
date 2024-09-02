// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/IWidgetPopup.h>

#include <dtk/ui/DrawUtil.h>
#include <dtk/ui/IWindow.h>

namespace dtk
{
    namespace
    {
        class ContainerWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            ContainerWidget();

        public:
            virtual ~ContainerWidget();

            static std::shared_ptr<ContainerWidget> create(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            void setGeometry(const Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
        };

        void ContainerWidget::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "dtk::ContainerWidget", parent);
            _setMouseHoverEnabled(true);
            _setMousePressEnabled(true);
        }

        ContainerWidget::ContainerWidget()
        {}

        ContainerWidget::~ContainerWidget()
        {}

        std::shared_ptr<ContainerWidget> ContainerWidget::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ContainerWidget>(new ContainerWidget);
            out->_init(context, parent);
            return out;
        }

        void ContainerWidget::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            const auto& children = getChildren();
            if (!children.empty())
            {
                children.front()->setGeometry(value);
            }
        }

        void ContainerWidget::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            const auto& children = getChildren();
            if (!children.empty())
            {
                _setSizeHint(children.front()->getSizeHint());
            }
        }
    }

    struct IWidgetPopup::Private
    {
        ColorRole popupRole = ColorRole::Window;
        Box2I buttonGeometry;
        bool open = false;
        std::function<void(void)> closeCallback;
        std::shared_ptr<IWidget> widget;
        std::shared_ptr<ContainerWidget> containerWidget;
        std::weak_ptr<IWidget> restoreFocus;

        struct SizeData
        {
            int border = 0;
            int shadow = 0;
        };
        SizeData size;

        struct DrawData
        {
            Box2I g;
            TriMesh2F shadow;
            TriMesh2F border;
        };
        DrawData draw;
    };

    void IWidgetPopup::_init(
        const std::shared_ptr<Context>& context,
        const std::string& objectName,
        const std::shared_ptr<IWidget>& parent)
    {
        IPopup::_init(context, objectName, parent);
        DTK_P();
        p.containerWidget = ContainerWidget::create(context, shared_from_this());
    }

    IWidgetPopup::IWidgetPopup() :
        _p(new Private)
    {}

    IWidgetPopup::~IWidgetPopup()
    {}

    void IWidgetPopup::open(
        const std::shared_ptr<IWindow>& window,
        const Box2I& buttonGeometry)
    {
        DTK_P();
        p.buttonGeometry = buttonGeometry;
        p.open = true;
        p.restoreFocus = window->getKeyFocus();
        setParent(window);
        if (auto widget = window->getNextKeyFocus(shared_from_this()))
        {
            widget->takeKeyFocus();
        }
    }

    bool IWidgetPopup::isOpen() const
    {
        return _p->open;
    }

    void IWidgetPopup::close()
    {
        DTK_P();
        p.open = false;
        setParent(nullptr);
        auto widget = p.restoreFocus.lock();
        p.restoreFocus.reset();
        if (p.closeCallback)
        {
            p.closeCallback();
        }
        if (widget)
        {
            widget->takeKeyFocus();
        }
    }

    void IWidgetPopup::setCloseCallback(const std::function<void(void)>& value)
    {
        _p->closeCallback = value;
    }

    ColorRole IWidgetPopup::getPopupRole() const
    {
        return _p->popupRole;
    }

    void IWidgetPopup::setPopupRole(ColorRole value)
    {
        DTK_P();
        if (value == p.popupRole)
            return;
        p.popupRole = value;
        _setDrawUpdate();
    }

    const std::shared_ptr<IWidget>& IWidgetPopup::getWidget() const
    {
        return _p->widget;
    }

    void IWidgetPopup::setWidget(const std::shared_ptr<IWidget>& value)
    {
        DTK_P();
        if (p.widget)
        {
            p.widget->setParent(nullptr);
        }
        p.widget = value;
        if (p.widget)
        {
            p.widget->setParent(p.containerWidget);
        }
    }

    void IWidgetPopup::setGeometry(const Box2I& value)
    {
        IPopup::setGeometry(value);
        DTK_P();
        Size2I sizeHint = p.containerWidget->getSizeHint();
        std::list<Box2I> boxes;
        boxes.push_back(Box2I(
            p.buttonGeometry.min.x,
            p.buttonGeometry.max.y + 1,
            sizeHint.w,
            sizeHint.h));
        boxes.push_back(Box2I(
            p.buttonGeometry.max.x + 1 - sizeHint.w,
            p.buttonGeometry.max.y + 1,
            sizeHint.w,
            sizeHint.h));
        boxes.push_back(Box2I(
            p.buttonGeometry.min.x,
            p.buttonGeometry.min.y - sizeHint.h,
            sizeHint.w,
            sizeHint.h));
        boxes.push_back(Box2I(
            p.buttonGeometry.max.x + 1 - sizeHint.w,
            p.buttonGeometry.min.y - sizeHint.h,
            sizeHint.w,
            sizeHint.h));
        struct Intersect
        {
            Box2I original;
            Box2I intersected;
        };
        std::vector<Intersect> intersect;
        for (const auto& box : boxes)
        {
            intersect.push_back({ box, dtk::intersect(box, value) });
        }
        std::stable_sort(
            intersect.begin(),
            intersect.end(),
            [](const Intersect& a, const Intersect& b)
            {
                return
                    area(a.intersected.size()) >
                    area(b.intersected.size());
            });
        Box2I g = intersect.front().intersected;
        p.containerWidget->setGeometry(g);

        p.draw.g = g;
        const Box2I g2 = margin(g, p.size.border);
        const Box2I g3 = Box2I(
            g.min.x - p.size.shadow,
            g.min.y,
            g.w() + p.size.shadow * 2,
            g.h() + p.size.shadow);
        p.draw.shadow = shadow(g3, p.size.shadow);
        p.draw.border = border(g2, p.size.border);
    }

    void IWidgetPopup::sizeHintEvent(const SizeHintEvent& event)
    {
        IPopup::sizeHintEvent(event);
        DTK_P();
        p.size.border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
        p.size.shadow = event.style->getSizeRole(SizeRole::Shadow, event.displayScale);
    }

    void IWidgetPopup::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IPopup::drawEvent(drawRect, event);
        DTK_P();
        event.render->drawColorMesh(p.draw.shadow);
        event.render->drawMesh(
            p.draw.border,
            event.style->getColorRole(ColorRole::Border));
        event.render->drawRect(
            convert(p.draw.g),
            event.style->getColorRole(p.popupRole));
    }

    void IWidgetPopup::keyPressEvent(KeyEvent& event)
    {
        if (0 == event.modifiers)
        {
            if (Key::Escape == event.key)
            {
                event.accept = true;
                close();
            }
        }
        if (!event.accept)
        {
            IPopup::keyPressEvent(event);
        }
    }

    void IWidgetPopup::keyReleaseEvent(KeyEvent& event)
    {
        IPopup::keyReleaseEvent(event);
        event.accept = true;
    }
}