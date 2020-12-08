#pragma once

#include <utility>
#include <glad/glad.h>

namespace glc{
    class Resource {
    protected:
        constexpr Resource() = default;
        virtual ~Resource() = default;

    public:
        GLuint id{};
        Resource(Resource&& other)  noexcept {
            id = other.id;
            other.id = 0;
        }

        Resource& operator=(Resource&& other) noexcept {
            if (this == &other)
                return *this;
            this->~Resource();
            id = other.id;
            other.id = 0;
            return *this;
        }
        Resource(const Resource &) = delete;
        Resource &operator=(const Resource &) = delete;
    };
}
