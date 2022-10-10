#pragma once
#include "pch.h"
#include "glutils.h"
#include <vector>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch(type)
        {
            case GL_FLOAT           : return sizeof(GLfloat);
            case GL_UNSIGNED_INT    : return sizeof(GLuint);
            case GL_UNSIGNED_BYTE   : return sizeof(GLbyte);
        }
        assert(false);
        return 0;
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout()
        : gl_Stride(0) {};

    inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const { return gl_Stride; };

    void AddFloat(unsigned int count)   { Push(GL_FLOAT, count, false); }
    void AddUInt(unsigned int count)   { Push(GL_UNSIGNED_INT, count, false); }
    void AddUChar(unsigned int count)   { Push(GL_UNSIGNED_BYTE, count, true); }


public:
    std::vector<VertexBufferElement> m_Elements;

private:   
    void Push(unsigned int type, unsigned int count, unsigned char normalized)
    {
        // Explicit type casting to keep gcc happy
        m_Elements.push_back((VertexBufferElement){type, count, normalized});
        gl_Stride += count * VertexBufferElement::GetSizeOfType(type);
    };
    unsigned int gl_Stride;
};