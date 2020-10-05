#pragma once

#include "resource.h"
#include <string>

namespace glc {
    class Texture : public Resource{
    public:
        GLenum target{};
        explicit Texture(GLenum target);
        explicit Texture(GLsizei width, GLsizei height, GLenum format);
        explicit Texture(GLsizei width, GLsizei height, GLenum format, GLsizei levels);
        ~Texture();
        void bind(GLenum slot);
    };
}


