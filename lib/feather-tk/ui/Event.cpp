// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/Event.h>

#include <feather-tk/core/Error.h>
#include <feather-tk/core/String.h>

#include <sstream>

namespace feather_tk
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
        const std::shared_ptr<IconSystem>& iconSystem,
        float                              displayScale,
        const std::shared_ptr<Style>&      style) :
        fontSystem(fontSystem),
        iconSystem(iconSystem),
        displayScale(displayScale),
        style(style)
    {}

    DrawEvent::DrawEvent(
        const std::shared_ptr<FontSystem>& fontSystem,
        const std::shared_ptr<IconSystem>& iconSystem,
        float                              displayScale,
        const std::shared_ptr<Style>&      style,
        const std::shared_ptr<IRender>&    render) :
        fontSystem(fontSystem),
        iconSystem(iconSystem),
        displayScale(displayScale),
        style(style),
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

    namespace
    {
        std::map<KeyModifier, std::string> keyModifierLabels =
        {
            { KeyModifier::None, "None" },
            { KeyModifier::Shift, "Shift" },
            { KeyModifier::Control, "Ctrl" },
            { KeyModifier::Alt, "Alt" },
            { KeyModifier::Super, "Cmd" }
        };
    }

    std::string to_string(KeyModifier value)
    {
        return keyModifierLabels[value];
    }

    void from_string(const std::string& s, KeyModifier& value)
    {
        for (auto i = keyModifierLabels.begin(); i != keyModifierLabels.end(); ++i)
        {
            if (compare(s, i->second, CaseCompare::Insensitive))
            {
                value = i->first;
                break;
            }
        }
    }

    bool checkKeyModifier(KeyModifier modifier, int modifiers)
    {
        return (KeyModifier::None == modifier && 0 == modifiers) ?
            true :
            (modifiers & static_cast<int>(modifier));
    }

    std::string getKeyModifierLabel(int value)
    {
        std::vector<std::string> out;
        if (value & static_cast<size_t>(KeyModifier::Shift))
        {
            out.push_back(to_string(KeyModifier::Shift));
        }
        if (value & static_cast<size_t>(KeyModifier::Control))
        {
            out.push_back(to_string(KeyModifier::Control));
        }
        if (value & static_cast<size_t>(KeyModifier::Alt))
        {
            out.push_back(to_string(KeyModifier::Alt));
        }
        if (value & static_cast<size_t>(KeyModifier::Super))
        {
            out.push_back(to_string(KeyModifier::Super));
        }
        return join(out, '+');
    }

    FEATHER_TK_ENUM_IMPL(
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
