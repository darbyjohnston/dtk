// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/ComboBox.h>
#include <feather-tk/ui/IButton.h>
#include <feather-tk/ui/IMenuPopup.h>

namespace feather_tk
{
    class ComboBoxButton : public IButton
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const ComboBoxItem&,
            const std::shared_ptr<IWidget>& parent);

        ComboBoxButton();

    public:
        virtual ~ComboBoxButton();

        static std::shared_ptr<ComboBoxButton> create(
            const std::shared_ptr<Context>&,
            const ComboBoxItem&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setCurrent(bool);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;
        void clipEvent(const Box2I&, bool) override;
        void drawEvent(const Box2I&, const DrawEvent&) override;

    private:
        FEATHER_TK_PRIVATE();
    };

    class ComboBoxMenu : public IMenuPopup
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::vector<ComboBoxItem>&,
            int currentIndex,
            const std::shared_ptr<IWidget>& parent);

        ComboBoxMenu();

    public:
        virtual ~ComboBoxMenu();

        static std::shared_ptr<ComboBoxMenu> create(
            const std::shared_ptr<Context>&,
            const std::vector<ComboBoxItem>&,
            int currentIndex,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setCallback(const std::function<void(int)>&);

        void setGeometry(const Box2I&) override;
        void keyFocusEvent(bool) override;
        void keyPressEvent(KeyEvent&) override;
        void keyReleaseEvent(KeyEvent&) override;

    private:
        void _setCurrent(int);
        void _currentUpdate();
        void _scrollToCurrent();

        FEATHER_TK_PRIVATE();
    };
}
