#include "GPUBuffer.hpp"

GPUBuffer::GPUBuffer()
{

}

GPUBuffer::~GPUBuffer() {
    if(id) glDeleteBuffers(1, &id);
}

void GPUBuffer::Create(Type type, size_t size, const void* data) {
    bufferType = type;
    elementCount = size / (type == Vertex ? sizeof(float) : sizeof(unsigned int));
    
    GLenum glType = GL_ARRAY_BUFFER;
    switch(type) {
        case Index: glType = GL_ELEMENT_ARRAY_BUFFER; break;
        case Uniform: glType = GL_UNIFORM_BUFFER; break;
    }

    glGenBuffers(1, &id);
    glBindBuffer(glType, id);
    glBufferData(glType, size, data, GL_STATIC_DRAW);
}

void GPUBuffer::Update(size_t offset, size_t size, const void* data) {
    GLenum glType = GL_ARRAY_BUFFER;
    switch(bufferType) {
        case Index: glType = GL_ELEMENT_ARRAY_BUFFER; break;
        case Uniform: glType = GL_UNIFORM_BUFFER; break;
    }

    glBindBuffer(glType, id);
    glBufferSubData(glType, offset, size, data);
}

void GPUBuffer::Bind() const {
    GLenum glType = GL_ARRAY_BUFFER;
    switch(bufferType) {
        case Index: glType = GL_ELEMENT_ARRAY_BUFFER; break;
        case Uniform: glType = GL_UNIFORM_BUFFER; break;
    }
    glBindBuffer(glType, id);
}