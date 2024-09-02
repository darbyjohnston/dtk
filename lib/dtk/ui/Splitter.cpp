// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/Splitter.h>

#include <dtk/ui/LayoutUtil.h>

namespace dtk
{
    namespace ui
    {
        struct Splitter::Private
        {
            Orientation orientation = Orientation::Horizontal;
            std::vector<float> split;
            SizeRole spacingRole = SizeRole::SpacingSmall;

            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int handle = 0;

                std::vector<Box2I> handleGeometry;
            };
            SizeData size;

            struct MouseData
            {
                int hoverHandle = -1;
                int pressedHandle = -1;
                float pressedSplit = 0.F;
            };
            MouseData mouse;
        };

        void Splitter::_init(
            const std::shared_ptr<Context>& context,
            Orientation orientation,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "dtk::ui::Splitter", parent);
            DTK_P();
            setStretch(Stretch::Expanding);
            _setMouseHoverEnabled(true);
            _setMousePressEnabled(true);
            p.orientation = orientation;
        }

        Splitter::Splitter() :
            _p(new Private)
        {}

        Splitter::~Splitter()
        {}

        std::shared_ptr<Splitter> Splitter::create(
            const std::shared_ptr<Context>& context,
            Orientation orientation,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<Splitter>(new Splitter);
            out->_init(context, orientation, parent);
            return out;
        }

        std::vector<float> Splitter::getSplit() const
        {
            return _p->split;
        }

        void Splitter::setSplit(const std::vector<float>& value)
        {
            DTK_P();
            if (value == p.split)
                return;
            p.split = value;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void Splitter::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            DTK_P();

            const Box2I& g = getGeometry();
            const int w = g.w();
            const int h = g.h();
            std::vector<Box2I> childGeometry;
            p.size.handleGeometry.clear();
            switch (p.orientation)
            {
            case Orientation::Horizontal:
            {
                int x = 0;
                for (size_t i = 0; i < p.split.size(); ++i)
                {
                    const int w2 = w * p.split[i];
                    childGeometry.push_back(Box2I(g.min.x + x, g.min.y, w2, h));
                    x += w2;
                }
                for (size_t i = 1; i < childGeometry.size(); ++i)
                {
                    childGeometry[i - 1].max.x -= p.size.handle / 2;
                    childGeometry[i].min.x += p.size.handle / 2;
                    p.size.handleGeometry.push_back(Box2I(
                        childGeometry[i - 1].max.x,
                        childGeometry[i - 1].min.y,
                        p.size.handle,
                        childGeometry[i - 1].h()));
                }
                if (!childGeometry.empty())
                {
                    childGeometry[childGeometry.size() - 1].max.x = g.max.x;
                }
                break;
            }
            case Orientation::Vertical:
            {
                int y = 0;
                for (size_t i = 0; i < p.split.size(); ++i)
                {
                    const int h2 = h * p.split[i];
                    childGeometry.push_back(Box2I(g.min.x, g.min.y + y, w, h2));
                    y += h2;
                }
                for (size_t i = 1; i < childGeometry.size(); ++i)
                {
                    childGeometry[i - 1].max.y -= p.size.handle / 2;
                    childGeometry[i].min.y += p.size.handle / 2;
                    p.size.handleGeometry.push_back(Box2I(
                        childGeometry[i - 1].min.x,
                        childGeometry[i - 1].max.y,
                        childGeometry[i - 1].w(),
                        p.size.handle));
                }
                if (!childGeometry.empty())
                {
                    childGeometry[childGeometry.size() - 1].max.y = g.max.y;
                }
                break;
            }
            default: break;
            }

            const auto& children = getChildren();
            int i = 0;
            for (auto j = children.begin();
                i < childGeometry.size() && j != children.end();
                ++i, ++j)
            {
                (*j)->setGeometry(childGeometry[i]);
            }
        }

        void Splitter::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            DTK_P();

            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (p.size.init || displayScaleChanged)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.handle = event.style->getSizeRole(SizeRole::HandleSmall, p.size.displayScale);
            }

            Size2I sizeHint;
            const auto& children = getChildren();
            for (const auto& child : children)
            {
                const auto& childSizeHint = child->getSizeHint();
                switch (p.orientation)
                {
                case Orientation::Horizontal:
                    sizeHint.w += childSizeHint.w;
                    sizeHint.h = std::max(sizeHint.h, childSizeHint.h);
                    break;
                case Orientation::Vertical:
                    sizeHint.w = std::max(sizeHint.w, childSizeHint.w);
                    sizeHint.h += childSizeHint.h;
                    break;
                default: break;
                }
            }
            switch (p.orientation)
            {
            case Orientation::Horizontal:
                sizeHint.w += p.size.handle * children.size();
                break;
            case Orientation::Vertical:
                sizeHint.h += p.size.handle * children.size();
                break;
            default: break;
            }
            _setSizeHint(sizeHint);
        }

        void Splitter::childAddEvent(const ChildAddEvent& event)
        {
            IWidget::childAddEvent(event);
            DTK_P();
            const auto& children = getChildren();
            if (p.split.size() < children.size())
            {
                float split = 1.F;
                if (!p.split.empty())
                {
                    split = p.split.back() / 2.F;
                    p.split.back() = split;
                }
                p.split.push_back(split);
            }
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void Splitter::childRemoveEvent(const ChildRemoveEvent& event)
        {
            IWidget::childRemoveEvent(event);
            DTK_P();
            if (event.index < p.split.size())
            {
                const float split = p.split[event.index];
                p.split.erase(p.split.begin() + event.index);
                if (event.index > 0)
                {
                    p.split[event.index - 1] += split;
                }
                else if (!p.split.empty())
                {
                    p.split[0] += split;
                }
            }
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void Splitter::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            DTK_P();
            for (const auto& handle : p.size.handleGeometry)
            {
                event.render->drawRect(
                    convert(handle),
                    event.style->getColorRole(ColorRole::Button));
            }
            if (p.mouse.pressedHandle >= 0 &&
                p.mouse.pressedHandle < p.size.handleGeometry.size())
            {
                const Box2I g = p.size.handleGeometry[p.mouse.pressedHandle];
                event.render->drawRect(
                    convert(g),
                    event.style->getColorRole(ColorRole::Pressed));
            }
            else if (p.mouse.hoverHandle >= 0 &&
                p.mouse.hoverHandle < p.size.handleGeometry.size())
            {
                const Box2I g = p.size.handleGeometry[p.mouse.hoverHandle];
                event.render->drawRect(
                    convert(g),
                    event.style->getColorRole(ColorRole::Hover));
            }
        }

        void Splitter::mouseEnterEvent()
        {}

        void Splitter::mouseLeaveEvent()
        {
            DTK_P();
            if (p.mouse.hoverHandle != -1)
            {
                p.mouse.hoverHandle = -1;
                _setDrawUpdate();
            }
        }

        void Splitter::mouseMoveEvent(MouseMoveEvent& event)
        {
            DTK_P();
            event.accept = true;
            if (p.mouse.pressedHandle != -1)
            {
                const Box2I& g = getGeometry();
                float s = 0.F;
                switch (p.orientation)
                {
                case Orientation::Horizontal:
                    s = (event.pos.x - event.prev.x) / static_cast<float>(g.w());
                    break;
                case Orientation::Vertical:
                    s = (event.pos.y - event.prev.y) / static_cast<float>(g.h());
                    break;
                default: break;
                }
                p.split[p.mouse.pressedHandle] += s;

                const int last = static_cast<int>(p.split.size()) - 1;
                if (p.mouse.pressedHandle < last)
                {
                    float size = 0.F;
                    for (int i = 0; i < last; ++i)
                    {
                        size += p.split[i];
                    }
                    p.split[last] = 1.F - size;
                }

                _setSizeUpdate();
                _setDrawUpdate();
            }
            else
            {
                int hoverHandle = -1;
                for (size_t i = 0; i < p.size.handleGeometry.size(); ++i)
                {
                    if (contains(p.size.handleGeometry[i], event.pos))
                    {
                        hoverHandle = i;
                        break;
                    }
                }
                if (hoverHandle != p.mouse.hoverHandle)
                {
                    p.mouse.hoverHandle = hoverHandle;
                    _setDrawUpdate();
                }
            }
        }

        void Splitter::mousePressEvent(MouseClickEvent& event)
        {
            DTK_P();
            p.mouse.pressedHandle = -1;
            for (size_t i = 0; i < p.size.handleGeometry.size(); ++i)
            {
                if (contains(p.size.handleGeometry[i], event.pos))
                {
                    event.accept = true;
                    p.mouse.pressedHandle = i;
                    p.mouse.pressedSplit = p.split[i];
                    _setDrawUpdate();
                    break;
                }
            }
        }

        void Splitter::mouseReleaseEvent(MouseClickEvent& event)
        {
            DTK_P();
            event.accept = true;
            p.mouse.pressedHandle = -1;
            _setDrawUpdate();
        }

        void Splitter::_releaseMouse()
        {
            IWidget::_releaseMouse();
            DTK_P();
            if (p.mouse.hoverHandle || p.mouse.pressedHandle)
            {
                p.mouse.hoverHandle = -1;
                p.mouse.pressedHandle = -1;
                _setDrawUpdate();
            }
        }
    }
}
