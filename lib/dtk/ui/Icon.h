// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWidget.h>

namespace dtk
{
    //! \name Icons
    ///@{
        
    //! Icon widget.
    class Icon : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        Icon();

    public:
        virtual ~Icon();

        //! Create a new widget.
        static std::shared_ptr<Icon> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Create a new widget.
        static std::shared_ptr<Icon> create(
            const std::shared_ptr<Context>&,
            const std::string& icon,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the icon.
        const std::string& getIcon() const;

        //! Set the icon.
        void setIcon(const std::string&);

        //! Get the margin role.
        SizeRole getMarginRole() const;

        //! Set the margin role.
        void setMarginRole(SizeRole);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;
        void drawEvent(const Box2I&, const DrawEvent&) override;

    private:
        DTK_PRIVATE();
    };
        
    ///@}
}
