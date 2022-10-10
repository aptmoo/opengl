#include "pch.h"
#include "gl/shader.h"
#include "gl/glutils.h"

#include "gl/mesh.h"

#include "gl/indexbuffer.h"
#include "gl/vertexarray.h"

int main(void)
{

    #ifdef LOGFILE
    freopen("game.log", "w", stdout);
    #endif

    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(1280, 720, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        return -1;

    std::printf("%s\n", glGetString(GL_VERSION));

    float positions[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };


    // unsigned int buffer;
    // glGenBuffers(1, &buffer);
    // glBindBuffer(GL_ARRAY_BUFFER, buffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8, positions, GL_STATIC_DRAW);

    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

    // unsigned int ibo;
    // glGenBuffers(1, &ibo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*6, indices, GL_STATIC_DRAW);

    // std::vector<SimpleVertex> verts = 
    // {
    //     {glm::vec2(-0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},
    //     {glm::vec2(0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},
    //     {glm::vec2(0.5f, 0.5f), glm::vec3(1.0f)},
    //     {glm::vec2(-0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},
    // };

    // std::vector<unsigned int> indices = 
    // {
    //     0, 1, 2,
    //     2, 3, 0
    // };


    // SimpleMesh msh(verts, indices);;


    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));
    IndexBuffer ib(indices, 6);

    VertexBufferLayout layout;
    layout.AddFloat(2);

    va.AddBuffer(vb, layout);

    Shader test;
    test.Compile(ParseShader("shaders/debug.shader"));
    test.Use();

    float delta = 0.0f;
    float previousFrameTime = 0.0f;
    float currentFrameTime;

    float r = 0.0f;
    float increment = 0.5f;

    while (!glfwWindowShouldClose(window))
    {
        currentFrameTime = glfwGetTime();
        delta = currentFrameTime - previousFrameTime;
        previousFrameTime = currentFrameTime;

        glClear(GL_COLOR_BUFFER_BIT);

        if(r > 1.0f)
            increment = -0.5f;
        else if(r < 0.0f)
            increment = 0.5f;

        r += increment * delta;

        test.Use();
        test.SetVec4("u_Color", r, 0.3f, 0.8f, 1.0f);
        
        va.Bind();
        ib.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}