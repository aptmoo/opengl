#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall( glGenBuffers(1, &gl_ID) );
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, gl_ID) );
    GLCall( glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW) );
}

VertexBuffer::~VertexBuffer()
{
    GLCall( glDeleteBuffers(1, &gl_ID) );
}

void VertexBuffer::Bind()
{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, gl_ID));
}

void VertexBuffer::Unbind()
{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
}