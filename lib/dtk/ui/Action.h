// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/Event.h>

namespace dtk
{
    //! \name Actions
    ///@{

    //! Action.
    struct Action
    {
        Action();
        Action(
            const std::string&               text,
            const std::function<void(void)>& callback);
        Action(
            const std::string&               text,
            const std::string&               icon,
            const std::function<void(void)>& callback);
        Action(
            const std::string&               text,
            Key                              shortcut,
            int                              shortcutModifiers,
            const std::function<void(void)>& callback);
        Action(
            const std::string&               text,
            const std::string&               icon,
            Key                              shortcut,
            int                              shortcutModifiers,
            const std::function<void(void)>& callback);
        Action(
            const std::string&               text,
            const std::function<void(bool)>& checkedCallback);
        Action(
            const std::string&               text,
            const std::string&               icon,
            const std::function<void(bool)>& checkedCallback);
        Action(
            const std::string&               text,
            Key                              shortcut,
            int                              shortcutModifiers,
            const std::function<void(bool)>& checkedCallback);
        Action(
            const std::string&               text,
            const std::string&               icon,
            Key                              shortcut,
            int                              shortcutModifiers,
            const std::function<void(bool)>& checkedCallback);

        std::string               text;
        std::string               icon;
        std::string               checkedIcon;
        Key                       shortcut          = Key::Unknown;
        int                       shortcutModifiers = 0;
        std::function<void(void)> callback;
        bool                      checkable         = false;
        bool                      checked           = false;
        std::function<void(bool)> checkedCallback;
        std::string               toolTip;
    };

    ///@}
}
