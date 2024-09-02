// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/gl/Util.h>

#include <dtk/gl/GL.h>

namespace dtk
{
    namespace gl
    {
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

