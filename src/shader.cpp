#include "glclasses/shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace wangtiles;

Shader::Shader(const std::string& path, GLenum type) : id(glCreateShader(type)) {
    std::ifstream file;
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try{
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();

        std::string sourcestr = stream.str();
        const char* source = sourcestr.c_str();

        glShaderSource(id, 1, &source, NULL);
        glCompileShader(id);
        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if(!success){
            char infoLog[512];
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            std::cerr << "Compilation for shader \"" << path << "\" has failed: \n" << infoLog << std::endl;
        }
    }
    catch(std::ifstream::failure e)
    {
        std::cerr << "Loading shader \"" << path << "\" has failed: " << e.what() << std::endl;
    }
}

Shader::~Shader() {
    glDeleteShader(id);
}

Program::Program(std::initializer_list<std::shared_ptr<Shader>> shaders) : id(glCreateProgram()) {
    for(const auto& shader : shaders){
        glAttachShader(id, shader->id);
    }
    glLinkProgram(id);
    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cerr << "Linking program has failed: \n" << infoLog << std::endl;
    }
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
