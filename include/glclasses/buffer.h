#pragma once

#include "resource.h"

namespace glc {
    class Buffer : public Resource{
    public:
        Buffer();
        ~Buffer() override;
        void bind(GLenum target);
    };

    class VertexArray : public Resource{
    public:
        VertexArray();
        ~VertexArray() override;
        void bind();
    };

}


