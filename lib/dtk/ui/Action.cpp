// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/Action.h>

namespace dtk
{
    Action::Action()
    {}

    Action::Action(
        const std::string& text,
        const std::function<void(void)>& callback) :
        text(text),
        callback(callback)
    {}

    Action::Action(
        const std::string& text,
        const std::string& icon,
        const std::function<void(void)>& callback) :
        text(text),
        icon(icon),
        callback(callback)
    {}

    Action::Action(
        const std::string& text,
        Key                              shortcut,
        int                              shortcutModifiers,
        const std::function<void(void)>& callback) :
        text(text),
        shortcut(shortcut),
        shortcutModifiers(shortcutModifiers),
        callback(callback)
    {}

    Action::Action(
        const std::string& text,
        const std::string& icon,
        Key                              shortcut,
        int                              shortcutModifiers,
        const std::function<void(void)>& callback) :
        text(text),
        icon(icon),
        shortcut(shortcut),
        shortcutModifiers(shortcutModifiers),
        callback(callback)
    {}

    Action::Action(
        const std::string& text,
        const std::function<void(bool)>& checkedCallback) :
        text(text),
        checkable(true),
        checkedCallback(checkedCallback)
    {}

    Action::Action(
        const std::string& text,
        const std::string& icon,
        const std::function<void(bool)>& checkedCallback) :
        text(text),
        icon(icon),
        checkable(true),
        checkedCallback(checkedCallback)
    {}

    Action::Action(
        const std::string& text,
        Key                              shortcut,
        int                              shortcutModifiers,
        const std::function<void(bool)>& checkedCallback) :
        text(text),
        shortcut(shortcut),
        shortcutModifiers(shortcutModifiers),
        checkable(true),
        checkedCallback(checkedCallback)
    {}

    Action::Action(
        const std::string& text,
        const std::string& icon,
        Key                              shortcut,
        int                              shortcutModifiers,
        const std::function<void(bool)>& checkedCallback) :
        text(text),
        icon(icon),
        shortcut(shortcut),
        shortcutModifiers(shortcutModifiers),
        checkable(true),
        checkedCallback(checkedCallback)
    {}
}