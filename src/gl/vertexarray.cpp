#include "vertexarray.h"

VertexArray::VertexArray()
{
    GLCall( glGenVertexArrays(1, &m_RendererID) );
}

VertexArray::~VertexArray()
{
    GLCall( glDeleteVertexArrays(1, &m_RendererID) );
}

void VertexArray::AddBuffer(VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const std::vector<VertexBufferElement> elements = layout.GetElements();
    std::cout << elements.size();
    uintptr_t offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        std::printf("%d", layout.GetStride());
        const VertexBufferElement element = elements[i];
        GLCall( glEnableVertexAttribArray(i) );
        GLCall( glVertexAttribPointer(i, element.count, element.type, element.normalized,
                                      layout.GetStride(), (void*)offset) );
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind()
{
    GLCall( glBindVertexArray(m_RendererID) );
}

void VertexArray::Unbind()
{
    GLCall( glBindVertexArray(0) );
};