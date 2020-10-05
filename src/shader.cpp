#include "glclasses/shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace glc;

Shader::Shader(GLenum type) {
    id = glCreateShader(type);
}

Shader::~Shader() {
    glDeleteShader(id);
}

Program::Program() {
    id = glCreateProgram();
}

Program::~Program() {
    glDeleteProgram(id);
}

void Program::bind() {
    glUseProgram(id);
}

GLint Program::getUniformLocation(const std::string& name) {
    return glGetUniformLocation(id, name.c_str());
}
