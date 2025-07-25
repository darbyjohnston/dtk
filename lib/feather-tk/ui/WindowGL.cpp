// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/Window.h>

#include <feather-tk/gl/GL.h>
#include <feather-tk/gl/OffscreenBuffer.h>
#include <feather-tk/gl/Render.h>
#include <feather-tk/gl/Window.h>
#if defined(FEATHER_TK_API_GLES_2)
#include <feather-tk/gl/Mesh.h>
#include <feather-tk/gl/Shader.h>
#endif // FEATHER_TK_API_GLES_2

#include <feather-tk/ui/IClipboard.h>
#include <feather-tk/ui/IconSystem.h>
#include <feather-tk/ui/Style.h>

#include <feather-tk/core/Context.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/LogSystem.h>
#include <feather-tk/core/FontSystem.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <codecvt>
#include <locale>

namespace feather_tk
{
    namespace
    {
        class Clipboard : public IClipboard
        {
        protected:
            Clipboard()
            {}

        public:
            virtual ~Clipboard()
            {}

            static std::shared_ptr<Clipboard> create(
                const std::shared_ptr<Context>& context,
                GLFWwindow* glfwWindow)
            {
                auto out = std::shared_ptr<Clipboard>(new Clipboard);
                out->_init(context);
                out->_glfwWindow = glfwWindow;
                return out;
            }

            std::string getText() const override
            {
                return glfwGetClipboardString(_glfwWindow);
            }

            void setText(const std::string& value) override
            {
                glfwSetClipboardString(_glfwWindow, value.c_str());
            }

        private:
            GLFWwindow* _glfwWindow = nullptr;
        };

        int fromGLFWModifiers(int value)
        {
            int out = 0;
            if (value & GLFW_MOD_SHIFT)
            {
                out |= static_cast<int>(KeyModifier::Shift);
            }
            if (value & GLFW_MOD_CONTROL)
            {
                out |= static_cast<int>(KeyModifier::Control);
            }
            if (value & GLFW_MOD_ALT)
            {
                out |= static_cast<int>(KeyModifier::Alt);
            }
            if (value & GLFW_MOD_SUPER)
            {
                out |= static_cast<int>(KeyModifier::Super);
            }
            return out;
        }

