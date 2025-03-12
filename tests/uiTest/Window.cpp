// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/Window.h>

#include <uiTest/App.h>

#include <dtk/ui/IClipboard.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>
#include <dtk/core/LogSystem.h>

namespace dtk
{
    namespace ui_test
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
                    const std::shared_ptr<Context>& context)
                {
                    auto out = std::shared_ptr<Clipboard>(new Clipboard);
                    out->_init(context);
                    return out;
                }

                std::string getText() const override
                {
                    return _text;
                }

                void setText(const std::string& value) override
                {
                    _text = value;
                }

            private:
                std::string _text;
            };

            class Render : public IRender
            {
            public:
                virtual ~Render()
                {
                    if (auto context = _context.lock())
                    {
                        if (auto logSystem = context->getSystem<LogSystem>())
                        {
                            logSystem->print(
                                "dtk::ui_test::Render",
                                Format(
                                    "\n"
                                    "    Render count: {0}\n"
                                    "    Rectangle count: {1}\n"
                                    "    Mesh count: {2}\n"
                                    "    Texture count: {3}\n"
                                    "    Text count: {4}\n"
                                    "    Image count: {5}").
                                arg(_renderCount).
                                arg(_rectCount).
                                arg(_meshCount).
                                arg(_textureCount).
                                arg(_textCount).
                                arg(_imageCount));
                        }
                    }
                }

                static std::shared_ptr<Render> create(
                    const std::shared_ptr<Context>&);

                void begin(
                    const Size2I&,
                    const RenderOptions& = RenderOptions()) override;
                void end() override {}
                Size2I getRenderSize() const override;
                void setRenderSize(const Size2I&) override;
                RenderOptions getRenderOptions() const override;
                Box2I getViewport() const override;
                void setViewport(const Box2I&) override;
                void clearViewport(const Color4F&) override {}
                bool getClipRectEnabled() const override;
                void setClipRectEnabled(bool) override;
                Box2I getClipRect() const override;
                void setClipRect(const Box2I&) override;
                M44F getTransform() const override;
                void setTransform(const M44F&) override;
                void drawRect(
                    const Box2F&,
                    const Color4F&) override
                {
                    ++_rectCount;
                }
                void drawRects(
                    const std::vector<Box2F>& rects,
                    const Color4F&) override
                {
                    _rectCount += rects.size();
                }
                void drawLine(
                    const V2F&,
                    const V2F&,
                    const Color4F&,
                    const LineOptions& = LineOptions()) override {}
                void drawLines(
                    const std::vector<std::pair<V2F, V2F> >&,
                    const Color4F&,
                    const LineOptions& = LineOptions()) override {}
                void drawMesh(
                    const TriMesh2F&,
                    const Color4F& = Color4F(1.F, 1.F, 1.F, 1.F),
                    const V2F& pos = V2F()) override
                {
                    ++_meshCount;
                }
                void drawColorMesh(
                    const TriMesh2F&,
                    const Color4F& = Color4F(1.F, 1.F, 1.F, 1.F),
                    const V2F& pos = V2F()) override
                {
                    ++_meshCount;
                }
                void drawTexture(
                    unsigned int,
                    const Box2I&,
                    const Color4F& = Color4F(1.F, 1.F, 1.F),
                    AlphaBlend = AlphaBlend::Straight) override
                {
                    ++_textureCount;
                }
                void drawText(
                    const std::vector<std::shared_ptr<Glyph> >&,
                    const FontMetrics&,
                    const V2F& position,
                    const Color4F& = Color4F(1.F, 1.F, 1.F, 1.F)) override
                {
                    ++_textCount;
                }
                void drawImage(
                    const std::shared_ptr<Image>&,
                    const TriMesh2F&,
                    const Color4F& = Color4F(1.F, 1.F, 1.F, 1.F),
                    const ImageOptions& = ImageOptions()) override
                {
                    ++_imageCount;
                }
                void drawImage(
                    const std::shared_ptr<Image>&,
                    const Box2F&,
                    const Color4F& = Color4F(1.F, 1.F, 1.F, 1.F),
                    const ImageOptions& = ImageOptions()) override
                {
                    ++_imageCount;
                }

            private:
                Size2I _renderSize;
                RenderOptions _options;
                Box2I _viewport;
                bool _clipRectEnabled = false;
                Box2I _clipRect;
                M44F _transform;
                size_t _renderCount = 0;
                size_t _rectCount = 0;
                size_t _meshCount = 0;
                size_t _textureCount = 0;
                size_t _textCount = 0;
                size_t _imageCount = 0;
            };

            std::shared_ptr<Render> Render::create(const std::shared_ptr<Context>& context)
            {
                auto out = std::shared_ptr<Render>(new Render);
                out->_init(context);
                return out;
            }

            void Render::begin(
                const Size2I& size,
                const RenderOptions& options)
            {
                _renderSize = size;
                _options = options;
                ++_renderCount;
            }

            Size2I Render::getRenderSize() const 
            {
                return _renderSize;
            }

            void Render::setRenderSize(const Size2I& value)
            {
                _renderSize = value;
            }

            RenderOptions Render::getRenderOptions() const
            {
                return _options;
            }

            Box2I Render::getViewport() const
            {
                return _viewport;
            }

            void Render::setViewport(const Box2I& value)
            {
                _viewport = value;
            }

            bool Render::getClipRectEnabled() const
            {
                return _clipRectEnabled;
            }

            void Render::setClipRectEnabled(bool value)
            {
                _clipRectEnabled = value;
            }

            Box2I Render::getClipRect() const
            {
                return _clipRect;
            }

            void Render::setClipRect(const Box2I& value)
            {
                _clipRect = value;
            }

            M44F Render::getTransform() const
            {
                return _transform;
            }

            void Render::setTransform(const M44F& value)
            {
                _transform = value;
            }
        }

        struct Window::Private
        {
            std::weak_ptr<Context> context;
            std::weak_ptr<App> app;
            Size2I bufferSize = Size2I(0, 0);
            float displayScale = 1.F;
            bool refresh = true;
            int modifiers = 0;
            std::shared_ptr<Render> render;
        };

        void Window::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::string& name,
            const Size2I& size)
        {
            IWindow::_init(context, name, nullptr);
            DTK_P();

            p.context = context;
            p.app = app;
            p.bufferSize = size;
            p.render = Render::create(context);

            setClipboard(Clipboard::create(context));
            DTK_ASSERT(getClipboard());

            _setSizeUpdate();
            _setDrawUpdate();
        }

        Window::Window() :
            _p(new Private)
        {}

        Window::~Window()
        {}

        std::shared_ptr<Window> Window::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::string& name,
            const Size2I& size)
        {
            auto out = std::shared_ptr<Window>(new Window);
            out->_init(context, app, name, size);
            return out;
        }

        void Window::setDisplayScale(float value)
        {
            DTK_P();
            if (value == p.displayScale)
                return;
            p.displayScale = value;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void Window::setCursorEnter(bool value)
        {
            DTK_P();
            _cursorEnter(value);
            if (auto app = p.app.lock()) { app->tick(); }
        }

        void Window::setCursorPos(const V2I& pos)
        {
            DTK_P();
            _cursorPos(pos);
            if (auto app = p.app.lock()) { app->tick(); }
        }

        void Window::setButton(int button, int modifiers)
        {
            DTK_P();
            p.modifiers = modifiers;
            _mouseButton(button, true, modifiers);
            if (auto app = p.app.lock()) { app->tick(); }
            _mouseButton(button, false, modifiers);
            if (auto app = p.app.lock()) { app->tick(); }
        }

        void Window::setButton(int button, bool press, int modifiers)
        {
            DTK_P();
            p.modifiers = modifiers;
            _mouseButton(button, press, modifiers);
            if (auto app = p.app.lock()) { app->tick(); }
        }

        void Window::setScroll(const V2F& value)
        {
            DTK_P();
            _scroll(value, p.modifiers);
            if (auto app = p.app.lock()) { app->tick(); }
        }

        void Window::setKey(Key key, int modifiers)
        {
            DTK_P();
            p.modifiers = modifiers;
            _key(key, true, modifiers);
            if (auto app = p.app.lock()) { app->tick(); }
            _key(key, false, modifiers);
            if (auto app = p.app.lock()) { app->tick(); }
        }

        void Window::setKey(Key key, bool press, int modifiers)
        {
            DTK_P();
            p.modifiers = modifiers;
            _key(key, press, modifiers);
            if (auto app = p.app.lock()) { app->tick(); }
        }

        void Window::setText(const std::string& value)
        {
            DTK_P();
            _text(value);
            if (auto app = p.app.lock()) { app->tick(); }
        }

        void Window::setDrop(const std::vector<std::string>& value)
        {
            DTK_P();
            _drop(value);
            if (auto app = p.app.lock()) { app->tick(); }
        }

        void Window::update(
            const std::shared_ptr<FontSystem>& fontSystem,
            const std::shared_ptr<IconSystem>& iconSystem,
            const std::shared_ptr<Style>& style)
        {
            DTK_P();

            if (_hasSizeUpdate(shared_from_this()))
            {
                SizeHintEvent sizeHintEvent(
                    fontSystem,
                    iconSystem,
                    p.displayScale,
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
                p.render->begin(p.bufferSize);
                p.render->setClipRectEnabled(true);
                DrawEvent drawEvent(
                    fontSystem,
                    iconSystem,
                    p.displayScale,
                    style,
                    p.render);
                _drawEventRecursive(
                    shared_from_this(),
                    Box2I(V2I(), p.bufferSize),
                    drawEvent);
                p.render->setClipRectEnabled(false);
                p.render->end();

                p.refresh = false;
            }
        }

        void Window::setGeometry(const Box2I& value)
        {
            IWindow::setGeometry(value);
            for (const auto& child : getChildren())
            {
                child->setGeometry(value);
            }
        }

        void Window::sizeHintEvent(const SizeHintEvent& event)
        {
            IWindow::sizeHintEvent(event);
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

