#pragma once

#include "resource.h"

namespace glc {
    class VertexBuffer : public Resource{
    public:
        VertexBuffer();
        ~VertexBuffer();
        void bind(GLenum target);
    };

    class VertexArray : public Resource{
    public:
        VertexArray();
        ~VertexArray();
        void bind();
    };

}


