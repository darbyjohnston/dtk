// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
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
        void setFullScreen(bool, int screen = -1);

        //! Get which screen the window is on.
        int getScreen() const;

        //! Get whether the window is floating on top.
        bool isFloatOnTop() const;

        //! Observe whether the window is floating on top.
        std::shared_ptr<dtk::IObservableValue<bool> > observeFloatOnTop() const;

        //! Set whether the window is floating on top.
        void setFloatOnTop(bool);

        //! Get whether the window should close.
        bool shouldClose() const;

        //! Get the window frame buffer size.
        const Size2I& getFrameBufferSize() const;

        //! Get the frame buffer type.
        dtk::ImageType getFrameBufferType() const;

        //! Observe the frame buffer type.
        std::shared_ptr<dtk::IObservableValue<dtk::ImageType> > observeFrameBufferType() const;

        //! Set the frame buffer type.
        void setFrameBufferType(dtk::ImageType);

        //! Get the display scale.
        float getDisplayScale() const;

        //! Observe the display scale.
        std::shared_ptr<IObservableValue<float> > observeDisplayScale() const;

        //! Set the display scale. A value of zero will set the display scale
        //! automatically.
        void setDisplayScale(float);

        //! Update the window.
        void update(
            const std::shared_ptr<FontSystem>&,
            const std::shared_ptr<IconSystem>&,
            const std::shared_ptr<Style>&);

        void setGeometry(const Box2I&) override;
        void setVisible(bool) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    protected:
        virtual std::shared_ptr<IRender> _createRender(const std::shared_ptr<Context>&);

        void _makeCurrent();

    private:
        DTK_PRIVATE();
    };
}