        Key fromGLFWKey(int key)
        {
            Key out = Key::Unknown;
            switch (key)
            {
            case GLFW_KEY_SPACE: out = Key::Space; break;
            case GLFW_KEY_APOSTROPHE: out = Key::Apostrophe; break;
            case GLFW_KEY_COMMA: out = Key::Comma; break;
            case GLFW_KEY_MINUS: out = Key::Minus; break;
            case GLFW_KEY_PERIOD: out = Key::Period; break;
            case GLFW_KEY_SLASH: out = Key::Slash; break;
            case GLFW_KEY_0: out = Key::_0; break;
            case GLFW_KEY_1: out = Key::_1; break;
            case GLFW_KEY_2: out = Key::_2; break;
            case GLFW_KEY_3: out = Key::_3; break;
            case GLFW_KEY_4: out = Key::_4; break;
            case GLFW_KEY_5: out = Key::_5; break;
            case GLFW_KEY_6: out = Key::_6; break;
            case GLFW_KEY_7: out = Key::_7; break;
            case GLFW_KEY_8: out = Key::_8; break;
            case GLFW_KEY_9: out = Key::_9; break;
            case GLFW_KEY_SEMICOLON: out = Key::Semicolon; break;
            case GLFW_KEY_EQUAL: out = Key::Equal; break;
            case GLFW_KEY_A: out = Key::A; break;
            case GLFW_KEY_B: out = Key::B; break;
            case GLFW_KEY_C: out = Key::C; break;
            case GLFW_KEY_D: out = Key::D; break;
            case GLFW_KEY_E: out = Key::E; break;
            case GLFW_KEY_F: out = Key::F; break;
            case GLFW_KEY_G: out = Key::G; break;
            case GLFW_KEY_H: out = Key::H; break;
            case GLFW_KEY_I: out = Key::I; break;
            case GLFW_KEY_J: out = Key::J; break;
            case GLFW_KEY_K: out = Key::K; break;
            case GLFW_KEY_L: out = Key::L; break;
            case GLFW_KEY_M: out = Key::M; break;
            case GLFW_KEY_N: out = Key::N; break;
            case GLFW_KEY_O: out = Key::O; break;
            case GLFW_KEY_P: out = Key::P; break;
            case GLFW_KEY_Q: out = Key::Q; break;
            case GLFW_KEY_R: out = Key::R; break;
            case GLFW_KEY_S: out = Key::S; break;
            case GLFW_KEY_T: out = Key::T; break;
            case GLFW_KEY_U: out = Key::U; break;
            case GLFW_KEY_V: out = Key::V; break;
            case GLFW_KEY_W: out = Key::W; break;
            case GLFW_KEY_X: out = Key::X; break;
            case GLFW_KEY_Y: out = Key::Y; break;
            case GLFW_KEY_Z: out = Key::Z; break;
            case GLFW_KEY_LEFT_BRACKET: out = Key::LeftBracket; break;
            case GLFW_KEY_BACKSLASH: out = Key::Backslash; break;
            case GLFW_KEY_RIGHT_BRACKET: out = Key::RightBracket; break;
            case GLFW_KEY_GRAVE_ACCENT: out = Key::GraveAccent; break;
            case GLFW_KEY_ESCAPE: out = Key::Escape; break;
            case GLFW_KEY_ENTER: out = Key::Enter; break;
            case GLFW_KEY_TAB: out = Key::Tab; break;
            case GLFW_KEY_BACKSPACE: out = Key::Backspace; break;
            case GLFW_KEY_INSERT: out = Key::Insert; break;
            case GLFW_KEY_DELETE: out = Key::Delete; break;
            case GLFW_KEY_RIGHT: out = Key::Right; break;
            case GLFW_KEY_LEFT: out = Key::Left; break;
            case GLFW_KEY_DOWN: out = Key::Down; break;
            case GLFW_KEY_UP: out = Key::Up; break;
            case GLFW_KEY_PAGE_UP: out = Key::PageUp; break;
            case GLFW_KEY_PAGE_DOWN: out = Key::PageDown; break;
            case GLFW_KEY_HOME: out = Key::Home; break;
            case GLFW_KEY_END: out = Key::End; break;
            case GLFW_KEY_CAPS_LOCK: out = Key::CapsLock; break;
            case GLFW_KEY_SCROLL_LOCK: out = Key::ScrollLock; break;
            case GLFW_KEY_NUM_LOCK: out = Key::NumLock; break;
            case GLFW_KEY_PRINT_SCREEN: out = Key::PrintScreen; break;
            case GLFW_KEY_PAUSE: out = Key::Pause; break;
            case GLFW_KEY_F1: out = Key::F1; break;
            case GLFW_KEY_F2: out = Key::F2; break;
            case GLFW_KEY_F3: out = Key::F3; break;
            case GLFW_KEY_F4: out = Key::F4; break;
            case GLFW_KEY_F5: out = Key::F5; break;
            case GLFW_KEY_F6: out = Key::F6; break;
            case GLFW_KEY_F7: out = Key::F7; break;
            case GLFW_KEY_F8: out = Key::F8; break;
            case GLFW_KEY_F9: out = Key::F9; break;
            case GLFW_KEY_F10: out = Key::F10; break;
            case GLFW_KEY_F11: out = Key::F11; break;
            case GLFW_KEY_F12: out = Key::F12; break;
            case GLFW_KEY_LEFT_SHIFT: out = Key::LeftShift; break;
            case GLFW_KEY_LEFT_CONTROL: out = Key::LeftControl; break;
            case GLFW_KEY_LEFT_ALT: out = Key::LeftAlt; break;
            case GLFW_KEY_LEFT_SUPER: out = Key::LeftSuper; break;
            case GLFW_KEY_RIGHT_SHIFT: out = Key::RightShift; break;
            case GLFW_KEY_RIGHT_CONTROL: out = Key::RightControl; break;
            case GLFW_KEY_RIGHT_ALT: out = Key::RightAlt; break;
            case GLFW_KEY_RIGHT_SUPER: out = Key::RightSuper; break;
            }
            return out;
        }

#if defined(_WINDOWS)
        //! \bug https://social.msdn.microsoft.com/Forums/vstudio/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error?forum=vcgeneral
        typedef unsigned int feather_tk_char_t;
#else // _WINDOWS
        typedef char32_t feather_tk_char_t;
#endif // _WINDOWS
    }

