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

GLint Program::getInfo(GLenum info) {
    GLint result;
    glGetProgramiv(id, info, &result);
    return result;
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

template<typename T, size_t N>
void Program::setUniform(GLint location, GLsizei count, const T *v0) {
    static_assert(false, "type not supported!");
}

template<>
void Program::setUniform<GLfloat, 1>(GLint location, GLsizei count, const GLfloat* v0) {
    glProgramUniform1fv(id, location, count, v0);
}

template<>
void Program::setUniform<GLfloat, 2>(GLint location, GLsizei count, const GLfloat* v0) {
    glProgramUniform2fv(id, location, count, v0);
}

template<>
void Program::setUniform<GLfloat, 3>(GLint location, GLsizei count, const GLfloat* v0) {
    glProgramUniform3fv(id, location, count, v0);
}

template<>
void Program::setUniform<GLfloat, 4>(GLint location, GLsizei count, const GLfloat* v0) {
    glProgramUniform4fv(id, location, count, v0);
}

template<>
void Program::setUniform<GLdouble, 1>(GLint location, GLsizei count, const GLdouble* v0) {
    glProgramUniform1dv(id, location, count, v0);
}

template<>
void Program::setUniform<GLdouble, 2>(GLint location, GLsizei count, const GLdouble* v0) {
    glProgramUniform2dv(id, location, count, v0);
}

template<>
void Program::setUniform<GLdouble, 3>(GLint location, GLsizei count, const GLdouble* v0) {
    glProgramUniform3dv(id, location, count, v0);
}

template<>
void Program::setUniform<GLdouble, 4>(GLint location, GLsizei count, const GLdouble* v0) {
    glProgramUniform4dv(id, location, count, v0);
}

template<>
void Program::setUniform<GLuint, 1>(GLint location, GLsizei count, const GLuint* v0) {
    glProgramUniform1uiv(id, location, count, v0);
}

template<>
void Program::setUniform<GLuint, 2>(GLint location, GLsizei count, const GLuint* v0) {
    glProgramUniform2uiv(id, location, count, v0);
}

template<>
void Program::setUniform<GLuint, 3>(GLint location, GLsizei count, const GLuint* v0) {
    glProgramUniform3uiv(id, location, count, v0);
}

template<>
void Program::setUniform<GLuint, 4>(GLint location, GLsizei count, const GLuint* v0) {
    glProgramUniform4uiv(id, location, count, v0);
}

template<>
void Program::setUniform<GLint, 1>(GLint location, GLsizei count, const GLint* v0) {
    glProgramUniform1iv(id, location, count, v0);
}

template<>
void Program::setUniform<GLint, 2>(GLint location, GLsizei count, const GLint* v0) {
    glProgramUniform2iv(id, location, count, v0);
}

template<>
void Program::setUniform<GLint, 3>(GLint location, GLsizei count, const GLint* v0) {
    glProgramUniform3iv(id, location, count, v0);
}

template<>
void Program::setUniform<GLint, 4>(GLint location, GLsizei count, const GLint* v0) {
    glProgramUniform4iv(id, location, count, v0);
}


template<typename T, size_t N, size_t M>
void Program::setUniformMatrix(GLint location, GLsizei count, GLboolean transpose, const T *v0) {
    static_assert(false, "type not supported!");
}

template<>
void Program::setUniformMatrix<GLfloat, 2, 2>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *v0) {
    glProgramUniformMatrix2fv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLfloat, 3, 3>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *v0) {
    glProgramUniformMatrix3fv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLfloat, 4, 4>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *v0) {
    glProgramUniformMatrix4fv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLfloat, 2, 3>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *v0) {
    glProgramUniformMatrix2x3fv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLfloat, 3, 2>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *v0) {
    glProgramUniformMatrix3x2fv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLfloat, 2, 4>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *v0) {
    glProgramUniformMatrix2x4fv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLfloat, 4, 2>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *v0) {
    glProgramUniformMatrix4x2fv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLfloat, 3, 4>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *v0) {
    glProgramUniformMatrix3x4fv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLfloat, 4, 3>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *v0) {
    glProgramUniformMatrix4x3fv(id, location, count, transpose, v0);
}


template<>
void Program::setUniformMatrix<GLdouble, 2, 2>(GLint location, GLsizei count, GLboolean transpose, const GLdouble *v0) {
    glProgramUniformMatrix2dv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLdouble, 3, 3>(GLint location, GLsizei count, GLboolean transpose, const GLdouble *v0) {
    glProgramUniformMatrix3dv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLdouble, 4, 4>(GLint location, GLsizei count, GLboolean transpose, const GLdouble *v0) {
    glProgramUniformMatrix4dv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLdouble, 2, 3>(GLint location, GLsizei count, GLboolean transpose, const GLdouble *v0) {
    glProgramUniformMatrix2x3dv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLdouble, 3, 2>(GLint location, GLsizei count, GLboolean transpose, const GLdouble *v0) {
    glProgramUniformMatrix3x2dv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLdouble, 2, 4>(GLint location, GLsizei count, GLboolean transpose, const GLdouble *v0) {
    glProgramUniformMatrix2x4dv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLdouble, 4, 2>(GLint location, GLsizei count, GLboolean transpose, const GLdouble *v0) {
    glProgramUniformMatrix4x2dv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLdouble, 3, 4>(GLint location, GLsizei count, GLboolean transpose, const GLdouble *v0) {
    glProgramUniformMatrix3x4dv(id, location, count, transpose, v0);
}

template<>
void Program::setUniformMatrix<GLdouble, 4, 3>(GLint location, GLsizei count, GLboolean transpose, const GLdouble *v0) {
    glProgramUniformMatrix4x3dv(id, location, count, transpose, v0);
}


template<typename T>
void Program::getUniform(GLint location, T* params) {
    static_assert(false, "type not supported!");
}

template<>
void Program::getUniform(GLint location, GLfloat* params) {
    glGetUniformfv(id, location, params);
}

template<>
void Program::getUniform(GLint location, GLdouble* params) {
    glGetUniformdv(id, location, params);
}

template<>
void Program::getUniform(GLint location, GLint* params) {
    glGetUniformiv(id, location, params);
}

template<>
void Program::getUniform(GLint location, GLuint* params) {
    glGetUniformuiv(id, location, params);
}