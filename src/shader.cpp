#include "glclasses/shader.h"
#include <iostream>

using namespace glc;

Shader::Shader(const std::string& source, ShaderType type) {
    id = glCreateShader(type);

    const char *c_str = source.c_str();
    glShaderSource(id, 1, &c_str, NULL);
    glCompileShader(id);
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cerr << "Compilation for shader has failed: \n" << infoLog << std::endl;
    }
}

Shader::~Shader() {
    if(id != 0)
        glDeleteShader(id);
}

Program::Program() {
    id = glCreateProgram();
}

Program::~Program() {
    if(id != 0)
        glDeleteProgram(id);
}

void Program::bind() {
    glUseProgram(id);
}

GLint Program::getUniformLocation(const std::string& name) {
    return glGetUniformLocation(id, name.c_str());
}

ProgramBuilder::ProgramBuilder(std::initializer_list<Shader*> shaders) {
    for(auto& shader : shaders){
        attachShader(shader);
    }
    link();
}

ProgramBuilder& ProgramBuilder::attachShader(Shader* shader) {
    glAttachShader(id, shader->id);
    return *this;
}

ProgramBuilder& ProgramBuilder::link() {
    glLinkProgram(id);
    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cerr << "Linking program has failed: \n" << infoLog << std::endl;
    }
    return *this;
}
