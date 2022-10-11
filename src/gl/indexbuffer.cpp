#include "indexbuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : gl_ID(0)
{
    static_assert(sizeof(unsigned int) == sizeof(GLuint), "GLuint does not equal uint!");

    this->count = count;

    GLCall( glGenBuffers(1, &gl_ID) );
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_ID) );
    GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW) );
}

IndexBuffer::~IndexBuffer()
{
    GLCall( glDeleteBuffers(1, &gl_ID) );
}

unsigned int IndexBuffer::GetCount()
{
    return count;
}

void IndexBuffer::Bind()
{
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_ID));
}

void IndexBuffer::Unbind()
{
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
}