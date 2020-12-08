#include <glclasses/buffer.h>

using namespace glc;

Buffer::Buffer(){
    glCreateBuffers(1, &id);
}

Buffer::~Buffer() {
    if(id != 0)
        glDeleteBuffers(1, &id);
}

void Buffer::bind(GLenum target) {
    glBindBuffer(target, id);
}

VertexArray::VertexArray() {
    glCreateVertexArrays(1, &id);
}

VertexArray::~VertexArray() {
    if(id != 0)
        glDeleteVertexArrays(1, &id);
}

void VertexArray::bind() {
    glBindVertexArray(id);
}
