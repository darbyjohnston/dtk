// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/LineEdit.h>

#include <feather-tk/ui/DrawUtil.h>
#include <feather-tk/ui/IClipboard.h>
#include <feather-tk/ui/IWindow.h>
#include <feather-tk/ui/LayoutUtil.h>

#include <feather-tk/core/RenderUtil.h>

#include <optional>

namespace feather_tk
{
    namespace
    {
        typedef std::pair<int, int> SelectionPair;

        class Selection
        {
        public:
            const SelectionPair& get() const;
            SelectionPair getSorted() const;
            bool isValid() const;
            void set(const SelectionPair&);
            void setFirst(int);
            void setSecond(int);

            void select(int first, int second);
            void clear();

        private:
            SelectionPair _pair = std::make_pair(-1, -1);
        };

        const SelectionPair& Selection::get() const
        {
            return _pair;
        }

        SelectionPair Selection::getSorted() const
        {
            return std::make_pair(
                std::min(_pair.first, _pair.second),
                std::max(_pair.first, _pair.second));
        }

        bool Selection::isValid() const
        {
            return
                _pair.first != -1 &&
                _pair.second != -1 &&
                _pair.first != _pair.second;
        }

        void Selection::set(const SelectionPair& value)
        {
            _pair = value;
        }

        void Selection::setFirst(int value)
        {
            _pair.first = value;
        }

        void Selection::setSecond(int value)
        {
            _pair.second = value;
        }

        void Selection::select(int first, int second)
        {
            if (-1 == _pair.first)
            {
                _pair.first = first;
                _pair.second = second;
            }
            else
            {
                _pair.second = second;
            }
        }

        void Selection::clear()
        {
            _pair = std::make_pair(-1, -1);
        }
    }

    struct LineEdit::Private
    {
        std::string text;
        std::function<void(const std::string&)> textCallback;
        std::function<void(const std::string&)> textChangedCallback;
        std::string format = "                    ";
        std::function<void(bool)> focusCallback;
        FontRole fontRole = FontRole::Label;
        ColorRole borderRole = ColorRole::Border;
        int cursorPos = 0;
        bool cursorVisible = false;
        std::chrono::steady_clock::time_point cursorTimer;
        Selection selection;

        struct SizeData
        {
            std::optional<float> displayScale;
            int margin = 0;
            int border = 0;
            FontInfo fontInfo;
            FontMetrics fontMetrics;
            Size2I textSize;
            Size2I formatSize;
        };
        SizeData size;

        struct DrawData
        {
            Box2I g2;
            Box2I g3;
            TriMesh2F border;
            std::vector<std::shared_ptr<Glyph> > glyphs;
            std::vector<Box2I> glyphsBox;
        };
        std::optional<DrawData> draw;
    };

