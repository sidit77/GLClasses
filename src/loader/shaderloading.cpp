#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "glclasses/loader/shaderloading.h"

using json = nlohmann::json;

glc::Shader *glc::loader::loadShaderFromFile(const std::string &path, GLenum type) {
    std::ifstream file;
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try{
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        return loadShaderFromString(stream.str(), type);
    }
    catch(std::ifstream::failure& e)
    {
        std::cerr << "Loading shader \"" << path << "\" has failed: " << e.what() << std::endl;
    }
    return nullptr;

}

glc::Shader *glc::loader::loadShaderFromString(const std::string &source, GLenum type) {
    auto shader = std::make_unique<glc::Shader>(type);
    const char *c_str = source.c_str();
    glShaderSource(shader->id, 1, &c_str, NULL);
    glCompileShader(shader->id);
    int success;
    glGetShaderiv(shader->id, GL_COMPILE_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetShaderInfoLog(shader->id, 512, NULL, infoLog);
        std::cerr << "Compilation for shader has failed: \n" << infoLog << std::endl;
        return nullptr;
    }
    return shader.release();
}

bool linkProgram(glc::Program* program){
    glLinkProgram(program->id);
    int success;
    glGetProgramiv(program->id, GL_LINK_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetProgramInfoLog(program->id, 512, NULL, infoLog);
        std::cerr << "Linking program has failed: \n" << infoLog << std::endl;
    }
    return success;
}

glc::Program* glc::loader::createProgram(std::initializer_list<Shader*> list){
    auto program = std::make_unique<glc::Program>();
    for(auto shader : list){
        glAttachShader(program->id, shader->id);
    }
    if(linkProgram(program.get()))
        return program.release();
    return nullptr;
}

GLenum parseShaderType(const std::string& type){
    if(type == "VERTEX")
        return GL_VERTEX_SHADER;
    if(type == "FRAGMENT")
        return GL_FRAGMENT_SHADER;
    if(type == "GEOMETRY")
        return GL_GEOMETRY_SHADER;
    if(type == "TESS_EVALUATION")
        return GL_TESS_EVALUATION_SHADER;
    if(type == "TESS_CONTROL")
        return GL_TESS_CONTROL_SHADER;
    if(type == "COMPUTE")
        return GL_COMPUTE_SHADER;
    throw std::exception("Invalid shader type");
}

glc::Program *glc::loader::loadProgramFromFile(const std::string &path) {

    std::ifstream file;
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try{
        file.open(path);
        json j;
        file >> j;
        file.close();

        auto program = std::make_unique<glc::Program>();
        for(auto& shaderdesc : j["shaders"]){
            auto shader = std::unique_ptr<glc::Shader>(loadShaderFromFile(
                    std::filesystem::path(path).remove_filename().concat(shaderdesc["path"].get<std::string>()).string(),
                    parseShaderType(shaderdesc["type"])));
            glAttachShader(program->id, shader->id);
        }
        if(linkProgram(program.get()))
            return program.release();
        return nullptr;
    }
    catch(std::ifstream::failure& e)
    {
        std::cerr << "Loading program \"" << path << "\" has failed: " << e.what() << std::endl;
    }
    return nullptr;
}
