// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkUI/IconLibrary.h>
#include <dtkUI/Style.h>

#include <dtkCore/FontSystem.h>
#include <dtkCore/IRender.h>

namespace dtk
{
    namespace ui
    {
        class IWidget;

        //! \name Events
        ///@{
        
        //! Child added event.
        struct ChildAddEvent
        {
            ChildAddEvent(const std::shared_ptr<IWidget>&);

            std::shared_ptr<IWidget> child;
        };

        //! Child removed event.
        struct ChildRemoveEvent
        {
            ChildRemoveEvent(const std::shared_ptr<IWidget>&, int index);

            std::shared_ptr<IWidget> child;
            int index = 0;
        };

        //! Tick event.
        struct TickEvent
        {
        };

        //! Size hint event.
        struct SizeHintEvent
        {
            SizeHintEvent(
                const std::shared_ptr<core::FontSystem>&,
                float displayScale,
                const std::shared_ptr<Style>&,
                const std::shared_ptr<IconLibrary>&);

            std::shared_ptr<core::FontSystem> fontSystem;
            float                             displayScale = 1.F;
            std::shared_ptr<Style>            style;
            std::shared_ptr<IconLibrary>      iconLibrary;
        };

        //! Draw event.
        struct DrawEvent
        {
            DrawEvent(
                const std::shared_ptr<core::FontSystem>&,
                float displayScale,
                const std::shared_ptr<Style>&,
                const std::shared_ptr<IconLibrary>&,
                const std::shared_ptr<core::IRender>&);

            std::shared_ptr<core::FontSystem> fontSystem;
            float                             displayScale = 1.F;
            std::shared_ptr<Style>            style;
            std::shared_ptr<IconLibrary>      iconLibrary;
            std::shared_ptr<core::IRender>    render;
        };

        //! Drag and drop data.
        class DragAndDropData : public std::enable_shared_from_this<DragAndDropData>
        {
        public:
            virtual ~DragAndDropData() = 0;
        };

        //! Mouse move event.
        struct MouseMoveEvent
        {
            MouseMoveEvent(
                const core::V2I& pos,
                const core::V2I& prev);

            core::V2I                        pos;
            core::V2I                        prev;
            bool                             accept = false;
            std::shared_ptr<DragAndDropData> dndData;
            std::shared_ptr<core::Image>     dndCursor;
            core::V2I                        dndCursorHotspot;
        };

        //! Keyboard modifiers.
        enum class KeyModifier
        {
            None    = 0,
            Shift   = 1,
            Control = 2,
            Alt     = 4,
            Super   = 8
        };

        //! OS specific command key modifier.
#if defined(__APPLE__)
        const KeyModifier commandKeyModifier = KeyModifier::Super;
#else // __APPLE__
        const KeyModifier commandKeyModifier = KeyModifier::Control;
#endif // __APPLE__

        //! Get a keyboard modifier label.
        std::string getKeyModifierLabel(int);

        //! Mouse click event.
        struct MouseClickEvent
        {
            MouseClickEvent() = default;
            MouseClickEvent(
                int              button,
                int              modifiers,
                const core::V2I& pos);

            int       button    = 0;
            int       modifiers = 0;
            core::V2I pos;
            bool      accept    = false;
        };

        //! Scroll event (mouse wheel or touch pad).
        struct ScrollEvent
        {
            ScrollEvent(
                const core::V2F& value,
                int              modifiers,
                const core::V2I& pos);

            core::V2F value;
            int       modifiers = 0;
            core::V2I pos;
            bool      accept    = false;
        };

        //! Keys.
        enum class Key
        {
            Unknown,
            Space,
            Apostrophe, // '
            Comma,      // ,
            Minus,      // -
            Period,     // .
            Slash,      // /
            _0,
            _1,
            _2,
            _3,
            _4,
            _5,
            _6,
            _7,
            _8,
            _9,
            Semicolon, // ;
            Equal,     // = 
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
            LeftBracket,  // [
            Backslash,    // '\'
            RightBracket, // ]
            GraveAccent,  // `
            Escape,
            Enter,
            Tab,
            Backspace,
            Insert,
            Delete,
            Right,
            Left,
            Down,
            Up,
            PageUp,
            PageDown,
            Home,
            End,
            CapsLock,
            ScrollLock,
            NumLock,
            PrintScreen,
            Pause,
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,
            LeftShift,
            LeftControl,
            LeftAlt,
            LeftSuper,
            RightShift,
            RightControl,
            RightAlt,
            RightSuper,

            Count,
            First = Unknown
        };
        DTK_ENUM(Key);

        //! Get a keyboard shortcut label.
        std::string getShortcutLabel(Key, int modifiers = 0);

        //! Key event.
        struct KeyEvent
        {
            KeyEvent() = default;
            KeyEvent(
                Key              key,
                int              modifiers,
                const core::V2I& pos);

            Key       key       = Key::Unknown;
            int       modifiers = 0;
            core::V2I pos;
            bool      accept    = false;
        };

        //! Text event.
        struct TextEvent
        {
            TextEvent(const std::string& text);

            std::string text;
            bool        accept = false;
        };

        //! Drag and drop text data.
        class TextDragAndDropData : public DragAndDropData
        {
        public:
            TextDragAndDropData(const std::string& text);

            virtual ~TextDragAndDropData();

            const std::string& getText() const;

        private:
            std::string _text;
        };

        //! Drag and drop event.
        struct DragAndDropEvent
        {
            DragAndDropEvent(
                const core::V2I&                        pos,
                const core::V2I&                        prev,
                const std::shared_ptr<DragAndDropData>& data);

            core::V2I                        pos;
            core::V2I                        prev;
            std::shared_ptr<DragAndDropData> data;
            bool                             accept = false;
        };
        
        ///@}
    }
}

