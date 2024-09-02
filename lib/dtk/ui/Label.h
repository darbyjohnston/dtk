// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWidget.h>

namespace dtk
{
    namespace ui
    {
        //! \name Text Widgets
        ///@{
        
        //! Text label.
        //! 
        //! \todo Add text wrapping.
        class Label : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<IWidget>& parent);

            Label();

        public:
            virtual ~Label();

            //! Create a new widget.
            static std::shared_ptr<Label> create(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Create a new widget.
            static std::shared_ptr<Label> create(
                const std::shared_ptr<Context>&,
                const std::string& text,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the text.
            const std::string& getText() const;

            //! Set the text.
            void setText(const std::string&);

            //! Get the text color role.
            ColorRole getTextRole() const;

            //! Set the text color role.
            void setTextRole(ColorRole);

            //! Get the margin role.
            SizeRole getMarginRole() const;

            //! Set the margin role.
            void setMarginRole(SizeRole);

            //! Get the font role.
            FontRole getFontRole() const;

            //! Set the font role.
            void setFontRole(FontRole);

            void setGeometry(const Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void clipEvent(const Box2I&, bool) override;
            void drawEvent(const Box2I&, const DrawEvent&) override;

        private:
            DTK_PRIVATE();
        };
        
        ///@}
    }
}