    struct Window::Private
    {
        std::weak_ptr<Context> context;

        std::shared_ptr<ObservableValue<bool> > fullScreen;
        std::shared_ptr<ObservableValue<bool> > floatOnTop;
        Size2I bufferSize = Size2I(0, 0);
        std::shared_ptr<ObservableValue<ImageType> > bufferType;
        V2F contentScale = V2F(1.F, 1.F);
        std::shared_ptr<ObservableValue<float> > displayScale;
        bool refresh = true;
        int modifiers = 0;
        std::shared_ptr<gl::Window> window;
        std::function<void(void)> closeCallback;

        std::shared_ptr<gl::OffscreenBuffer> buffer;
        std::shared_ptr<IRender> render;
#if defined(FEATHER_TK_API_GLES_2)
        std::shared_ptr<gl::Shader> shader;
#endif // FEATHER_TK_API_GLES_2
    };

    void Window::_init(
        const std::shared_ptr<Context>& context,
        const std::string& name,
        const Size2I& size)
    {
        IWindow::_init(context, name, nullptr);
        FEATHER_TK_P();

        p.context = context;

        p.fullScreen = ObservableValue<bool>::create(false);
        p.floatOnTop = ObservableValue<bool>::create(false);
        p.bufferType = ObservableValue<ImageType>::create(gl::offscreenColorDefault);
        p.displayScale = ObservableValue<float>::create(0.F);

        p.window = gl::Window::create(
            context,
            name,
            size,
            static_cast<int>(gl::WindowOptions::DoubleBuffer));
        p.window->setSizeCallback(
            [this](const Size2I& value)
            {
                _setSizeUpdate();
                _setDrawUpdate();
            });
        p.window->setFrameBufferSizeCallback(
            [this](const Size2I& value)
            {
                _p->bufferSize = value;
                _setSizeUpdate();
                _setDrawUpdate();
            });
        p.window->setContentScaleCallback(
            [this](const V2F& value)
            {
                _p->contentScale = value;
                _setSizeUpdate();
                _setDrawUpdate();
            });
        p.window->setRefreshCallback(
            [this]()
            {
                _p->refresh = true;
            });
        p.window->setFullScreenCallback(
            [this](bool value)
            {
                _p->fullScreen->setIfChanged(value);
            });
        p.window->setCursorEnterCallback(
            [this](bool value)
            {
                _cursorEnter(value);
            });
        p.window->setCursorPosCallback(
            [this](const V2F& value)
            {
                V2I pos;
#if defined(__APPLE__)
                //! \bug The mouse position needs to be scaled on macOS?
                pos.x = value.x * _p->contentScale.x;
                pos.y = value.y * _p->contentScale.y;
#else // __APPLE__
                pos.x = value.x;
                pos.y = value.y;
#endif // __APPLE__
                _cursorPos(pos);
            });
        p.window->setButtonCallback(
            [this](int button, int action, int modifiers)
            {
                _p->modifiers = modifiers;
                _mouseButton(
                    button,
                    GLFW_PRESS == action,
                    fromGLFWModifiers(modifiers));
            });
        p.window->setScrollCallback(
            [this](const V2F& value)
            {
                _scroll(value, fromGLFWModifiers(_p->modifiers));
            });
        p.window->setKeyCallback(
            [this](int key, int scanCode, int action, int modifiers)
            {
                FEATHER_TK_P();
                p.modifiers = modifiers;
                switch (action)
                {
                case GLFW_PRESS:
                case GLFW_REPEAT:
                    _key(
                        fromGLFWKey(key),
                        true,
                        fromGLFWModifiers(modifiers));
                    break;
                case GLFW_RELEASE:
                    _key(
                        fromGLFWKey(key),
                        false,
                        fromGLFWModifiers(modifiers));
                    break;
                }
            });
        p.window->setCharCallback(
            [this](unsigned int c)
            {
                std::wstring_convert<std::codecvt_utf8<feather_tk_char_t>, feather_tk_char_t> utf32Convert;
                _text(utf32Convert.to_bytes(c));
            });
        p.window->setDropCallback(
            [this](int count, const char** paths)
            {
                std::vector<std::string> tmp;
                for (int i = 0; i < count; ++i)
                {
                    tmp.push_back(paths[i]);
                }
                _drop(tmp);
            });
        p.window->setCloseCallback(
            [this]
            {
                hide();
                if (_p->closeCallback)
                {
                    _p->closeCallback();
                }
            });

        p.bufferSize = p.window->getFrameBufferSize();
        p.contentScale = p.window->getContentScale();
        p.render = _createRender(context);

        setClipboard(Clipboard::create(context, p.window->getGLFW()));

        _setSizeUpdate();
        _setDrawUpdate();
    }

