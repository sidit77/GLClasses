#pragma once

#include <glad/glad.h>
#include <string>
#include "noncopyable.h"

namespace wangtiles{
    class Texture : private NonCopyable{
    public:
        GLuint id{};
        GLenum target{};
        explicit Texture(GLenum target);
        explicit Texture(GLsizei width, GLsizei height, GLenum format);
        explicit Texture(GLsizei width, GLsizei height, GLenum format, GLsizei levels);
        ~Texture();
        void bind(GLenum slot);
    };
}


