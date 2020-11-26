#pragma once



#include <initializer_list>
#include <string>
#include "resource.h"

#if __has_include(<glm/glm.hpp>)
#define GLC_GLM_PRESENT TRUE
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

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
        void setUniform(GLint location, const std::array<T, N>& v) {
            setUniform<T, N>(location, 1, v);
        }

        template<typename T>
        void setUniform(GLint location, const T& v) {
            setUniform<T, 1>(location, 1, &v);
        }

#if GLC_GLM_PRESENT
        template<typename T, glm::precision P>
        void setUniform(GLint location, const glm::tvec2<T, P>& vec){
            setUniform<T, 2>(location, 1, glm::value_ptr(vec));
        }
        template<typename T, glm::precision P>
        void setUniform(GLint location, const glm::tvec3<T, P>& vec){
            setUniform<T, 3>(location, 1, glm::value_ptr(vec));
        }
        template<typename T, glm::precision P>
        void setUniform(GLint location, const glm::tvec4<T, P>& vec){
            setUniform<T, 4>(location, 1, glm::value_ptr(vec));
        }

        template<typename T, glm::precision P>
        void setUniformMatrix(GLint location, GLboolean transpose, const glm::tmat2x2<T, P>& mat){
            setUniformMatrix<T, 2, 2>(location, 1, transpose, glm::value_ptr(mat));
        }

        template<typename T, glm::precision P>
        void setUniformMatrix(GLint location, GLboolean transpose, const glm::tmat3x3<T, P>& mat){
            setUniformMatrix<T, 3, 3>(location, 1, transpose, glm::value_ptr(mat));
        }

        template<typename T, glm::precision P>
        void setUniformMatrix(GLint location, GLboolean transpose, const glm::tmat4x4<T, P>& mat){
            setUniformMatrix<T, 4, 4>(location, 1, transpose, glm::value_ptr(mat));
        }

        template<typename T, glm::precision P>
        void setUniformMatrix(GLint location, GLboolean transpose, const glm::tmat2x3<T, P>& mat){
            setUniformMatrix<T, 2, 3>(location, 1, transpose, glm::value_ptr(mat));
        }

        template<typename T, glm::precision P>
        void setUniformMatrix(GLint location, GLboolean transpose, const glm::tmat3x2<T, P>& mat){
            setUniformMatrix<T, 3, 2>(location, 1, transpose, glm::value_ptr(mat));
        }

         template<typename T, glm::precision P>
        void setUniformMatrix(GLint location, GLboolean transpose, const glm::tmat2x4<T, P>& mat){
            setUniformMatrix<T, 2, 4>(location, 1, transpose, glm::value_ptr(mat));
        }

        template<typename T, glm::precision P>
        void setUniformMatrix(GLint location, GLboolean transpose, const glm::tmat4x2<T, P>& mat){
            setUniformMatrix<T, 4, 2>(location, 1, transpose, glm::value_ptr(mat));
        }

        template<typename T, glm::precision P>
        void setUniformMatrix(GLint location, GLboolean transpose, const glm::tmat4x3<T, P>& mat){
            setUniformMatrix<T, 2, 3>(location, 1, transpose, glm::value_ptr(mat));
        }

        template<typename T, glm::precision P>
        void setUniformMatrix(GLint location, GLboolean transpose, const glm::tmat3x4<T, P>& mat){
            setUniformMatrix<T, 3, 2>(location, 1, transpose, glm::value_ptr(mat));
        }

        template<typename T>
        void setUniformMatrix(const std::string& name, GLboolean transpose, const T& mat) {
            setUniformMatrix(getUniformLocation(name), transpose, mat);
        }
#endif

        template<typename T, size_t N>
        void setUniform(const std::string& name, GLsizei count, const T *v0) {
            setUniform<T, N>(getUniformLocation(name), count, v0);
        }

        template<typename T>
        void setUniform(const std::string& name, const T& v) {
            setUniform(getUniformLocation(name), v);
        }

        template<typename T, size_t N, size_t M>
        void setUniformMatrix(const std::string& name, GLsizei count, GLboolean transpose, const T* v0){
            setUniformMatrix<T, N, M>(getUniformLocation(name), count, transpose, v0);
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