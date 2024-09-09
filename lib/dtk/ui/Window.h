// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWindow.h>

namespace dtk
{
    //! Window.
    class Window : public IWindow
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::string& name,
            const Size2I&);

        Window();

    public:
        virtual ~Window();

        //! Create a new window.
        static std::shared_ptr<Window> create(
            const std::shared_ptr<Context>&,
            const std::string& name,
            const Size2I&);

        //! Get the window size.
        const Size2I& getSize() const;

        //! Set the window size.
        void setSize(const Size2I&);

        //! Get whether the window is full screen.
        bool isFullScreen() const;

        //! Observe whether the window is full screen.
        std::shared_ptr<IObservableValue<bool> > observeFullScreen() const;

        //! Set whether the window is full screen.
        void setFullScreen(bool);

        //! Get the window frame buffer size.
        const Size2I& getFrameBufferSize() const;

        //! Get the display scale.
        float getDisplayScale() const;

        //! Observe the display scale.
        std::shared_ptr<IObservableValue<float> > observeDisplayScale() const;

        //! Set the display scale. A value of zero will set the display scale
        //! automatically.
        void setDisplayScale(float);

        //! Get whether the window should close.
        bool shouldClose() const;

        //! Update the window.
        void update(
            const std::shared_ptr<FontSystem>&,
            const std::shared_ptr<Style>&,
            const std::shared_ptr<IconLibrary>&);

        void setGeometry(const Box2I&) override;
        void setVisible(bool) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        DTK_PRIVATE();
    };
}