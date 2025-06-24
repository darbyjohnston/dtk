// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/IWidgetPopup.h>

#include <feather-tk/ui/DrawUtil.h>
#include <feather-tk/ui/IWindow.h>

#include <optional>

namespace feather_tk
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
            IWidget::_init(context, "feather_tk::ContainerWidget", parent);
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
            std::optional<float> displayScale;
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
        std::optional<DrawData> draw;
    };

    void IWidgetPopup::_init(
        const std::shared_ptr<Context>& context,
        const std::string& objectName,
        const std::shared_ptr<IWidget>& parent)
    {
        IPopup::_init(context, objectName, parent);
        FEATHER_TK_P();
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
        FEATHER_TK_P();
        p.buttonGeometry = buttonGeometry;
        p.open = true;
        p.restoreFocus = window->getKeyFocus();
        setParent(window);
        if (auto widget = window->getNextKeyFocus(shared_from_this()))
        {
            widget->takeKeyFocus();
        }
        else
        {
            window->setKeyFocus(nullptr);
        }
    }

    bool IWidgetPopup::isOpen() const
    {
        return _p->open;
    }

    void IWidgetPopup::close()
    {
        FEATHER_TK_P();
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
        FEATHER_TK_P();
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
        FEATHER_TK_P();
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
        FEATHER_TK_P();

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
            intersect.push_back({ box, feather_tk::intersect(box, value) });
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
        const Box2I g = intersect.front().intersected;
        const bool changed = g != p.containerWidget->getGeometry();
        p.containerWidget->setGeometry(g);

        if (!p.draw.has_value() || changed)
        {
            p.draw = Private::DrawData();
            p.draw->g = g;
            const Box2I g2 = margin(g, p.size.border);
            const Box2I g3 = Box2I(
                g.min.x - p.size.shadow,
                g.min.y,
                g.w() + p.size.shadow * 2,
                g.h() + p.size.shadow);
            p.draw->shadow = shadow(g3, p.size.shadow);
            p.draw->border = border(g2, p.size.border);
        }
    }

    void IWidgetPopup::sizeHintEvent(const SizeHintEvent& event)
    {
        IPopup::sizeHintEvent(event);
        FEATHER_TK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
            p.size.shadow = event.style->getSizeRole(SizeRole::Shadow, event.displayScale);
            p.draw.reset();
        }
    }

    void IWidgetPopup::clipEvent(const Box2I& clipRect, bool clipped)
    {
        IWidget::clipEvent(clipRect, clipped);
        FEATHER_TK_P();
        if (clipped)
        {
            p.draw.reset();
        }
    }

    void IWidgetPopup::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IPopup::drawEvent(drawRect, event);
        FEATHER_TK_P();

        if (p.draw.has_value())
        {
            event.render->drawColorMesh(p.draw->shadow);
            event.render->drawMesh(
                p.draw->border,
                event.style->getColorRole(ColorRole::Border));
            event.render->drawRect(
                p.draw->g,
                event.style->getColorRole(p.popupRole));
        }
    }

    void IWidgetPopup::mousePressEvent(MouseClickEvent& event)
    {
        IPopup::mousePressEvent(event);
        FEATHER_TK_P();
        if (contains(p.buttonGeometry, event.pos))
        {
            event.accept = true;
            close();
        }
    }

    void IWidgetPopup::mouseReleaseEvent(MouseClickEvent& event)
    {
        IPopup::mouseReleaseEvent(event);
        event.accept = true;
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