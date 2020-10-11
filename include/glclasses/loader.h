#pragma once

#include <string>
#include <memory>

namespace glc::loader {

    template<typename T>
    std::unique_ptr<T> loadResource(const std::string& path);
}