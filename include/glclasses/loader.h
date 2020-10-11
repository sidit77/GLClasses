#pragma once

#include <string>
#include <vector>
#include <memory>

namespace glc::loader {

    class ResourceLoader {
    public:
        virtual std::string loadString(const std::string& path);
        virtual std::vector<char> loadBytes(const std::string& path);
        virtual std::string relativePath(const std::string& base, const std::string& path);
    };

    inline ResourceLoader defaultloader;

    template<typename T>
    std::unique_ptr<T> loadResource(const std::string& path, ResourceLoader& loader = defaultloader);
}