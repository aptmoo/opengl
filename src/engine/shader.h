#pragma once
#include "pch.h"

struct ShaderProgramSource
{
    std::string vertex;
    std::string fragment;
};

ShaderProgramSource ParseShader(const std::string& path);


class Shader
{
public:
    Shader(){};
    ~Shader();

    Shader& Use();

    void Compile(ShaderProgramSource source);
    unsigned int GetId(){return gl_id;};

    void SetFloat(const char* name, float value);
    void SetInt(const char* name, int value);

    void SetVec4(const char* name, glm::vec4 value);
    void SetVec4(const char* name, float x, float y, float z, float w);

private:
    unsigned int gl_id;
};