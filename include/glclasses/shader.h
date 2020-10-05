#pragma once

#include <initializer_list>
#include <utility>
#include <string>
#include <memory>
#include "resource.h"

namespace glc {

    class Shader : public Resource{
    public:
        Shader(const std::string&, GLenum);
        ~Shader();
    };

    class Program : public Resource{
    public:
        Program(std::initializer_list<std::shared_ptr<Shader>> shaders);
        ~Program();
        void bind();
        GLint getUniformLocation(const std::string& name);
    };

}