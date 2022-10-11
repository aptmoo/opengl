#include "pch.h"
#include "gl/shader.h"
#include "vendor/stb_image.h"
#include "gl/glutils.h"

#include "gl/texture.h"
#include "gl/renderer.h"

float px, py;

static void MouseCursorPosCallback(GLFWwindow *window, double x, double y)
{
    px = (float)x;
    py = (float)y;
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

    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, MouseCursorPosCallback);

    if (glewInit() != GLEW_OK)
        return -1;

    std::printf("%s\n", glGetString(GL_VERSION));

    // float positions[] = {
    //     -0.5f, -0.5f, 0.0f, 0.0f,
    //     0.5f, -0.5f, 1.0f, 0.0f,
    //     0.5f, 0.5f, 1.0f, 1.0f,
    //     -0.5f, 0.5f, 0.0f, 1.0f
    // };


    float positions[] = {
        100.0f, 100.0f, 0.0f, 0.0f, // 0
        200.0f, 100.0f, 1.0f, 0.0f, // 1
        200.0f, 200.0f, 1.0f, 1.0f, // 2
        100.0f, 200.0f, 0.0f, 1.0f  // 3
    };



    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };


    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
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

    glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    // glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 ident = glm::mat4(1.0f);
    glm::vec3 trvec = glm::vec3(-100, 0, 0);
    glm::mat4 view = glm::translate(ident, trvec);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

    glm::mat4 mvp = proj * view * model;

    test.SetMat4("u_MVP", mvp);



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
        
        test.SetVec4("u_Color", r, 0.3f, 0.8f, 1.0f);
        thingy.Draw(va, ib, test);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

