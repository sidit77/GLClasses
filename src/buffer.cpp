#include <glclasses/buffer.h>

using namespace glc;

VertexBuffer::VertexBuffer(){
    glCreateBuffers(1, &id);
}

VertexBuffer::~VertexBuffer() {
    if(id != 0)
        glDeleteBuffers(1, &id);
}

void VertexBuffer::bind(GLenum target) {
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
