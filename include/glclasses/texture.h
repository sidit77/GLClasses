#pragma once

#include "resource.h"
#include <string>

namespace glc {
    class Texture : public Resource{
    public:
        GLenum target{};
        explicit Texture(GLenum target);
        ~Texture();
        void bind(GLenum slot);
    };

    class Texture2D : public Texture {
    public:
        explicit Texture2D(GLsizei width, GLsizei height, GLenum format);
        explicit Texture2D(GLsizei width, GLsizei height, GLenum format, GLsizei levels);
    };

    class Texture2DArray : public Texture {
    public:
        explicit Texture2DArray(GLsizei width, GLsizei height, GLsizei depth, GLenum format);
        explicit Texture2DArray(GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei levels);
    };
}


