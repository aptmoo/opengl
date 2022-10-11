#pragma once
#include "pch.h"

#include "glutils.h"

#include "shader.h"
#include "indexbuffer.h"
#include "vertexbuffer.h"
#include "vertexarray.h"

// NOTE: Renderer != Render Pass!
class Renderer
{
public:
    void Clear();
    void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader);
private:

};