// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/IRender.h>

#include <dtk/core/LRUCache.h>

namespace dtk
{
    namespace gl
    {
        class Texture;

        //! \name Renderer
        ///@{

        //! Texture cache.
        typedef LRUCache<
            std::shared_ptr<Image>,
            std::vector<std::shared_ptr<Texture> > > TextureCache;
        
        //! OpenGL renderer.
        class Render : public IRender
        {
        protected:
            void _init(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<TextureCache>&);

            Render();

        public:
            virtual ~Render();

            //! Create a new renderer.
            static std::shared_ptr<Render> create(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<TextureCache>& = nullptr);

            //! Get the texture cache.
            const std::shared_ptr<TextureCache>& getTextureCache() const;

            void begin(
                const Size2I&,
                const RenderOptions& = RenderOptions()) override;
            void end() override;
            Size2I getRenderSize() const override;
            void setRenderSize(const Size2I&) override;
            RenderOptions getRenderOptions() const override;
            Box2I getViewport() const override;
            void setViewport(const Box2I&) override;
            void clearViewport(const Color4F&) override;
            bool getClipRectEnabled() const override;
            void setClipRectEnabled(bool) override;
            Box2I getClipRect() const override;
            void setClipRect(const Box2I&) override;
            M44F getTransform() const override;
            void setTransform(const M44F&) override;
            void drawRect(
                const Box2F&,
                const Color4F&) override;
            void drawRects(
                const std::vector<Box2F>&,
                const Color4F&) override;
            void drawLine(
                const V2F&,
                const V2F&,
                const Color4F&,
                const LineOptions& = LineOptions()) override;
            void drawLines(
                const std::vector<std::pair<V2F, V2F> >&,
                const Color4F&,
                const LineOptions& = LineOptions()) override;
            void drawMesh(
                const TriMesh2F&,
                const Color4F& = Color4F(1.F, 1.F, 1.F, 1.F),
                const V2F& pos = V2F()) override;
            void drawColorMesh(
                const TriMesh2F&,
                const Color4F& = Color4F(1.F, 1.F, 1.F, 1.F),
                const V2F& pos = V2F()) override;
            void drawText(
                const std::vector<std::shared_ptr<Glyph> >&,
                const FontMetrics&,
                const V2F& position,
                const Color4F& = Color4F(1.F, 1.F, 1.F, 1.F)) override;
            void drawImage(
                const std::shared_ptr<Image>&,
                const TriMesh2F&,
                const Color4F & = Color4F(1.F, 1.F, 1.F, 1.F),
                const ImageOptions & = ImageOptions()) override;
            void drawImage(
                const std::shared_ptr<Image>&,
                const Box2F&,
                const Color4F& = Color4F(1.F, 1.F, 1.F, 1.F),
                const ImageOptions& = ImageOptions()) override;

        private:
            std::vector<std::shared_ptr<Texture> > _getTextures(
                const ImageInfo&,
                const ImageFilters&,
                size_t offset = 0);
            void _copyTextures(
                const std::shared_ptr<Image>&,
                const std::vector<std::shared_ptr<Texture> >&,
                size_t offset = 0);
            void _setActiveTextures(
                const ImageInfo& info,
                const std::vector<std::shared_ptr<Texture> >&,
                size_t offset = 0);

            void _drawTextMesh(const TriMesh2F&);
            
            void _log();

            DTK_PRIVATE();
        };
        
        ///@}
    }
}

