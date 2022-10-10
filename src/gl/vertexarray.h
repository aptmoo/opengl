#pragma once

#include "pch.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

class VertexArray
{
    private:
        unsigned int m_RendererID;

    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(VertexBuffer& vb, const VertexBufferLayout& layout);
        void Bind();
        void Unbind();
};