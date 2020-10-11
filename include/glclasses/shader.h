#pragma once

#include <initializer_list>
#include <string>
#include "resource.h"

namespace glc {

    enum ShaderType : GLenum {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
        COMPUTE = GL_COMPUTE_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER,
        TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
        TESS_CONTROL = GL_TESS_CONTROL_SHADER
    };

    class Shader : public Resource{
    public:
        Shader(std::string source, ShaderType type);
        ~Shader();
    };

    class Program : public Resource{
    public:
        Program();

        ~Program();
        void bind();
        GLint getUniformLocation(const std::string& name);
    };

    class ProgramBuilder : public Program{
    public:
        ProgramBuilder() = default;
        ProgramBuilder(std::initializer_list<Shader*> shader);
        ~ProgramBuilder() = default;
        ProgramBuilder& link();
        ProgramBuilder& attachShader(Shader* shader);
    };



}