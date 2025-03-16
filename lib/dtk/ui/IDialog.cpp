// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/IDialog.h>

#include <dtk/ui/DrawUtil.h>
#include <dtk/ui/IWindow.h>

#include <optional>

namespace dtk
{
    struct IDialog::Private
    {
        bool open = false;
        std::function<void(void)> closeCallback;
        std::weak_ptr<IWidget> restoreFocus;

        struct SizeData
        {
            std::optional<float> displayScale;
            int margin = 0;
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

    void IDialog::_init(
        const std::shared_ptr<Context>& context,
        const std::string& objectName,
        const std::shared_ptr<IWidget>& parent)
    {
        IPopup::_init(context, objectName, parent);
        setBackgroundRole(ColorRole::Overlay);
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);
    }

    IDialog::IDialog() :
        _p(new Private)
    {}

    IDialog::~IDialog()
    {}

    void IDialog::open(const std::shared_ptr<IWindow>& window)
    {
        DTK_P();
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

    bool IDialog::isOpen() const
    {
        return _p->open;
    }

    void IDialog::setCloseCallback(const std::function<void(void)>& value)
    {
        _p->closeCallback = value;
    }

    void IDialog::close()
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

    void IDialog::setGeometry(const Box2I& value)
    {
        IPopup::setGeometry(value);
        DTK_P();
        const auto& children = getChildren();
        if (!children.empty())
        {
            const Box2I g = margin(value, -p.size.margin);
            const Size2I& sizeHint = children.front()->getSizeHint();
            V2I size;
            size.x = std::min(sizeHint.w, g.w());
            size.y = std::min(sizeHint.h, g.h());
            if (Stretch::Expanding == children.front()->getHStretch())
            {
                size.x = g.w();
            }
            if (Stretch::Expanding == children.front()->getVStretch())
            {
                size.y = g.h();
            }
            children.front()->setGeometry(Box2I(
                g.x() + g.w() / 2 - size.x / 2,
                g.y() + g.h() / 2 - size.y / 2,
                size.x,
                size.y));

            p.draw.g = children.front()->getGeometry();
            const Box2I g2(
                p.draw.g.min.x - p.size.shadow,
                p.draw.g.min.y,
                p.draw.g.w() + p.size.shadow * 2,
                p.draw.g.h() + p.size.shadow);
            p.draw.shadow = shadow(g2, p.size.shadow);
            p.draw.border = border(margin(p.draw.g, p.size.border), p.size.border);
        }
        else
        {
            p.draw.g = Box2I();
            p.draw.shadow = TriMesh2F();
            p.draw.border = TriMesh2F();
        }
    }

    void IDialog::sizeHintEvent(const SizeHintEvent& event)
    {
        IPopup::sizeHintEvent(event);
        DTK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(SizeRole::MarginDialog, event.displayScale);
            p.size.border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
            p.size.shadow = event.style->getSizeRole(SizeRole::Shadow, event.displayScale);
        }
    }

    void IDialog::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IPopup::drawEvent(drawRect, event);
        DTK_P();
        if (!getChildren().empty())
        {
            event.render->drawColorMesh(p.draw.shadow);
            event.render->drawMesh(
                p.draw.border,
                event.style->getColorRole(ColorRole::Border));
            event.render->drawRect(
                p.draw.g,
                event.style->getColorRole(ColorRole::Window));
        }
    }

    void IDialog::keyPressEvent(KeyEvent& event)
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

    void IDialog::keyReleaseEvent(KeyEvent& event)
    {
        IPopup::keyReleaseEvent(event);
        event.accept = true;
    }
}