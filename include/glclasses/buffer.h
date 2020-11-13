#pragma once

#include "resource.h"

namespace glc {
    class VertexBuffer : public Resource{
    public:
        VertexBuffer();
        ~VertexBuffer() override;
        void bind(GLenum target);
    };

    class VertexArray : public Resource{
    public:
        VertexArray();
        ~VertexArray() override;
        void bind();
    };

}


