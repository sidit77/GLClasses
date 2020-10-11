#include "glclasses/loader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <glclasses/shader.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

template<>
std::unique_ptr<std::string> glc::loader::loadResource<>(const std::string &path) {
    std::ifstream file;
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try{
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        return std::make_unique<std::string>(stream.str());
    }
    catch(std::ifstream::failure& e)
    {
        std::cerr << "Loading string \"" << path << "\" has failed: " << e.what() << std::endl;
    }
    return nullptr;
}

namespace glc {
    NLOHMANN_JSON_SERIALIZE_ENUM( ShaderType, {
        {ShaderType::VERTEX, "VERTEX"},
        {ShaderType::FRAGMENT, "FRAGMENT"},
        {ShaderType::COMPUTE, "COMPUTE"},
        {ShaderType::GEOMETRY, "GEOMETRY"},
        {ShaderType::TESS_EVALUATION, "TESS_EVALUATION"},
        {ShaderType::TESS_CONTROL, "TESS_CONTROL"},
    })
}

template<>
std::unique_ptr<glc::Program> glc::loader::loadResource<>(const std::string &path) {
    auto jsonstr = loadResource<std::string>(path);
    if(!jsonstr)
        return nullptr;

    auto j = json::parse(*jsonstr);

    auto program = std::make_unique<glc::ProgramBuilder>();

    for(auto& shaderdesc : j["shaders"]){
        auto shadersrc = loadResource<std::string>(std::filesystem::path(path).remove_filename().concat(shaderdesc["path"].get<std::string>()).string());
        if(!shadersrc)
            continue;

        auto shader = std::make_unique<glc::Shader>(*shadersrc, shaderdesc["type"].get<ShaderType>());
        program->attachShader(shader.get());
    }
    program->link();

    return program;
}

