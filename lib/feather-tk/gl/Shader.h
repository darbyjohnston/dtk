// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/Color.h>
#include <feather-tk/core/Matrix.h>
#include <feather-tk/core/Util.h>
#include <feather-tk/core/Vector.h>

#include <memory>
#include <string>
#include <vector>

namespace feather_tk
{
    namespace gl
    {
        //! \name Shaders
        ///@{
        
        //! Shader.
        class Shader : public std::enable_shared_from_this<Shader>
        {
            FEATHER_TK_NON_COPYABLE(Shader);

        protected:
            void _init();

            Shader();

        public:
            ~Shader();

            //! Create a new shader.
            static std::shared_ptr<Shader> create(
                const std::string& vertexSource,
                const std::string& fragmentSource);

            //! Get the vertex shader source.
            const std::string& getVertexSource() const;

            //! Get the fragment shader source.
            const std::string& getFragmentSource() const;

            //! Get the OpenGL shader program.
            unsigned int getProgram() const;

            //! Bind the shader.
            void bind();

            //! \name Uniforms
            //! Set uniform values.
            ///@{

            void setUniform(int, int);
            void setUniform(int, float);
            void setUniform(int, const V2F&);
            void setUniform(int, const V3F&);
            void setUniform(int, const V4F&);
            void setUniform(int, const M33F&);
            void setUniform(int, const M44F&);
            void setUniform(int, const Color4F&);
            void setUniform(int, const float[4]);

            void setUniform(int, const std::vector<int>&);
            void setUniform(int, const std::vector<float>&);
            void setUniform(int, const std::vector<V3F>&);
            void setUniform(int, const std::vector<V4F>&);

            void setUniform(const std::string&, int);
            void setUniform(const std::string&, float);
            void setUniform(const std::string&, const V2F&);
            void setUniform(const std::string&, const V3F&);
            void setUniform(const std::string&, const V4F&);
            void setUniform(const std::string&, const M33F&);
            void setUniform(const std::string&, const M44F&);
            void setUniform(const std::string&, const Color4F&);
            void setUniform(const std::string&, const float[4]);

            void setUniform(const std::string&, const std::vector<int>&);
            void setUniform(const std::string&, const std::vector<float>&);
            void setUniform(const std::string&, const std::vector<V3F>&);
            void setUniform(const std::string&, const std::vector<V4F>&);

            ///@}

        private:
            FEATHER_TK_PRIVATE();
        };
        
        ///@}
    }
}
