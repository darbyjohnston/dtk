// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUI/IMenuPopup.h>

#include <dtkUI/DrawUtil.h>
#include <dtkUI/IWindow.h>
#include <dtkUI/ScrollWidget.h>

using namespace dtk::core;

namespace dtk
{
    namespace ui
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
                IWidget::_init(context, "dtk::ui::MenuPopupWidget", parent);
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
                bool init = true;
                float displayScale = 0.F;
                int shadow = 0;
            };
            SizeData size;

            struct DrawData
            {
                Box2I g;
                TriMesh2F shadow;
            };
            DrawData draw;
        };

        void IMenuPopup::_init(
            const std::shared_ptr<Context>& context,
            const std::string& objectName,
            const std::shared_ptr<IWidget>& parent)
        {
            IPopup::_init(context, objectName, parent);
            DTK_P();

            p.scrollWidget = ScrollWidget::create(
                context,
                ScrollType::Menu);
            
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
        }

        bool IMenuPopup::isOpen() const
        {
            return _p->open;
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
                intersect.push_back({ box, core::intersect(box, value) });
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
            p.menuPopupWidget->setGeometry(g);

            p.draw.g = g;
            const Box2I g2(
                g.min.x - p.size.shadow,
                g.min.y,
                g.w() + p.size.shadow * 2,
                g.h() + p.size.shadow);
            p.draw.shadow = shadow(g2, p.size.shadow);
        }

        void IMenuPopup::sizeHintEvent(const SizeHintEvent& event)
        {
            IPopup::sizeHintEvent(event);
            DTK_P();
            if (p.size.init || event.displayScale != p.size.displayScale)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.shadow = event.style->getSizeRole(SizeRole::Shadow, p.size.displayScale);
            }
        }

        void IMenuPopup::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IPopup::drawEvent(drawRect, event);
            DTK_P();
            event.render->drawColorMesh(p.draw.shadow);
            event.render->drawRect(
                convert(p.draw.g),
                event.style->getColorRole(p.popupRole));
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
}
