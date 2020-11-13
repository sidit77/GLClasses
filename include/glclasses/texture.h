#pragma once

#include "resource.h"
#include <string>

namespace glc {
    class Texture : public Resource{
    public:
        GLenum target{};
        explicit Texture(GLenum target);
        ~Texture() override;
        Texture(Texture&& other)  noexcept : Resource(std::move(other)) {
            target = other.target;
        }

        Texture& operator=(Texture&& other) noexcept {
            if (this == &other)
                return *this;
            target = other.target;
            Resource::operator=(std::move(other));
            return *this;
        }
        void bind(GLenum slot);
    };

    Texture createTexture2D(GLsizei width, GLsizei height, GLenum format);
    Texture createTexture2D(GLsizei width, GLsizei height, GLenum format, GLsizei levels);

    Texture createTexture2DArray(GLsizei width, GLsizei height, GLsizei depth, GLenum format);
    Texture createTexture2DArray(GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei levels);

    Texture createTexture1D(GLsizei width, GLenum format);
    Texture createTexture1D(GLsizei width, GLenum format, GLsizei levels);

}


