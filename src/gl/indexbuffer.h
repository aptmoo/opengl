#pragma once
#include "pch.h"
#include "glutils.h"

class IndexBuffer
{
public:
    // IndexBuffer constructor.
    // NOTE: This constructor calculates the size by itself
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    unsigned int GetCount();

    // Bind this vertex buffer
    void Bind();
    // Bind vertex buffer ID 0
    void Unbind();
private:
    // Internal ID
    unsigned int count;
    unsigned int gl_ID;
};