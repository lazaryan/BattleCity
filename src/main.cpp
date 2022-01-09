#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

struct WindowSizeStruct {
    int x;
    int y;
};

WindowSizeStruct WindowSize = WindowSizeStruct{ 640, 480 };

void updateWindowSizeCallback(GLFWwindow * window, int width, int height)
{
    WindowSize.x = width;
    WindowSize.y = height;

    // update viewport for drawing
    glViewport(0, 0, WindowSize.x, WindowSize.y);
}

void keyActionCallback(GLFWwindow* window, int key, int scanner, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void regiserCallbacks(GLFWwindow* window)
{
    glfwSetWindowSizeCallback(window, updateWindowSizeCallback);
    glfwSetKeyCallback(window, keyActionCallback);
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    // use actual version opengl
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    
    // use core profiler
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(WindowSize.x, WindowSize.y, "Battle City", nullptr, nullptr);
    if (!pWindow)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout << "ERROR Load glad" << std::endl;
        return -1;
    }

    std::cout << "OpenGL version: " << GLVersion.major << "." << GLVersion.minor << std::endl;

    glClearColor(0, 1, 0, 1);

    regiserCallbacks(pWindow);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT); // color creating with glClearColor(0, 1, 0, 1)

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
	return 0;
}