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

        template<typename T, size_t N>
        void setUniform(GLint location, GLsizei count, const T* v0);

        template<typename T, size_t N, size_t M>
        void setUniformMatrix(GLint location, GLsizei count, GLboolean transpose, const T* v0);

        template<typename T, size_t N>
        void setUniform(GLint location, T const (&v)[N]) {
            setUniform<T, N>(location, 1, v);
        }

        template<typename T>
        void setUniform(GLint location, const T& v){
            setUniform<T, 1>(location, 1, &v);
        }

        template<typename T, size_t N>
        void setUniform(const std::string& name, GLsizei count, const T *v0) {
            setUniform<T, N>(getUniformLocation(name), count, v0);
        }

        template<typename T, size_t N, size_t M>
        void setUniformMatrix(const std::string& name, GLsizei count, GLboolean transpose, const T* v0){
            setUniformMatrix<T, N, M>(getUniformLocation(name), count, transpose, v0);
        }
        
        template<typename T, size_t N>
        void setUniform(const std::string& name, T const (&v)[N]) {
            setUniform<T>(getUniformLocation(name), v);
        }

        template<typename T>
        void setUniform(const std::string& name, const T& v) {
            setUniform<T>(getUniformLocation(name), v);
        }

    };

    class ProgramBuilder : public Program{
    public:
        ProgramBuilder() = default;
        ProgramBuilder(std::initializer_list<Shader*> shader);
        ProgramBuilder& link();
        ProgramBuilder& attachShader(Shader* shader);
    };



}