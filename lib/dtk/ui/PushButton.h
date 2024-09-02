// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IButton.h>

namespace dtk
{
    namespace ui
    {
        //! \name Buttons
        ///@{
        
        //! Push button.
        class PushButton : public IButton
        {
        protected:
            void _init(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<IWidget>& parent);

            PushButton();

        public:
            virtual ~PushButton();

            //! Create a new widget.
            static std::shared_ptr<PushButton> create(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Create a new widget.
            static std::shared_ptr<PushButton> create(
                const std::shared_ptr<Context>&,
                const std::string& text,
                const std::shared_ptr<IWidget>& parent = nullptr);

            void setText(const std::string&) override;
            void setFontRole(FontRole) override;

            void setGeometry(const Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void clipEvent(const Box2I&, bool) override;
            void drawEvent(const Box2I&, const DrawEvent&) override;
            void keyPressEvent(KeyEvent&) override;
            void keyReleaseEvent(KeyEvent&) override;

        private:
            DTK_PRIVATE();
        };
        
        ///@}
    }
}