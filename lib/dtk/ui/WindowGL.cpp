// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/Window.h>

#include <dtk/gl/GL.h>
#include <dtk/gl/OffscreenBuffer.h>
#include <dtk/gl/Render.h>
#include <dtk/gl/Window.h>
#if defined(dtk_API_GLES_2)
#include <dtk/gl/Mesh.h>
#include <dtk/gl/Shader.h>
#endif // dtk_API_GLES_2

#include <dtk/ui/IClipboard.h>
#include <dtk/ui/IconLibrary.h>
#include <dtk/ui/Style.h>

#include <dtk/core/Context.h>
#include <dtk/core/Format.h>
#include <dtk/core/LogSystem.h>
#include <dtk/core/FontSystem.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <codecvt>
#include <locale>

namespace dtk
{
    namespace ui
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
                    out |= static_cast<int>(ui::KeyModifier::Shift);
                }
                if (value & GLFW_MOD_CONTROL)
                {
                    out |= static_cast<int>(ui::KeyModifier::Control);
                }
                if (value & GLFW_MOD_ALT)
                {
                    out |= static_cast<int>(ui::KeyModifier::Alt);
                }
                if (value & GLFW_MOD_SUPER)
                {
                    out |= static_cast<int>(ui::KeyModifier::Super);
                }
                return out;
            }

            ui::Key fromGLFWKey(int key)
            {
                ui::Key out = ui::Key::Unknown;
                switch (key)
                {
                case GLFW_KEY_SPACE: out = ui::Key::Space; break;
                case GLFW_KEY_APOSTROPHE: out = ui::Key::Apostrophe; break;
                case GLFW_KEY_COMMA: out = ui::Key::Comma; break;
                case GLFW_KEY_MINUS: out = ui::Key::Minus; break;
                case GLFW_KEY_PERIOD: out = ui::Key::Period; break;
                case GLFW_KEY_SLASH: out = ui::Key::Slash; break;
                case GLFW_KEY_0: out = ui::Key::_0; break;
                case GLFW_KEY_1: out = ui::Key::_1; break;
                case GLFW_KEY_2: out = ui::Key::_2; break;
                case GLFW_KEY_3: out = ui::Key::_3; break;
                case GLFW_KEY_4: out = ui::Key::_4; break;
                case GLFW_KEY_5: out = ui::Key::_5; break;
                case GLFW_KEY_6: out = ui::Key::_6; break;
                case GLFW_KEY_7: out = ui::Key::_7; break;
                case GLFW_KEY_8: out = ui::Key::_8; break;
                case GLFW_KEY_9: out = ui::Key::_9; break;
                case GLFW_KEY_SEMICOLON: out = ui::Key::Semicolon; break;
                case GLFW_KEY_EQUAL: out = ui::Key::Equal; break;
                case GLFW_KEY_A: out = ui::Key::A; break;
                case GLFW_KEY_B: out = ui::Key::B; break;
                case GLFW_KEY_C: out = ui::Key::C; break;
                case GLFW_KEY_D: out = ui::Key::D; break;
                case GLFW_KEY_E: out = ui::Key::E; break;
                case GLFW_KEY_F: out = ui::Key::F; break;
                case GLFW_KEY_G: out = ui::Key::G; break;
                case GLFW_KEY_H: out = ui::Key::H; break;
                case GLFW_KEY_I: out = ui::Key::I; break;
                case GLFW_KEY_J: out = ui::Key::J; break;
                case GLFW_KEY_K: out = ui::Key::K; break;
                case GLFW_KEY_L: out = ui::Key::L; break;
                case GLFW_KEY_M: out = ui::Key::M; break;
                case GLFW_KEY_N: out = ui::Key::N; break;
                case GLFW_KEY_O: out = ui::Key::O; break;
                case GLFW_KEY_P: out = ui::Key::P; break;
                case GLFW_KEY_Q: out = ui::Key::Q; break;
                case GLFW_KEY_R: out = ui::Key::R; break;
                case GLFW_KEY_S: out = ui::Key::S; break;
                case GLFW_KEY_T: out = ui::Key::T; break;
                case GLFW_KEY_U: out = ui::Key::U; break;
                case GLFW_KEY_V: out = ui::Key::V; break;
                case GLFW_KEY_W: out = ui::Key::W; break;
                case GLFW_KEY_X: out = ui::Key::X; break;
                case GLFW_KEY_Y: out = ui::Key::Y; break;
                case GLFW_KEY_Z: out = ui::Key::Z; break;
                case GLFW_KEY_LEFT_BRACKET: out = ui::Key::LeftBracket; break;
                case GLFW_KEY_BACKSLASH: out = ui::Key::Backslash; break;
                case GLFW_KEY_RIGHT_BRACKET: out = ui::Key::RightBracket; break;
                case GLFW_KEY_GRAVE_ACCENT: out = ui::Key::GraveAccent; break;
                case GLFW_KEY_ESCAPE: out = ui::Key::Escape; break;
                case GLFW_KEY_ENTER: out = ui::Key::Enter; break;
                case GLFW_KEY_TAB: out = ui::Key::Tab; break;
                case GLFW_KEY_BACKSPACE: out = ui::Key::Backspace; break;
                case GLFW_KEY_INSERT: out = ui::Key::Insert; break;
                case GLFW_KEY_DELETE: out = ui::Key::Delete; break;
                case GLFW_KEY_RIGHT: out = ui::Key::Right; break;
                case GLFW_KEY_LEFT: out = ui::Key::Left; break;
                case GLFW_KEY_DOWN: out = ui::Key::Down; break;
                case GLFW_KEY_UP: out = ui::Key::Up; break;
                case GLFW_KEY_PAGE_UP: out = ui::Key::PageUp; break;
                case GLFW_KEY_PAGE_DOWN: out = ui::Key::PageDown; break;
                case GLFW_KEY_HOME: out = ui::Key::Home; break;
                case GLFW_KEY_END: out = ui::Key::End; break;
                case GLFW_KEY_CAPS_LOCK: out = ui::Key::CapsLock; break;
                case GLFW_KEY_SCROLL_LOCK: out = ui::Key::ScrollLock; break;
                case GLFW_KEY_NUM_LOCK: out = ui::Key::NumLock; break;
                case GLFW_KEY_PRINT_SCREEN: out = ui::Key::PrintScreen; break;
                case GLFW_KEY_PAUSE: out = ui::Key::Pause; break;
                case GLFW_KEY_F1: out = ui::Key::F1; break;
                case GLFW_KEY_F2: out = ui::Key::F2; break;
                case GLFW_KEY_F3: out = ui::Key::F3; break;
                case GLFW_KEY_F4: out = ui::Key::F4; break;
                case GLFW_KEY_F5: out = ui::Key::F5; break;
                case GLFW_KEY_F6: out = ui::Key::F6; break;
                case GLFW_KEY_F7: out = ui::Key::F7; break;
                case GLFW_KEY_F8: out = ui::Key::F8; break;
                case GLFW_KEY_F9: out = ui::Key::F9; break;
                case GLFW_KEY_F10: out = ui::Key::F10; break;
                case GLFW_KEY_F11: out = ui::Key::F11; break;
                case GLFW_KEY_F12: out = ui::Key::F12; break;
                case GLFW_KEY_LEFT_SHIFT: out = ui::Key::LeftShift; break;
                case GLFW_KEY_LEFT_CONTROL: out = ui::Key::LeftControl; break;
                case GLFW_KEY_LEFT_ALT: out = ui::Key::LeftAlt; break;
                case GLFW_KEY_LEFT_SUPER: out = ui::Key::LeftSuper; break;
                case GLFW_KEY_RIGHT_SHIFT: out = ui::Key::RightShift; break;
                case GLFW_KEY_RIGHT_CONTROL: out = ui::Key::RightControl; break;
                case GLFW_KEY_RIGHT_ALT: out = ui::Key::RightAlt; break;
                case GLFW_KEY_RIGHT_SUPER: out = ui::Key::RightSuper; break;
                }
                return out;
            }

