#include <glclasses/glerror.h>
#include <initializer_list>
#include <algorithm>
#include "glclasses/texture.h"


using namespace glc;

int getLevels(std::initializer_list<int> dims){
    return 1 + floor(log2(std::max(dims)));
}

Texture::Texture(GLenum t) {
    target = t;
    glCreateTextures(target, 1, &id);
    CHECK_GL_ERROR
}

Texture::~Texture() {
    if(id != 0)
        glDeleteTextures(1, &id);
}

void Texture::bind(GLenum slot) {
    glActiveTexture(slot);
    glBindTexture(target, id);
    CHECK_GL_ERROR
}

Texture glc::createTexture2D(GLsizei width, GLsizei height, GLenum format) {
    return createTexture2D(width, height, format, getLevels({width, height}));
}

Texture glc::createTexture2D(GLsizei width, GLsizei height, GLenum format, GLsizei levels) {
    Texture texture(GL_TEXTURE_2D);
    glTextureStorage2D(texture.id, levels, format, width, height);
    CHECK_GL_ERROR
    return texture;
}

Texture glc::createTexture2DArray(GLsizei width, GLsizei height, GLsizei depth, GLenum format) {
    return createTexture2DArray(width, height, depth, format,getLevels({width, height}));
}

Texture glc::createTexture2DArray(GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei levels) {
    Texture texture(GL_TEXTURE_2D_ARRAY);
    glTextureStorage3D(texture.id, 1, format, width, height, depth);
    CHECK_GL_ERROR
    return texture;
}

Texture glc::createTexture1D(GLsizei width, GLenum format) {
    return createTexture1D(width, format, getLevels({width}));
}

Texture glc::createTexture1D(GLsizei width, GLenum format, GLsizei levels) {
    Texture texture(GL_TEXTURE_1D);
    glTextureStorage1D(texture.id, levels, format, width);
    CHECK_GL_ERROR
    return texture;
}




