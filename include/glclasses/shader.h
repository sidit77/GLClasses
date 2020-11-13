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
        Shader(const std::string& source, ShaderType type);
        ~Shader() override;
    };

    class Program : public Resource{
    public:
        Program();

        ~Program() override;
        void bind();
        GLint getUniformLocation(const std::string& name);
    };

    class ProgramBuilder : public Program{
    public:
        ProgramBuilder() = default;
        ProgramBuilder(std::initializer_list<Shader*> shader);
        ProgramBuilder& link();
        ProgramBuilder& attachShader(Shader* shader);
    };



}