// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/IWidget.h>

namespace feather_tk
{
    //! \name Layouts
    ///@{
        
    //! Base class for dock widgets.
    class IDockWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        IDockWidget();

    public:
        virtual ~IDockWidget();

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        FEATHER_TK_PRIVATE();
    };
        
    //! Dock layout.
    class DockLayout : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        DockLayout();

    public:
        virtual ~DockLayout();

        //! Create a new layout.
        static std::shared_ptr<DockLayout> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        FEATHER_TK_PRIVATE();
    };
        
    ///@}
}