    Window::Window() :
        _p(new Private)
    {}

    Window::~Window()
    {
        FEATHER_TK_P();
        p.window->makeCurrent();
        p.render.reset();
        p.buffer.reset();
        p.window->doneCurrent();
    }

    std::shared_ptr<Window> Window::create(
        const std::shared_ptr<Context>& context,
        const std::string& name,
        const Size2I& size)
    {
        auto out = std::shared_ptr<Window>(new Window);
        out->_init(context, name, size);
        return out;
    }

    const Size2I& Window::getSize() const
    {
        return _p->window->getSize();
    }

    void Window::setSize(const Size2I& value)
    {
        _p->window->setSize(value);
    }

    bool Window::isFullScreen() const
    {
        return _p->window->isFullScreen();
    }

    std::shared_ptr<IObservableValue<bool> > Window::observeFullScreen() const
    {
        return _p->fullScreen;
    }

    void Window::setFullScreen(bool value, int screen)
    {
        _p->window->setFullScreen(value, screen);
    }

    int Window::getScreen() const
    {
        return _p->window->getScreen();
    }

    bool Window::isFloatOnTop() const
    {
        return _p->floatOnTop->get();
    }

    std::shared_ptr<IObservableValue<bool> > Window::observeFloatOnTop() const
    {
        return _p->floatOnTop;
    }

    void Window::setFloatOnTop(bool value)
    {
        FEATHER_TK_P();
        if (p.floatOnTop->setIfChanged(value))
        {
            p.window->setFloatOnTop(value);
        }
    }

    const Size2I& Window::getFrameBufferSize() const
    {
        return _p->bufferSize;
    }

    ImageType Window::getFrameBufferType() const
    {
        return _p->bufferType->get();
    }

    std::shared_ptr<IObservableValue<ImageType> > Window::observeFrameBufferType() const
    {
        return _p->bufferType;
    }

    void Window::setFrameBufferType(ImageType value)
    {
        if (_p->bufferType->setIfChanged(value))
        {
            _setDrawUpdate();
        }
    }

    float Window::getDisplayScale() const
    {
        FEATHER_TK_P();
        const float ds = p.displayScale->get();
        return ds > 0.F ? ds : p.contentScale.x;
    }

    std::shared_ptr<IObservableValue<float> > Window::observeDisplayScale() const
    {
        return _p->displayScale;
    }

