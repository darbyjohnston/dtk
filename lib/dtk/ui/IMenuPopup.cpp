// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/IMenuPopup.h>

#include <dtk/ui/DrawUtil.h>
#include <dtk/ui/IWindow.h>
#include <dtk/ui/ScrollWidget.h>

#include <optional>

namespace dtk
{
    namespace
    {
        class MenuPopupWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            MenuPopupWidget();

        public:
            virtual ~MenuPopupWidget();

            static std::shared_ptr<MenuPopupWidget> create(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            void setGeometry(const Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
        };

        void MenuPopupWidget::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "dtk::MenuPopupWidget", parent);
            _setMouseHoverEnabled(true);
            _setMousePressEnabled(true);
        }

        MenuPopupWidget::MenuPopupWidget()
        {}

        MenuPopupWidget::~MenuPopupWidget()
        {}

        std::shared_ptr<MenuPopupWidget> MenuPopupWidget::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<MenuPopupWidget>(new MenuPopupWidget);
            out->_init(context, parent);
            return out;
        }

        void MenuPopupWidget::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            const auto& children = getChildren();
            if (!children.empty())
            {
                children.front()->setGeometry(value);
            }
        }

        void MenuPopupWidget::sizeHintEvent(const SizeHintEvent& value)
        {
            IWidget::sizeHintEvent(value);
            const auto& children = getChildren();
            if (!children.empty())
            {
                _setSizeHint(children.front()->getSizeHint());
            }
        }
    }

    struct IMenuPopup::Private
    {
        MenuPopup popup = MenuPopup::Menu;
        ColorRole popupRole = ColorRole::Window;
        Box2I buttonGeometry;
        bool open = false;
        std::function<void(void)> closeCallback;
        std::shared_ptr<IWidget> widget;
        std::shared_ptr<ScrollWidget> scrollWidget;
        std::shared_ptr<MenuPopupWidget> menuPopupWidget;
        std::weak_ptr<IWidget> restoreFocus;

        struct SizeData
        {
            std::optional<float> displayScale;
            int shadow = 0;
        };
        SizeData size;

        struct DrawData
        {
            Box2I g;
            TriMesh2F shadow;
        };
        std::optional<DrawData> draw;
    };

    void IMenuPopup::_init(
        const std::shared_ptr<Context>& context,
        const std::string& objectName,
        const std::shared_ptr<IWidget>& parent)
    {
        IPopup::_init(context, objectName, parent);
        DTK_P();

        p.scrollWidget = ScrollWidget::create(context, ScrollType::Menu);

        p.menuPopupWidget = MenuPopupWidget::create(context, shared_from_this());
        p.scrollWidget->setParent(p.menuPopupWidget);
    }

    IMenuPopup::IMenuPopup() :
        _p(new Private)
    {}

    IMenuPopup::~IMenuPopup()
    {}

    void IMenuPopup::open(
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
        else
        {
            window->setKeyFocus(nullptr);
        }
    }

    bool IMenuPopup::isOpen() const
    {
        return _p->open;
    }

    void IMenuPopup::setCloseCallback(const std::function<void(void)>& value)
    {
        _p->closeCallback = value;
    }

    void IMenuPopup::setPopup(MenuPopup value)
    {
        DTK_P();
        p.popup = value;
    }

    void IMenuPopup::setPopupRole(ColorRole value)
    {
        DTK_P();
        if (value == p.popupRole)
            return;
        p.popupRole = value;
        _setDrawUpdate();
    }

    void IMenuPopup::setWidget(const std::shared_ptr<IWidget>& value)
    {
        DTK_P();
        p.widget = value;
        p.scrollWidget->setWidget(p.widget);
    }

    void IMenuPopup::close()
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

    void IMenuPopup::setGeometry(const Box2I& value)
    {
        IPopup::setGeometry(value);
        DTK_P();

        Size2I sizeHint = p.menuPopupWidget->getSizeHint();
        std::list<Box2I> boxes;
        switch (p.popup)
        {
        case MenuPopup::Menu:
            boxes.push_back(Box2I(
                p.buttonGeometry.min.x,
                p.buttonGeometry.max.y + 1,
                std::max(sizeHint.w, p.buttonGeometry.w()),
                sizeHint.h));
            boxes.push_back(Box2I(
                p.buttonGeometry.max.x + 1 - sizeHint.w,
                p.buttonGeometry.max.y + 1,
                std::max(sizeHint.w, p.buttonGeometry.w()),
                sizeHint.h));
            boxes.push_back(Box2I(
                p.buttonGeometry.min.x,
                p.buttonGeometry.min.y - sizeHint.h,
                std::max(sizeHint.w, p.buttonGeometry.w()),
                sizeHint.h));
            boxes.push_back(Box2I(
                p.buttonGeometry.max.x + 1 - sizeHint.w,
                p.buttonGeometry.min.y - sizeHint.h,
                std::max(sizeHint.w, p.buttonGeometry.w()),
                sizeHint.h));
            break;
        case MenuPopup::SubMenu:
            boxes.push_back(Box2I(
                p.buttonGeometry.max.x,
                p.buttonGeometry.min.y,
                sizeHint.w,
                sizeHint.h));
            boxes.push_back(Box2I(
                p.buttonGeometry.min.x - sizeHint.w,
                p.buttonGeometry.min.y,
                sizeHint.w,
                sizeHint.h));
            break;
        default: break;
        }
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
        const Box2I g = intersect.front().intersected;
        const bool changed = g != p.menuPopupWidget->getGeometry();
        p.menuPopupWidget->setGeometry(g);

        if (!p.draw.has_value() || changed)
        {
            p.draw = Private::DrawData();
            p.draw->g = g;
            const Box2I g2(
                g.min.x - p.size.shadow,
                g.min.y,
                g.w() + p.size.shadow * 2,
                g.h() + p.size.shadow);
            p.draw->shadow = shadow(g2, p.size.shadow);
        }
    }

    void IMenuPopup::sizeHintEvent(const SizeHintEvent& event)
    {
        IPopup::sizeHintEvent(event);
        DTK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.shadow = event.style->getSizeRole(SizeRole::Shadow, event.displayScale);
            p.draw.reset();
        }
    }

    void IMenuPopup::clipEvent(const Box2I& clipRect, bool clipped)
    {
        IWidget::clipEvent(clipRect, clipped);
        DTK_P();
        if (clipped)
        {
            p.draw.reset();
        }
    }

    void IMenuPopup::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IPopup::drawEvent(drawRect, event);
        DTK_P();
        if (p.draw.has_value())
        {
            event.render->drawColorMesh(p.draw->shadow);
            event.render->drawRect(
                p.draw->g,
                event.style->getColorRole(p.popupRole));
        }
    }

    void IMenuPopup::mousePressEvent(MouseClickEvent& event)
    {
        IPopup::mousePressEvent(event);
        DTK_P();
        if (contains(p.buttonGeometry, event.pos))
        {
            event.accept = true;
            close();
        }
    }

    void IMenuPopup::mouseReleaseEvent(MouseClickEvent& event)
    {
        IPopup::mouseReleaseEvent(event);
        event.accept = true;
    }

    void IMenuPopup::keyPressEvent(KeyEvent& event)
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

    void IMenuPopup::keyReleaseEvent(KeyEvent& event)
    {
        IPopup::keyReleaseEvent(event);
        event.accept = true;
    }

    const std::shared_ptr<ScrollWidget>& IMenuPopup::_getScrollWidget() const
    {
        return _p->scrollWidget;
    }
}