#if defined(_WINDOWS)
            //! \bug https://social.msdn.microsoft.com/Forums/vstudio/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error?forum=vcgeneral
            typedef unsigned int dtk_char_t;
#else // _WINDOWS
            typedef char32_t dtk_char_t;
#endif // _WINDOWS
        }

        struct Window::Private
        {
            std::weak_ptr<Context> context;
            std::shared_ptr<gl::Window> window;
            Size2I bufferSize = Size2I(0, 0);
            V2F contentScale = V2F(1.F, 1.F);
            bool refresh = true;
            int modifiers = 0;
            std::shared_ptr<gl::OffscreenBuffer> buffer;
            std::shared_ptr<gl::Render> render;
#if defined(dtk_API_GLES_2)
            std::shared_ptr<gl::Shader> shader;
#endif // dtk_API_GLES_2
        };
        
        void Window::_init(
            const std::shared_ptr<Context>& context,
            const std::string& name,
            const Size2I& size)
        {
            IWindow::_init(context, name, nullptr);
            DTK_P();
            
            p.context = context;

            p.window = gl::Window::create(context, name, size);
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
                    DTK_P();
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
                    std::wstring_convert<std::codecvt_utf8<dtk_char_t>, dtk_char_t> utf32Convert;
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

            p.bufferSize = p.window->getFrameBufferSize();
            p.contentScale = p.window->getContentScale();
            p.render = gl::Render::create(context);

            setClipboard(Clipboard::create(context, p.window->getGLFW()));

            _setSizeUpdate();
            _setDrawUpdate();
        }
        
        Window::Window() :
            _p(new Private)
        {}

        Window::~Window()
        {
            DTK_P();
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

        const Size2I& Window::getFrameBufferSize() const
        {
            return _p->bufferSize;
        }

        float Window::getDisplayScale() const
        {
            return _p->contentScale.x;
        }

        bool Window::shouldClose() const
        {
            return _p->window->shouldClose();
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
            DTK_P();
            if (value)
            {
                p.window->show();
            }
            else
            {
                p.window->hide();
            }
        }

        void Window::update(
            const std::shared_ptr<FontSystem>& fontSystem,
            const std::shared_ptr<Style>& style,
            const std::shared_ptr<IconLibrary>& iconLibrary)
        {
            DTK_P();

            if (_hasSizeUpdate(shared_from_this()))
            {
                SizeHintEvent sizeHintEvent(
                    fontSystem,
                    p.contentScale.x,
                    style,
                    iconLibrary);
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
                bufferOptions.color = gl::offscreenColorDefault;
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
                        p.contentScale.x,
                        style,
                        iconLibrary,
                        p.render);
                    _drawEventRecursive(
                        shared_from_this(),
                        Box2I(V2I(), p.bufferSize),
                        drawEvent);
                    p.render->setClipRectEnabled(false);
                    p.render->end();
                }

#if defined(dtk_API_GL_4_1)
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
#elif defined(dtk_API_GLES_2)
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
                                "dtk::ui::Window",
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

                    auto mesh = mesh(Box2I(
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
#endif // dtk_API_GL_4_1

                p.window->swap();
                p.window->doneCurrent();

                p.refresh = false;
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
    }
}