    void Window::setDisplayScale(float value)
    {
        FEATHER_TK_P();
        if (p.displayScale->setIfChanged(value))
        {
            _setSizeUpdate();
            _setDrawUpdate();
        }
    }

    void Window::update(
        const std::shared_ptr<FontSystem>& fontSystem,
        const std::shared_ptr<IconSystem>& iconSystem,
        const std::shared_ptr<Style>& style)
    {
        FEATHER_TK_P();
        if (_hasSizeUpdate(shared_from_this()))
        {
            SizeHintEvent sizeHintEvent(
                fontSystem,
                iconSystem,
                getDisplayScale(),
                style);
            _sizeHintEventRecursive(shared_from_this(), sizeHintEvent);

            setGeometry(Box2I(V2I(), p.bufferSize));

            _clipEventRecursive(
                shared_from_this(),
                getGeometry(),
                !isVisible(false));
        }

        const bool drawUpdate = _hasDrawUpdate(shared_from_this());
        if (p.refresh || drawUpdate)
        {
            p.window->makeCurrent();

            gl::OffscreenBufferOptions bufferOptions;
            bufferOptions.color = p.bufferType->get();
            if (gl::doCreate(p.buffer, p.bufferSize, bufferOptions))
            {
                p.buffer = gl::OffscreenBuffer::create(p.bufferSize, bufferOptions);
            }

            if (p.buffer && drawUpdate)
            {
                gl::OffscreenBufferBinding bufferBinding(p.buffer);
                p.render->begin(p.bufferSize);
                p.render->setClipRectEnabled(true);
                DrawEvent drawEvent(
                    fontSystem,
                    iconSystem,
                    getDisplayScale(),
                    style,
                    p.render);
                _drawEventRecursive(
                    shared_from_this(),
                    Box2I(V2I(), p.bufferSize),
                    drawEvent);
                p.render->setClipRectEnabled(false);
                p.render->end();
            }

#if defined(FEATHER_TK_API_GL_4_1)
            if (p.buffer)
            {
                glBindFramebuffer(
                    GL_READ_FRAMEBUFFER,
                    p.buffer->getID());
                glBlitFramebuffer(
                    0,
                    0,
                    p.bufferSize.w,
                    p.bufferSize.h,
                    0,
                    0,
                    p.bufferSize.w,
                    p.bufferSize.h,
                    GL_COLOR_BUFFER_BIT,
                    GL_LINEAR);
            }
#elif defined(FEATHER_TK_API_GLES_2)
            if (!p.shader)
            {
                try
                {
                    const std::string vertexSource =
                        "precision mediump float;\n"
                        "\n"
                        "attribute vec3 vPos;\n"
                        "attribute vec2 vTexture;\n"
                        "varying vec2 fTexture;\n"
                        "\n"
                        "struct Transform\n"
                        "{\n"
                        "    mat4 mvp;\n"
                        "};\n"
                        "\n"
                        "uniform Transform transform;\n"
                        "\n"
                        "void main()\n"
                        "{\n"
                        "    gl_Position = transform.mvp * vec4(vPos, 1.0);\n"
                        "    fTexture = vTexture;\n"
                        "}\n";
                    const std::string fragmentSource =
                        "precision mediump float;\n"
                        "\n"
                        "varying vec2 fTexture;\n"
                        "\n"
                        "uniform sampler2D textureSampler;\n"
                        "\n"
                        "void main()\n"
                        "{\n"
                        "    gl_FragColor = texture2D(textureSampler, fTexture);\n"
                        "}\n";
                    p.shader = gl::Shader::create(vertexSource, fragmentSource);
                }
                catch (const std::exception& e)
                {
                    if (auto context = p.context.lock())
                    {
                        context->getSystem<LogSystem>()->print(
                            "feather_tk::Window",
                            Format("Cannot compile shader: {0}").arg(e.what()),
                            LogType::Error);
                    }
                }
            }
            if (p.shader)
            {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                glDisable(GL_BLEND);
                glDisable(GL_SCISSOR_TEST);

                p.shader->bind();
                p.shader->setUniform(
                    "transform.mvp",
                    ortho(
                        0.F,
                        static_cast<float>(p.bufferSize.w),
                        0.F,
                        static_cast<float>(p.bufferSize.h),
                        -1.F,
                        1.F));
                p.shader->setUniform("textureSampler", 0);

                glActiveTexture(static_cast<GLenum>(GL_TEXTURE0));
                glBindTexture(GL_TEXTURE_2D, p.buffer->getColorID());

                auto mesh = feather_tk::mesh(Box2I(
                    0,
                    0,
                    p.bufferSize.w,
                    p.bufferSize.h));
                auto vboData = gl::convert(
                    mesh,
                    gl::VBOType::Pos2_F32_UV_U16,
                    RangeSizeT(0, mesh.triangles.size() - 1));
                auto vbo = gl::VBO::create(mesh.triangles.size() * 3, gl::VBOType::Pos2_F32_UV_U16);
                vbo->copy(vboData);
                auto vao = gl::VAO::create(gl::VBOType::Pos2_F32_UV_U16, vbo->getID());
                vao->bind();
                vao->draw(GL_TRIANGLES, 0, mesh.triangles.size() * 3);
            }
#endif // FEATHER_TK_API_GL_4_1

            p.window->swap();
            //! \todo Is this necessary?
            //p.window->doneCurrent();

            p.refresh = false;
        }
    }

