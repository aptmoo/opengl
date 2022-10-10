#pragma once
#include "pch.h"
#include "glutils.h"

class VertexBuffer
{
public:
    // VertexBuffer constructor.
    // NOTE: This constructor expects a raw size(see cpp file)
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    // Bind this vertex buffer
    void Bind();
    // Bind vertex buffer ID 0
    void Unbind();
private:
    // Internal ID
    unsigned int gl_ID;
};