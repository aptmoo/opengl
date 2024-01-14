#include "pch.h"
#include "gl/shader.h"
#include "vendor/stb_image.h"
#include "gl/glutils.h"

#include "gl/texture.h"
#include "gl/renderer.h"

int window_w = 1280;
int window_h = 720;

float sz = 5;


static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    sz += (float)yoffset;
}

static void FrameBufferSizeCallback(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, w, h);
    window_w = w;
    window_h = h;
}

int main(void)
{

    #ifdef LOGFILE
    freopen("game.log", "w", stdout);
    #endif

    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(1280, 720, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
    glfwSetScrollCallback(window, ScrollCallback);

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        return -1;

    std::printf("%s\n", glGetString(GL_VERSION));

    // float positions[] = {
    //     -0.5f, -0.5f, 0.0f, 0.0f,
    //     0.5f, -0.5f, 1.0f, 0.0f,
    //     0.5f, 0.5f, 1.0f, 1.0f,
    //     -0.5f, 0.5f, 0.0f, 1.0f
    // };


    // float positions[] = {
    //     -50.0f, -50.0f, 0.0f, 0.0f, // 0
    //     50.0f, -50.0f, 1.0f, 0.0f, // 1
    //     50.0f, 50.0f, 1.0f, 1.0f, // 2
    //     -50.0f, 50.0f, 0.0f, 1.0f  // 3
    // };

    std::vector<float> positions =
    {
        -50.0f, -50.0f, 0.0f, 0.0f, // 0
        50.0f, -50.0f, 1.0f, 0.0f, // 1
        50.0f, 50.0f, 1.0f, 1.0f, // 2
        -50.0f, 50.0f, 0.0f, 1.0f  // 3
    };



    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va;
    VertexBuffer vb(positions.data(), positions.size() * sizeof(float));
    IndexBuffer ib(indices, 6);

    VertexBufferLayout layout;
    layout.AddFloat(2);
    layout.AddFloat(2);

    va.AddBuffer(vb, layout);

    Shader test;
    test.Compile(ParseShader("shaders/debug.shader"));
    test.Use();

    Texture tex("textures/heit.png");
    tex.Bind();

    test.SetInt("u_Texture", 0);

    Renderer thingy;

    
    // glm::mat4 proj = glm::perspective(glm::radians(45.f), (float)1280/(float)720, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0f);


    

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

        thingy.Clear();

        if(r > 1.0f)
            increment = -0.5f;
        else if(r < 0.0f)
            increment = 0.5f;

        r += increment * delta;

        double px, py;

        glfwGetCursorPos(window, &px, &py);

        glm::mat4 proj = glm::ortho(0.0f, (float)window_w, 0.0f, (float)window_h, -1.0f, 1.0f);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(px, -py + window_h, 0));
        model = glm::scale(model, glm::vec3(sz, sz, 0));

        glm::mat4 mvp = proj * view * model;
        test.SetMat4("u_MVP", mvp);
        
        test.SetVec4("u_Color", r, 0.3f, 0.8f, 1.0f);
        thingy.Draw(va, ib, test);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

