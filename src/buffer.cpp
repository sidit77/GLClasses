#include <glclasses/buffer.h>
#include <glclasses/glerror.h>

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

void Buffer::bindBase(GLenum target, GLuint slot) {
    glBindBufferBase(target, slot, id);
}

void Buffer::unmap() {
    glUnmapNamedBuffer(id);
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

Buffer glc::createBuffer(GLsizeiptr size, GLbitfield flags, const void *data) {
    Buffer buffer;
    glNamedBufferStorage(buffer.id, size, data, flags);
    CHECK_GL_ERROR
    return buffer;
}
