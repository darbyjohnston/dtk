// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWidget.h>

namespace dtk
{
    //! \name Layouts
    ///@{
        
    //! Group box.
    class GroupBox : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        GroupBox();

    public:
        virtual ~GroupBox();

        //! Create a new widget.
        static std::shared_ptr<GroupBox> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Create a new widget.
        static std::shared_ptr<GroupBox> create(
            const std::shared_ptr<Context>&,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the text.
        const std::string& getText() const;

        //! Set the text.
        void setText(const std::string&);

        //! Get the font role.
        FontRole getFontRole() const;

        //! Set the font role.
        void setFontRole(FontRole);

        //! Remove all children from the group box.
        void clear();

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;
        void clipEvent(const Box2I&, bool) override;
        void drawEvent(const Box2I&, const DrawEvent&) override;

    private:
        DTK_PRIVATE();
    };
        
    ///@}
}
