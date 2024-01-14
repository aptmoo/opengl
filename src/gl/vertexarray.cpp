#include "vertexarray.h"

VertexArray::VertexArray()
    : gl_ID(0)
{
    GLCall( glCreateVertexArrays(1, &gl_ID) );
}

VertexArray::~VertexArray()
{
    GLCall( glDeleteVertexArrays(1, &gl_ID) );
}

void VertexArray::AddBuffer(VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const std::vector<VertexBufferElement> elements = layout.GetElements();
    uintptr_t offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const VertexBufferElement element = elements[i];
        GLCall( glEnableVertexAttribArray(i) );
        GLCall( glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (void*)offset) );

        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind()
{
    GLCall( glBindVertexArray(gl_ID) );
}

void VertexArray::Unbind()
{
    GLCall( glBindVertexArray(0) );
};