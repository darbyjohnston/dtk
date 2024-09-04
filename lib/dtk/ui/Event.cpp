// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/Event.h>

#include <dtk/core/Error.h>
#include <dtk/core/String.h>

#include <sstream>

namespace dtk
{
    ChildAddEvent::ChildAddEvent(const std::shared_ptr<IWidget>& child) :
        child(child)
    {}

    ChildRemoveEvent::ChildRemoveEvent(const std::shared_ptr<IWidget>& child, int index) :
        child(child),
        index(index)
    {}

    SizeHintEvent::SizeHintEvent(
        const std::shared_ptr<FontSystem>& fontSystem,
        float                               displayScale,
        const std::shared_ptr<Style>& style,
        const std::shared_ptr<IconLibrary>& iconLibrary) :
        fontSystem(fontSystem),
        displayScale(displayScale),
        style(style),
        iconLibrary(iconLibrary)
    {}

    DrawEvent::DrawEvent(
        const std::shared_ptr<FontSystem>& fontSystem,
        float                               displayScale,
        const std::shared_ptr<Style>& style,
        const std::shared_ptr<IconLibrary>& iconLibrary,
        const std::shared_ptr<IRender>& render) :
        fontSystem(fontSystem),
        displayScale(displayScale),
        style(style),
        iconLibrary(iconLibrary),
        render(render)
    {}

    DragAndDropData::~DragAndDropData()
    {}

    MouseEnterEvent::MouseEnterEvent(const V2I & pos) :
        pos(pos)
    {}

    MouseMoveEvent::MouseMoveEvent(
        const V2I & pos,
        const V2I & prev) :
        pos(pos),
        prev(prev)
    {}

    MouseClickEvent::MouseClickEvent(
        int        button,
        int        modifiers,
        const V2I& pos) :
        button(button),
        modifiers(modifiers),
        pos(pos)
    {}

    ScrollEvent::ScrollEvent(
        const V2F& value,
        int        modifiers,
        const V2I& pos) :
        value(value),
        modifiers(modifiers),
        pos(pos)
    {}

    std::string getKeyModifierLabel(int value)
    {
        std::vector<std::string> out;
        if (value & static_cast<size_t>(KeyModifier::Shift))
        {
            out.push_back("Shift");
        }
        if (value & static_cast<size_t>(KeyModifier::Control))
        {
            out.push_back("Ctrl");
        }
        if (value & static_cast<size_t>(KeyModifier::Alt))
        {
            out.push_back("Alt");
        }
        if (value & static_cast<size_t>(KeyModifier::Super))
        {
            out.push_back("Cmd");
        }
        return join(out, '+');
    }

    DTK_ENUM_IMPL(
        Key,
        "Unknown",
        "Space",
        "Apostrophe",
        "Comma",
        "Minus",
        "Period",
        "Slash",
        "0",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "Semicolon",
        "Equal",
        "A",
        "B",
        "C",
        "D",
        "E",
        "F",
        "G",
        "H",
        "I",
        "J",
        "K",
        "L",
        "M",
        "N",
        "O",
        "P",
        "Q",
        "R",
        "S",
        "T",
        "U",
        "V",
        "W",
        "X",
        "Y",
        "Z",
        "LeftBracket",
        "Backslash",
        "RightBracket",
        "GraveAccent",
        "Escape",
        "Enter",
        "Tab",
        "Backspace",
        "Insert",
        "Delete",
        "Right",
        "Left",
        "Down",
        "Up",
        "PageUp",
        "PageDown",
        "Home",
        "End",
        "CapsLock",
        "ScrollLock",
        "NumLock",
        "PrintScreen",
        "Pause",
        "F1",
        "F2",
        "F3",
        "F4",
        "F5",
        "F6",
        "F7",
        "F8",
        "F9",
        "F10",
        "F11",
        "F12",
        "LeftShift",
        "LeftControl",
        "LeftAlt",
        "LeftSuper",
        "RightShift",
        "RightControl",
        "RightAlt",
        "RightSuper");

    std::string getShortcutLabel(Key key, int modifiers)
    {
        std::stringstream ss;
        if (key != Key::Unknown)
        {
            if (modifiers)
            {
                ss << getKeyModifierLabel(modifiers);
                ss << "+";
            }
            ss << key;
        }
        return ss.str();
    }

    KeyEvent::KeyEvent(
        Key        key,
        int        modifiers,
        const V2I& pos) :
        key(key),
        modifiers(modifiers),
        pos(pos)
    {}

    TextEvent::TextEvent(const std::string& text) :
        text(text)
    {}

    TextDragAndDropData::TextDragAndDropData(const std::string& text) :
        _text(text)
    {}

    TextDragAndDropData::~TextDragAndDropData()
    {}

    const std::string& TextDragAndDropData::getText() const
    {
        return _text;
    }

    DragAndDropEvent::DragAndDropEvent(
        const V2I& pos,
        const V2I& prev,
        const std::shared_ptr<DragAndDropData>& data) :
        pos(pos),
        prev(prev),
        data(data)
    {}
}