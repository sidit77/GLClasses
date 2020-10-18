#include <glclasses/glerror.h>
#include "glclasses/texture.h"

using namespace glc;

int getLevels(int w, int h){
    return 1 + floor(log2(w > h ? w : h));
}

Texture::Texture(GLenum t) {
    target = t;
    glCreateTextures(target, 1, &id);
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::bind(GLenum slot) {
    glActiveTexture(slot);
    glBindTexture(target, id);
}


Texture2D::Texture2D(GLsizei width, GLsizei height, GLenum format, GLsizei levels) : Texture(GL_TEXTURE_2D) {
    glTextureStorage2D(id, levels, format, width, height);
}
Texture2D::Texture2D(GLsizei width, GLsizei height, GLenum format) : Texture2D(width, height, format, getLevels(width, height)){}


Texture2DArray::Texture2DArray(GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei levels) : Texture(GL_TEXTURE_2D_ARRAY) {
    glTextureStorage3D(id, levels, format, width, height, depth);
}

Texture2DArray::Texture2DArray(GLsizei width, GLsizei height, GLsizei depth, GLenum format) : Texture2DArray(width, height, depth, format, getLevels(width, height)) {}