    void LineEdit::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "feather_tk::LineEdit", parent);
        FEATHER_TK_P();
        setHAlign(HAlign::Fill);
        setAcceptsKeyFocus(true);
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);
        _textUpdate();
    }

    LineEdit::LineEdit() :
        _p(new Private)
    {}

    LineEdit::~LineEdit()
    {}

    std::shared_ptr<LineEdit> LineEdit::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<LineEdit>(new LineEdit);
        out->_init(context, parent);
        return out;
    }

    const std::string& LineEdit::getText() const
    {
        return _p->text;
    }

    void LineEdit::setText(const std::string& value)
    {
        FEATHER_TK_P();
        if (value == p.text)
            return;
        p.text = value;
        p.cursorPos = p.text.size();
        _textUpdate();
    }

    void LineEdit::clearText()
    {
        setText(std::string());
    }

    void LineEdit::setTextCallback(const std::function<void(const std::string&)>& value)
    {
        _p->textCallback = value;
    }

    void LineEdit::setTextChangedCallback(const std::function<void(const std::string&)>& value)
    {
        _p->textChangedCallback = value;
    }

    const std::string& LineEdit::getFormat() const
    {
        return _p->format;
    }

    void LineEdit::setFormat(const std::string& value)
    {
        FEATHER_TK_P();
        if (value == p.format)
            return;
        p.format = value;
        _textUpdate();
    }

    void LineEdit::setFocusCallback(const std::function<void(bool)>& value)
    {
        _p->focusCallback = value;
    }

    FontRole LineEdit::getFontRole() const
    {
        return _p->fontRole;
    }

    void LineEdit::setFontRole(FontRole value)
    {
        FEATHER_TK_P();
        if (value == p.fontRole)
            return;
        p.fontRole = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    ColorRole LineEdit::getBorderRole() const
    {
        return _p->borderRole;
    }

    void LineEdit::setBorderRole(ColorRole value)
    {
        FEATHER_TK_P();
        if (value == p.borderRole)
            return;
        p.borderRole = value;
        _setDrawUpdate();
    }

    void LineEdit::setGeometry(const Box2I& value)
    {
        const bool changed = value != getGeometry();
        IWidget::setGeometry(value);
        FEATHER_TK_P();
        if (changed)
        {
            p.draw.reset();
        }
    }

    void LineEdit::setVisible(bool value)
    {
        FEATHER_TK_P();
        const bool changed = value != isVisible(false);
        IWidget::setVisible(value);
        if (changed && !isVisible(false))
        {
            if (p.cursorVisible)
            {
                p.cursorVisible = false;
                _setDrawUpdate();
            }
        }
    }

    void LineEdit::setEnabled(bool value)
    {
        FEATHER_TK_P();
        const bool changed = value != isEnabled(false);
        IWidget::setEnabled(value);
        if (changed && !isEnabled(false))
        {
            if (p.cursorVisible)
            {
                p.cursorVisible = false;
                _setDrawUpdate();
            }
        }
    }

    void LineEdit::tickEvent(
        bool parentsVisible,
        bool parentsEnabled,
        const TickEvent& event)
    {
        IWidget::tickEvent(parentsVisible, parentsEnabled, event);
        FEATHER_TK_P();
        if (hasKeyFocus())
        {
            const auto now = std::chrono::steady_clock::now();
            const std::chrono::duration<float> diff = now - p.cursorTimer;
            if (diff.count() > .5F)
            {
                p.cursorVisible = !p.cursorVisible;
                _setDrawUpdate();
                p.cursorTimer = now;
            }
        }
        else if (p.cursorVisible)
        {
            p.cursorVisible = false;
            _setDrawUpdate();
        }
    }

    void LineEdit::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        FEATHER_TK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, event.displayScale);
            p.size.border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
            p.size.fontInfo = event.style->getFontRole(p.fontRole, event.displayScale);
            p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
            p.size.textSize = event.fontSystem->getSize(p.text, p.size.fontInfo);
            p.size.formatSize = event.fontSystem->getSize(p.format, p.size.fontInfo);
            p.draw.reset();
        }

        Size2I sizeHint(p.size.formatSize.w, p.size.fontMetrics.lineHeight);
        sizeHint = margin(
            sizeHint,
            p.size.margin * 2 + p.size.border,
            p.size.margin + p.size.border);
        _setSizeHint(sizeHint);
    }

    void LineEdit::clipEvent(const Box2I& clipRect, bool clipped)
    {
        IWidget::clipEvent(clipRect, clipped);
        FEATHER_TK_P();
        if (clipped)
        {
            p.draw.reset();
        }
    }

    void LineEdit::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        FEATHER_TK_P();

        if (!p.draw.has_value())
        {
            p.draw = Private::DrawData();
            const Box2I g = align(getGeometry(), getSizeHint(), getHAlign(), getVAlign());
            p.draw->g2 = margin(g, -p.size.border);
            p.draw->g3 = margin(
                p.draw->g2,
                -p.size.margin * 2,
                -p.size.margin);
            p.draw->border = border(g, p.size.border);
        }

        const bool enabled = isEnabled();

        // Draw the focus and border.
        event.render->drawMesh(
            p.draw->border,
            event.style->getColorRole(hasKeyFocus() ? ColorRole::KeyFocus : p.borderRole));

        // Draw the background.
        event.render->drawRect(
            p.draw->g2,
            event.style->getColorRole(ColorRole::Base));

        // Enable clipping.
        const ClipRectEnabledState clipRectEnabledState(event.render);
        const ClipRectState clipRectState(event.render);
        event.render->setClipRectEnabled(true);
        event.render->setClipRect(intersect(p.draw->g2, drawRect));

        // Draw the selection.
        if (p.selection.isValid())
        {
            const auto selection = p.selection.getSorted();
            const std::string text0 = p.text.substr(0, selection.first);
            const int x0 = event.fontSystem->getSize(text0, p.size.fontInfo).w;
            const std::string text1 = p.text.substr(0, selection.second);
            const int x1 = event.fontSystem->getSize(text1, p.size.fontInfo).w;
            event.render->drawRect(
                Box2I(p.draw->g3.x() + x0, p.draw->g3.y(), x1 - x0 + 1, p.draw->g3.h()),
                event.style->getColorRole(ColorRole::Checked));
        }

        // Draw the text.
        const V2I pos(
            p.draw->g3.x(),
            p.draw->g3.y() + p.draw->g3.h() / 2 - p.size.fontMetrics.lineHeight / 2);
        if (!p.text.empty() && p.draw->glyphs.empty())
        {
            p.draw->glyphs = event.fontSystem->getGlyphs(p.text, p.size.fontInfo);
            p.draw->glyphsBox = event.fontSystem->getBox(p.text, p.size.fontInfo);
        }
        event.render->drawText(
            p.draw->glyphs,
            p.size.fontMetrics,
            pos,
            event.style->getColorRole(enabled ?
                ColorRole::Text :
                ColorRole::TextDisabled));

        // Draw the cursor.
        if (p.cursorVisible)
        {
            const std::string text = p.text.substr(0, p.cursorPos);
            const int x = event.fontSystem->getSize(text, p.size.fontInfo).w;
            event.render->drawRect(
                Box2I(
                    p.draw->g3.x() + x,
                    p.draw->g3.y(),
                    p.size.border,
                    p.draw->g3.h()),
                event.style->getColorRole(ColorRole::Text));
        }
    }

    void LineEdit::mouseMoveEvent(MouseMoveEvent& event)
    {
        IWidget::mouseMoveEvent(event);
        FEATHER_TK_P();
        if (_isMousePressed())
        {
            const int cursorPos = _getCursorPos(event.pos);
            if (cursorPos != p.cursorPos)
            {
                p.cursorPos = cursorPos;
                p.cursorVisible = true;
                p.cursorTimer = std::chrono::steady_clock::now();
                _setDrawUpdate();
            }
            if (cursorPos != p.selection.get().second)
            {
                p.selection.setSecond(cursorPos);
                _setDrawUpdate();
            }
        }
    }

    void LineEdit::mousePressEvent(MouseClickEvent& event)
    {
        IWidget::mousePressEvent(event);
        FEATHER_TK_P();
        const int cursorPos = _getCursorPos(event.pos);
        if (cursorPos != p.cursorPos)
        {
            p.cursorPos = cursorPos;
            p.cursorVisible = true;
            p.cursorTimer = std::chrono::steady_clock::now();
            _setDrawUpdate();
        }
        const SelectionPair selection(cursorPos, cursorPos);
        if (selection != p.selection.get())
        {
            p.selection.set(selection);
            _setDrawUpdate();
        }
        takeKeyFocus();
    }

    void LineEdit::keyFocusEvent(bool value)
    {
        IWidget::keyFocusEvent(value);
        FEATHER_TK_P();
        if (value)
        {
            p.selection.clear();
            p.selection.select(0, p.text.size());
            _setDrawUpdate();
        }
        else
        {
            p.selection.clear();
            if (p.textCallback)
            {
                p.textCallback(p.text);
            }
            _setDrawUpdate();
        }
        if (p.focusCallback)
        {
            p.focusCallback(value);
        }
    }

    void LineEdit::keyPressEvent(KeyEvent& event)
    {
        FEATHER_TK_P();
        if (hasKeyFocus())
        {
            switch (event.key)
            {
            case Key::A:
                event.accept = true;
                if (event.modifiers & static_cast<int>(KeyModifier::Control))
                {
                    p.selection.clear();
                    p.selection.select(0, p.text.size());
                    _setDrawUpdate();
                }
                break;
            case Key::C:
                event.accept = true;
                if (event.modifiers & static_cast<int>(KeyModifier::Control))
                {
                    if (p.selection.isValid())
                    {
                        if (auto window = getWindow())
                        {
                            if (auto clipboard = window->getClipboard())
                            {
                                const auto selection = p.selection.getSorted();
                                const std::string text = p.text.substr(
                                    selection.first,
                                    selection.second - selection.first);
                                clipboard->setText(text);
                            }
                        }
                    }
                }
                break;
            case Key::V:
                event.accept = true;
                if (event.modifiers & static_cast<int>(KeyModifier::Control))
                {
                    if (auto window = getWindow())
                    {
                        if (auto clipboard = window->getClipboard())
                        {
                            const std::string text = clipboard->getText();
                            if (p.selection.isValid())
                            {
                                const auto selection = p.selection.getSorted();
                                p.text.replace(
                                    selection.first,
                                    selection.second - selection.first,
                                    text);
                                p.selection.clear();
                                p.cursorPos = selection.first + text.size();
                            }
                            else
                            {
                                p.text.insert(p.cursorPos, text);
                                p.cursorPos += text.size();
                            }
                            if (p.textChangedCallback)
                            {
                                p.textChangedCallback(p.text);
                            }
                            _textUpdate();
                        }
                    }
                }
                break;
            case Key::X:
                event.accept = true;
                if (event.modifiers & static_cast<int>(KeyModifier::Control))
                {
                    if (p.selection.isValid())
                    {
                        if (auto window = getWindow())
                        {
                            if (auto clipboard = window->getClipboard())
                            {
                                const auto selection = p.selection.getSorted();
                                const std::string text = p.text.substr(
                                    selection.first,
                                    selection.second - selection.first);
                                clipboard->setText(text);
                                p.text.replace(
                                    selection.first,
                                    selection.second - selection.first,
                                    "");
                                p.selection.clear();
                                p.cursorPos = selection.first;
                                if (p.textChangedCallback)
                                {
                                    p.textChangedCallback(p.text);
                                }
                                _textUpdate();
                            }
                        }
                    }
                }
                break;
            case Key::Left:
                event.accept = true;
                if (p.cursorPos > 0)
                {
                    if (event.modifiers & static_cast<int>(KeyModifier::Shift))
                    {
                        p.selection.select(p.cursorPos, p.cursorPos - 1);
                    }
                    else
                    {
                        p.selection.clear();
                    }

                    p.cursorPos--;
                    p.cursorVisible = true;
                    p.cursorTimer = std::chrono::steady_clock::now();

                    _setDrawUpdate();
                }
                break;
            case Key::Right:
                event.accept = true;
                if (p.cursorPos < p.text.size())
                {
                    if (event.modifiers & static_cast<int>(KeyModifier::Shift))
                    {
                        p.selection.select(p.cursorPos, p.cursorPos + 1);
                    }
                    else
                    {
                        p.selection.clear();
                    }

                    p.cursorPos++;
                    p.cursorVisible = true;
                    p.cursorTimer = std::chrono::steady_clock::now();

                    _setDrawUpdate();
                }
                break;
            case Key::Home:
                event.accept = true;
                if (p.cursorPos > 0)
                {
                    if (event.modifiers & static_cast<int>(KeyModifier::Shift))
                    {
                        p.selection.select(p.cursorPos, 0);
                    }
                    else
                    {
                        p.selection.clear();
                    }

                    p.cursorPos = 0;
                    p.cursorVisible = true;
                    p.cursorTimer = std::chrono::steady_clock::now();

                    _setDrawUpdate();
                }
                break;
            case Key::End:
                event.accept = true;
                if (p.cursorPos < p.text.size())
                {
                    if (event.modifiers & static_cast<int>(KeyModifier::Shift))
                    {
                        p.selection.select(p.cursorPos, p.text.size());
                    }
                    else
                    {
                        p.selection.clear();
                    }

                    p.cursorPos = p.text.size();
                    p.cursorVisible = true;
                    p.cursorTimer = std::chrono::steady_clock::now();

                    _setDrawUpdate();
                }
                break;
            case Key::Backspace:
                event.accept = true;
                if (p.selection.isValid())
                {
                    const auto selection = p.selection.getSorted();
                    p.text.erase(
                        selection.first,
                        selection.second - selection.first);
                    p.selection.clear();
                    p.cursorPos = selection.first;
                    if (p.textChangedCallback)
                    {
                        p.textChangedCallback(p.text);
                    }
                    _textUpdate();
                }
                else if (p.cursorPos > 0)
                {
                    const auto i = p.text.begin() + p.cursorPos - 1;
                    p.text.erase(i);
                    p.cursorPos--;
                    if (p.textChangedCallback)
                    {
                        p.textChangedCallback(p.text);
                    }
                    _textUpdate();
                }
                break;
            case Key::Delete:
                event.accept = true;
                if (p.selection.isValid())
                {
                    const auto selection = p.selection.getSorted();
                    p.text.erase(
                        selection.first,
                        selection.second - selection.first);
                    p.selection.clear();
                    p.cursorPos = selection.first;
                    if (p.textChangedCallback)
                    {
                        p.textChangedCallback(p.text);
                    }
                    _textUpdate();
                }
                else if (p.cursorPos < p.text.size())
                {
                    const auto i = p.text.begin() + p.cursorPos;
                    p.text.erase(i);
                    if (p.textChangedCallback)
                    {
                        p.textChangedCallback(p.text);
                    }
                    _textUpdate();
                }
                break;
            case Key::Enter:
                event.accept = true;
                if (p.textCallback)
                {
                    p.textCallback(p.text);
                }
                break;
            case Key::Escape:
                event.accept = true;
                releaseKeyFocus();
                break;
            case Key::Up:
            case Key::Down:
            case Key::PageUp:
            case Key::PageDown:
            case Key::Tab:
                break;
            default:
                if (0 == event.modifiers || event.modifiers == static_cast<int>(KeyModifier::Shift))
                {
                    event.accept = true;
                }
                break;
            }
        }
        if (!event.accept)
        {
            IWidget::keyPressEvent(event);
        }
    }

    void LineEdit::keyReleaseEvent(KeyEvent& event)
    {
        IWidget::keyReleaseEvent(event);
        event.accept = true;
    }

    void LineEdit::textEvent(TextEvent& event)
    {
        FEATHER_TK_P();
        event.accept = true;
        if (p.selection.isValid())
        {
            const auto selection = p.selection.getSorted();
            p.text.replace(
                selection.first,
                selection.second - selection.first,
                event.text);
            p.selection.clear();
            p.cursorPos = selection.first + event.text.size();
        }
        else
        {
            p.text.insert(p.cursorPos, event.text);
            p.cursorPos += event.text.size();
        }
        if (p.textChangedCallback)
        {
            p.textChangedCallback(p.text);
        }
        _textUpdate();
    }

    int LineEdit::_getCursorPos(const V2I& value)
    {
        FEATHER_TK_P();
        int out = 0;
        if (p.draw.has_value())
        {
            for (const auto& glyphBox : p.draw->glyphsBox)
            {
                if (value.x < p.draw->g3.x() + glyphBox.x() + glyphBox.w())
                {
                    break;
                }
                ++out;
            }
        }
        return out;
    }

    void LineEdit::_textUpdate()
    {
        FEATHER_TK_P();
        p.size.displayScale.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }
}