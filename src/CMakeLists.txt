set(CMAKE_CXX_STANDARD 17)

file(GLOB GLCLASSES_SOURCES "*.cpp")
file(GLOB GLCLASSES_HEADERS "../include/glclasses/*.h")

add_library(glclasses ${GLCLASSES_SOURCES} ${GLCLASSES_HAEDERS})

target_include_directories(glclasses PUBLIC ../include)
target_link_libraries(glclasses glad)
