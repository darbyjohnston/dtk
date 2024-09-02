// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IPopup.h>

namespace dtk
{
    namespace ui
    {
        class IWindow;

        //! \name Popup Widgets
        ///@{

        //! Base class for popup widgets.
        class IWidgetPopup : public IPopup
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string& objectName,
                const std::shared_ptr<IWidget>& parent = nullptr);

            IWidgetPopup();

        public:
            virtual ~IWidgetPopup() = 0;

            //! Open the popup.
            void open(
                const std::shared_ptr<IWindow>&,
                const core::Box2I& buttonGeometry);

            //! Get whether the popup is open.
            bool isOpen() const;

            //! Close the popup.
            void close() override;

            //! Set the close callback.
            void setCloseCallback(const std::function<void(void)>&);

            //! Get the widget.
            const std::shared_ptr<IWidget>& getWidget() const;

            //! Set the widget.
            void setWidget(const std::shared_ptr<IWidget>&);

            //! Get the popup color role.
            ColorRole getPopupRole() const;

            //! Set the popup color role.
            void setPopupRole(ColorRole);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;
            void keyPressEvent(KeyEvent&) override;
            void keyReleaseEvent(KeyEvent&) override;

        private:
            DTK_PRIVATE();
        };

        ///@}
    }
}
