#pragma once

#include <glclasses/texture.h>

namespace glc::loader {

    Texture* loadTextureFromFile(const std::string& path);
    Texture* loadTextureFromFile(const uint8_t* memory, int length);

}


