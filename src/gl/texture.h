#pragma once
#include "pch.h"
#include "glutils.h"

class Texture
{
public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth(){ return gl_Width; };
    inline int GetHeight(){ return gl_Height; }
private:
    unsigned int gl_ID;
    unsigned char* p_LocalBuffer;
    int gl_Width, gl_Height, gl_BPP;
};