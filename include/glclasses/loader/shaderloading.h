#pragma once

#include <glclasses/shader.h>

namespace glc::loader {

    Program* loadProgramFromFile(const std::string& path);
    Program* createProgram(std::initializer_list<Shader*> list);

    Shader* loadShaderFromFile(const std::string& path, GLenum type);
    Shader* loadShaderFromString(const std::string &source, GLenum type);

}
