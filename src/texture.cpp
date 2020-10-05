#include "glclasses/texture.h"

using namespace glc;

Texture::Texture(GLenum t) {
    target = t;
    glCreateTextures(target, 1, &id);
}

Texture::Texture(GLsizei width, GLsizei height, GLenum format, GLsizei levels) : Texture(GL_TEXTURE_2D){
    glTextureStorage2D(id, levels, format, width, height);
}

Texture::Texture(GLsizei width, GLsizei height, GLenum format) :
Texture(width, height, format, 1 + floor(log2(width > height ? width : height))) {}


Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::bind(GLenum slot) {
    glActiveTexture(slot);
    glBindTexture(target, id);
}




