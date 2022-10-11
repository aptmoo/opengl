#include "renderer.h"

void Renderer::Clear()
{
    GLCall( glClear(GL_COLOR_BUFFER_BIT) );
}

void Renderer::Draw(VertexArray& va, IndexBuffer& ib, Shader& shader)
{
    shader.Use();
    
    va.Bind();
    ib.Bind();

    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

}