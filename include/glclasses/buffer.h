#pragma once

#include "resource.h"

namespace glc {
    class Buffer : public Resource{
    public:
        Buffer();
        ~Buffer() override;
        Buffer(Buffer &&other) noexcept : Resource(std::move(other)){};
        Buffer& operator=(Buffer &&other) noexcept {
            if (this == &other)
                return *this;
            Resource::operator=(std::move(other));
            return *this;
        }
        void bind(GLenum target);
        void bindBase(GLenum target, GLuint slot);

        template<typename T>
        T* map(GLenum access){
            return (T*)glMapNamedBuffer(id, access);
        }

        void unmap();
    };

    Buffer createBuffer(GLsizeiptr size, GLbitfield flags, const void * data = nullptr);

    class VertexArray : public Resource{
    public:
        VertexArray();
        ~VertexArray() override;
        VertexArray(VertexArray &&other) noexcept : Resource(std::move(other)){};
        VertexArray& operator=(VertexArray &&other) noexcept {
            if (this == &other)
                return *this;
            Resource::operator=(std::move(other));
            return *this;
        }
        void bind();
    };

}


