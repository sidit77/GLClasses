#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
#include "glclasses/loader/textureloading.h"

GLint getFormat(int channels){
    switch(channels){
        case 1:return GL_RED;
        case 2:return GL_RG;
        case 3:return GL_RGB;
        default: return GL_RGBA;
    }
}

GLint getSizedFormat(int channels){
    switch(channels){
        case 1:return GL_R8;
        case 2:return GL_RG8;
        case 3:return GL_RGB8;
        default: return GL_RGBA8;
    }
}

glc::Texture* createTextureFromStb(stbi_uc* data, int width, int height, int nrChannels){
    auto texture = std::make_unique<glc::Texture>(width, height, getSizedFormat(nrChannels));
    glTextureSubImage2D(texture->id, 0, 0, 0, width, height, getFormat(nrChannels), GL_UNSIGNED_BYTE, data);
    glGenerateTextureMipmap(texture->id);
    stbi_image_free(data);
    return texture.release();
}


glc::Texture* glc::loader::loadTextureFromFile(const std::string &path) {
    int width, height, nrChannels;
    stbi_uc *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if(data) {
        return createTextureFromStb(data, width, height, nrChannels);
    }else{
        std::cerr << "Could not load image: " << path << std::endl;
    }
    return nullptr;
}

glc::Texture* glc::loader::loadTextureFromFile(const uint8_t* memory, int length) {
    int width, height, nrChannels;
    stbi_uc *data = stbi_load_from_memory(memory, length, &width, &height, &nrChannels, 0);
    if(data) {
        return createTextureFromStb(data, width, height, nrChannels);
    }else{
        std::cerr << "Could not load image from memory" << std::endl;
    }
    return nullptr;
}

