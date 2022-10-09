#include "shader.h"
#include "glutils.h"
#include <sstream>

ShaderProgramSource ParseShader(const std::string &path)
{
    std::ifstream stream(path);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            if(type != ShaderType::NONE) ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

static unsigned int CompileShader(unsigned int type, const std::string &__source)
{
    unsigned int id = glCreateShader(type);
    const char *source = __source.c_str();

    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::printf("Shader compilation failed:\n%s\n", message);
        return 0;
    }
    return id;
}

static int LinkShader(const std::string &vertex, const std::string &fragment)
{
    unsigned int program = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment);

    // TODO: More streamlined method
    // Maybe make the resource manager responsible for this?
    // If either shader fails to compile, return a bright pink shader
    if (vs == 0 || fs == 0)
    {
        std::string vertexShader =
            "#version 330 core\n"
            "\n"
            "layout(location = 0) in vec4 position;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = position;\n"
            "}\n";

        std::string fragmentShader =
            "#version 330 core\n"
            "\n"
            "layout(location = 0) out vec4 color;\n"
            "void main()\n"
            "{\n"
            "   color = vec4(1.0, 0.0, 1.0, 1.0);\n"
            "}\n";

        vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    // Linkage and validation

    glLinkProgram(program);

    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetProgramInfoLog(program, length, &length, message);
        std::printf("Program linkage failed:\n%s\n", message);
        return 0;
    }

    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetProgramInfoLog(program, length, &length, message);
        std::printf("Program validation failed:\n%s\n", message);  
        return 0;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    std::printf("[Program ID: %d] Successfully loaded\n", program);

    return program;
}

Shader::~Shader()
{
    if(gl_id != 0)
    {
        glDeleteProgram(gl_id);
        std::printf("[Program ID: %d] Successfully unloaded\n", gl_id);
    }
}

Shader &Shader::Use()
{
    glUseProgram(gl_id);
    return *this;
}

void Shader::Compile(ShaderProgramSource source)
{
    gl_id = LinkShader(source.vertex, source.fragment);
}

void Shader::SetFloat(const char* name, float value)
{
    glUniform1f(glGetUniformLocation(gl_id, name), value);
}

void Shader::SetVec4(const char* name, glm::vec4 value)
{
    glUniform4f(glGetUniformLocation(gl_id, name), value.x, value.y, value.z, value.w);
}
void Shader::SetVec4(const char* name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(gl_id, name), x, y, z, w);
}