    void Window::setIcons(const std::vector<std::shared_ptr<Image> >& images)
    {
        _p->window->setIcons(images);
    }

    std::shared_ptr<Image> Window::screenshot(const Box2I& rect)
    {
        FEATHER_TK_P();
        std::shared_ptr<Image> out;
        if (p.buffer)
        {
            Box2I rect2 = rect;
            if (!rect.isValid())
            {
                rect2 = Box2I(V2I(), p.buffer->getSize());
            }
            if (rect2.isValid())
            {
                out = Image::create(rect2.w(), rect2.h(), ImageType::RGBA_U8);
                p.window->makeCurrent();
                gl::OffscreenBufferBinding bufferBinding(p.buffer);
                glPixelStorei(GL_PACK_ALIGNMENT, 1);
#if defined(FEATHER_TK_API_GL_4_1)
                glPixelStorei(GL_PACK_SWAP_BYTES, 0);
#endif // FEATHER_TK_API_GL_4_1
                glReadPixels(
                    rect2.x(),
                    rect2.y(),
                    rect2.w(),
                    rect2.h(),
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    out->getData());
            }
        }
        return out;
    }

    void Window::setCloseCallback(const std::function<void(void)>& value)
    {
        _p->closeCallback = value;
    }

    void Window::setGeometry(const Box2I& value)
    {
        IWindow::setGeometry(value);
        for (const auto& child : getChildren())
        {
            child->setGeometry(value);
        }
    }

    void Window::setVisible(bool value)
    {
        IWindow::setVisible(value);
        FEATHER_TK_P();
        if (value)
        {
            p.window->show();
        }
        else
        {
            p.window->hide();
        }
    }

    void Window::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        Size2I sizeHint;
        for (const auto& child : getChildren())
        {
            const Size2I& childSizeHint = child->getSizeHint();
            sizeHint.w = std::max(sizeHint.w, childSizeHint.w);
            sizeHint.h = std::max(sizeHint.h, childSizeHint.h);
        }
        _setSizeHint(sizeHint);
    }

    std::shared_ptr<IRender> Window::_createRender(const std::shared_ptr<Context>& context)
    {
        return gl::Render::create(context);
    }

    void Window::_makeCurrent()
    {
        _p->window->makeCurrent();
    }

    void Window::_doneCurrent()
    {
        _p->window->doneCurrent();
    }
}
