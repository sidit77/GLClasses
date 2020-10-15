#include "glclasses/loader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <glclasses/shader.h>
#include <glclasses/texture.h>
#include <nlohmann/json.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using json = nlohmann::json;

std::string glc::loader::ResourceLoader::loadString(const std::string &path) {
    std::ifstream file;
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try{
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        return stream.str();
    }
    catch(std::ifstream::failure& e)
    {
        std::cerr << "Loading string \"" << path << "\" has failed: " << e.what() << std::endl;
    }
    return "";
}

std::vector<char> glc::loader::ResourceLoader::loadBytes(const std::string &path) {
    std::ifstream file;
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try{
        file.open(path, std::ios::binary|std::ios::ate);
        std::ifstream::pos_type pos = file.tellg();
        std::vector<char> result(pos);
        file.seekg(0, std::ios::beg);
        file.read(result.data(), pos);
        return result;
    }
    catch(std::ifstream::failure& e)
    {
        std::cerr << "Loading bytes \"" << path << "\" has failed: " << e.what() << std::endl;
    }
    return std::vector<char>(0);
}

bool glc::loader::ResourceLoader::writeString(const std::string &path, const std::string &str) {
    std::ofstream file (path);
    if (file.is_open())    {
        file << str;
        file.close();
        return true;
    }
    return false;
}

bool glc::loader::ResourceLoader::writeBytes(const std::string &path, std::vector<char> bytes) {
    std::ofstream file (path, std::ios::out | std::ios::binary);
    if (file.is_open())    {
        file.write(bytes.data(), bytes.size());
        file.close();
        return true;
    }
    return false;
}

std::string glc::loader::ResourceLoader::relativePath(const std::string &base, const std::string &path) {
    return std::filesystem::path(base).remove_filename().concat(path).string();
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
std::unique_ptr<glc::Program> glc::loader::loadResource<>(const std::string &path, ResourceLoader& loader) {
    auto j = json::parse(loader.loadString(path));

    auto program = std::make_unique<glc::ProgramBuilder>();

    for(auto& shaderdesc : j["shaders"]){
        auto shadersrc = loader.loadString(loader.relativePath(path, shaderdesc["path"].get<std::string>()));
        auto shader = std::make_unique<glc::Shader>(shadersrc, shaderdesc["type"].get<ShaderType>());
        program->attachShader(shader.get());
    }
    program->link();

    return program;
}

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

template<>
std::unique_ptr<glc::Texture> glc::loader::loadResource<>(const std::string &path, ResourceLoader& loader) {
    auto data = loader.loadBytes(path);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(false);
    stbi_uc *texdata = stbi_load_from_memory((const stbi_uc*)data.data(), data.size(), &width, &height, &nrChannels, 0);
    if(texdata) {
        auto texture = std::make_unique<glc::Texture>(width, height, getSizedFormat(nrChannels));
        glTextureSubImage2D(texture->id, 0, 0, 0, width, height, getFormat(nrChannels), GL_UNSIGNED_BYTE, texdata);
        glGenerateTextureMipmap(texture->id);
        glTextureParameteri(texture->id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(texture->id, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureParameteri(texture->id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(texture->id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(texdata);
        return texture;
    }else{
        std::cerr << "Could not load image from memory" << std::endl;
    }
    return nullptr;
}

