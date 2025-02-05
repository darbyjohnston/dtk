// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/gl/Util.h>

#include <dtk/gl/GL.h>

namespace dtk
{
    namespace gl
    {
        unsigned int getReadPixelsFormat(dtk::ImageType value)
        {
            const std::array<GLenum, static_cast<std::size_t>(dtk::ImageType::Count)> data =
            {
                GL_NONE,

#if defined(dtk_API_GL_4_1)
                GL_RED,
                GL_RED,
                GL_RED,
                GL_RED,
                GL_RED,

                GL_NONE,
                GL_NONE,
                GL_NONE,
                GL_NONE,
                GL_NONE,

                GL_RGB,
                GL_RGBA,
                GL_RGB,
                GL_RGB,
                GL_RGB,
                GL_RGB,

                GL_RGBA,
                GL_RGBA,
                GL_RGBA,
                GL_RGBA,
                GL_RGBA,
#elif defined(dtk_API_GLES_2)
                GL_NONE,
                GL_NONE,
                GL_NONE,
                GL_NONE,
                GL_NONE,

                GL_NONE,
                GL_NONE,
                GL_NONE,
                GL_NONE,
                GL_NONE,

                GL_RGB,
                GL_NONE,
                GL_NONE,
                GL_NONE,
                GL_NONE,
                GL_NONE,

                GL_RGBA,
                GL_NONE,
                GL_NONE,
                GL_NONE,
                GL_NONE,
#endif // dtk_API_GL_4_1

                GL_NONE
            };
            return data[static_cast<std::size_t>(value)];
        }

        unsigned int getReadPixelsType(dtk::ImageType value)
        {
            const std::array<GLenum, static_cast<std::size_t>(dtk::ImageType::Count)> data =
            {
                GL_NONE,

                GL_UNSIGNED_BYTE,
#if defined(dtk_API_GL_4_1)
                GL_UNSIGNED_SHORT,
                GL_UNSIGNED_INT,
                GL_HALF_FLOAT,
                GL_FLOAT,
#elif defined(dtk_API_GLES_2)
                GL_NONE,
                GL_NONE,
                GL_NONE,
                GL_NONE,
#endif // dtk_API_GL_4_1

                GL_NONE,
                GL_NONE,
                GL_NONE,
                GL_NONE,
                GL_NONE,

                GL_UNSIGNED_BYTE,
#if defined(dtk_API_GL_4_1)
                GL_UNSIGNED_INT_10_10_10_2,
                GL_UNSIGNED_SHORT,
                GL_UNSIGNED_INT,
                GL_HALF_FLOAT,
                GL_FLOAT,
#elif defined(dtk_API_GLES_2)
                GL_NONE,
                GL_NONE,
                GL_NONE,
                GL_NONE,
                GL_NONE,
#endif // dtk_API_GL_4_1

                GL_UNSIGNED_BYTE,
#if defined(dtk_API_GL_4_1)
                GL_UNSIGNED_SHORT,
                GL_UNSIGNED_INT,
                GL_HALF_FLOAT,
                GL_FLOAT,
#elif defined(dtk_API_GLES_2)
                GL_NONE,
                GL_NONE,
                GL_NONE,
                GL_NONE,
#endif // dtk_API_GL_4_1

                GL_NONE
            };
            return data[static_cast<std::size_t>(value)];
        }

        struct SetAndRestore::Private
        {
            unsigned int id = 0;
            GLboolean previous = GL_FALSE;
        };

        SetAndRestore::SetAndRestore(unsigned int id, bool value) :
            _p(new Private)
        {
            _p->id = id;

            glGetBooleanv(id, &_p->previous);

            if (value)
            {
                glEnable(id);
            }
            else
            {
                glDisable(id);
            }
        }

        SetAndRestore::~SetAndRestore()
        {
            if (_p->previous)
            {
                glEnable(_p->id);
            }
            else
            {
                glDisable(_p->id);
            }
        }

        std::string getErrorLabel(unsigned int value)
        {
            std::string out;
            switch(value)
            {
            case GL_NO_ERROR: out = "GL_NO_ERROR"; break;
            case GL_INVALID_ENUM: out = "GL_INVALID_ENUM"; break;
            case GL_INVALID_VALUE: out = "GL_INVALID_VALUE"; break;
            case GL_INVALID_OPERATION: out = "GL_INVALID_OPERATION"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: out = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
            case GL_OUT_OF_MEMORY: out = "GL_OUT_OF_MEMORY"; break;
            default: break;
            }
            return out;
        }
    }
}

