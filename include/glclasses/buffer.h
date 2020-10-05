#pragma once

#include <glad/glad.h>
#include "noncopyable.h"

namespace wangtiles {
    class VertexBuffer : private NonCopyable{
    public:
        GLuint id{};
        VertexBuffer();
        ~VertexBuffer();
        void bind(GLenum target);
    };

    class VertexArray : private NonCopyable{
    public:
        GLuint id{};
        VertexArray();
        ~VertexArray();
        void bind();
    };

}


