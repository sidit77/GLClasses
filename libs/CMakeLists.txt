set(CMAKE_CXX_STANDARD 17)

add_library(glad "glad/src/glad.c")
target_include_directories(glad PUBLIC "glad/include")

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE "stb")

add_subdirectory(json)