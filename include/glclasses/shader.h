#pragma once

#include <initializer_list>
#include <string>
#include "resource.h"

namespace glc {

    class Shader : public Resource{
    public:
        Shader(GLenum type);
        ~Shader();
    };

    class Program : public Resource{
    public:
        Program();

        ~Program();
        void bind();
        GLint getUniformLocation(const std::string& name);
    };

}