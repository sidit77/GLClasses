#pragma once

#include <utility>
#include <string>
#include <glad/glad.h>

namespace glc{
    class Resource {
    protected:
        GLenum type;
        explicit Resource(GLenum type) : type(type) {};
        virtual ~Resource() = default;

    public:
        GLuint id{};
        Resource(Resource&& other)  noexcept {
            id = other.id;
            type = other.type;
            other.id = 0;
        }

        Resource& operator=(Resource&& other) noexcept {
            if (this == &other)
                return *this;
            this->~Resource();
            id = other.id;
            type = other.type;
            other.id = 0;
            return *this;
        }
        Resource(const Resource &) = delete;
        Resource &operator=(const Resource &) = delete;
        void setLabel(std::string label){
            glObjectLabel(type, id, label.length(), label.c_str());
        }
        /*
        std::string getLabel() const {
            GLsizei length = 0;
            glGetObjectLabel(type, id, 0, &length, nullptr);
            std::string label;
            label.resize(length);
            glGetObjectLabel(type, id, label.length(), &length, label.data());
        }*/
    };
}
