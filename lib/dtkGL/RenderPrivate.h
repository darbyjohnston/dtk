// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkGL/Render.h>

#include <dtkGL/GL.h>
#include <dtkGL/Mesh.h>
#include <dtkGL/Shader.h>
#include <dtkGL/TextureAtlas.h>

#include <dtkCore/Timer.h>

#include <chrono>
#include <list>
#include <map>

namespace dtk
{
    namespace gl
    {
        std::string vertexSource();
        std::string meshFragmentSource();
        std::string colorMeshVertexSource();
        std::string colorMeshFragmentSource();
        std::string textFragmentSource();
        std::string imageFragmentSource();

        struct Render::Private
        {
            core::Size2I size;
            core::RenderOptions options;
            core::Box2I viewport;
            bool clipRectEnabled = false;
            core::Box2I clipRect;
            core::M44F transform;
            
            std::map<std::string, std::shared_ptr<gl::Shader> > shaders;
            std::shared_ptr<TextureCache> textureCache;
            std::shared_ptr<gl::TextureAtlas> glyphTextureAtlas;
            std::map<core::GlyphInfo, core::BoxPackID> glyphIDs;
            std::map<std::string, std::shared_ptr<gl::VBO> > vbos;
            std::map<std::string, std::shared_ptr<gl::VAO> > vaos;

            std::chrono::time_point<std::chrono::steady_clock> startTime;
            struct Stats
            {
                int renderTime = 0;
                size_t triCount = 0;
                size_t textureCount = 0;
                size_t glyphCount = 0;
            };
            Stats stats;
            std::list<Stats> statsList;
            std::shared_ptr<core::Timer> logTimer;
        };
    }
}

