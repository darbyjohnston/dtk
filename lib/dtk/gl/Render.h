// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
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
        typedef core::LRUCache<
            std::shared_ptr<core::Image>,
            std::vector<std::shared_ptr<Texture> > > TextureCache;
        
        //! OpenGL renderer.
        class Render : public core::IRender
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<TextureCache>&);

            Render();

        public:
            virtual ~Render();

            //! Create a new renderer.
            static std::shared_ptr<Render> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<TextureCache>& = nullptr);

            //! Get the texture cache.
            const std::shared_ptr<TextureCache>& getTextureCache() const;

            void begin(
                const core::Size2I&,
                const core::RenderOptions& = core::RenderOptions()) override;
            void end() override;
            core::Size2I getRenderSize() const override;
            void setRenderSize(const core::Size2I&) override;
            core::Box2I getViewport() const override;
            void setViewport(const core::Box2I&) override;
            void clearViewport(const core::Color4F&) override;
            bool getClipRectEnabled() const override;
            void setClipRectEnabled(bool) override;
            core::Box2I getClipRect() const override;
            void setClipRect(const core::Box2I&) override;
            core::M44F getTransform() const override;
            void setTransform(const core::M44F&) override;
            void drawRect(
                const core::Box2F&,
                const core::Color4F&) override;
            void drawRects(
                const std::vector<core::Box2F>&,
                const core::Color4F&) override;
            void drawLine(
                const core::V2F&,
                const core::V2F&,
                const core::Color4F&,
                const core::LineOptions& = core::LineOptions()) override;
            void drawLines(
                const std::vector<std::pair<core::V2F, core::V2F> >&,
                const core::Color4F&,
                const core::LineOptions& = core::LineOptions()) override;
            void drawMesh(
                const core::TriMesh2F&,
                const core::Color4F& = core::Color4F(1.F, 1.F, 1.F, 1.F),
                const core::V2F& pos = core::V2F()) override;
            void drawColorMesh(
                const core::TriMesh2F&,
                const core::Color4F& = core::Color4F(1.F, 1.F, 1.F, 1.F),
                const core::V2F& pos = core::V2F()) override;
            void drawText(
                const std::vector<std::shared_ptr<core::Glyph> >&,
                const core::FontMetrics&,
                const core::V2F& position,
                const core::Color4F& = core::Color4F(1.F, 1.F, 1.F, 1.F)) override;
            void drawImage(
                const std::shared_ptr<core::Image>&,
                const core::Box2F&,
                const core::Color4F& = core::Color4F(1.F, 1.F, 1.F, 1.F),
                const core::ImageOptions& = core::ImageOptions()) override;

        private:
            std::vector<std::shared_ptr<Texture> > _getTextures(
                const core::ImageInfo&,
                const core::ImageFilters&,
                size_t offset = 0);
            void _copyTextures(
                const std::shared_ptr<core::Image>&,
                const std::vector<std::shared_ptr<Texture> >&,
                size_t offset = 0);
            void _setActiveTextures(
                const core::ImageInfo& info,
                const std::vector<std::shared_ptr<Texture> >&,
                size_t offset = 0);

            void _drawTextMesh(const core::TriMesh2F&);
            
            void _log();

            DTK_PRIVATE();
        };
        
        ///@}
    }
}

