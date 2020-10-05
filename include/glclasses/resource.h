#pragma once

#include <glad/glad.h>

namespace glc{
    class Resource {
    protected:
        constexpr Resource() = default;
        ~Resource() = default;

    public:
        GLuint id{};

        Resource(const Resource &) = delete;
        Resource &operator=(const Resource &) = delete;
    };
}
