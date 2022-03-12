#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer/ShaderPropgram.hpp"
#include "Resources/ResourceManager.hpp"

// vertices of the triangle to be drawn (each vertex from -1 to 1) 
GLfloat points[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
};

// the colors of these vertices (from 0.0 to 1.0) 
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
};

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

int main(int args, char** argv)
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

    {
        Resources::ResourceManager resourceManager(argv[0]);

        resourceManager.loadTexture("Default", "assets/textures/map_16x16.png");

        auto pDefaultShaderProgram = resourceManager.loadShaderProgram("defaultShaderProgram", "assets/shaders/vertex.txt", "assets/shaders/fragment.txt");
        if (!pDefaultShaderProgram)
        {
            std::cerr << "ERROR::MAIN => Can`t create shader program" << std::endl;
        }

        // create buffer for vertex
        GLuint pointsVertexBoooferObject = 0;
        glGenBuffers(1, &pointsVertexBoooferObject);
        glBindBuffer(GL_ARRAY_BUFFER, pointsVertexBoooferObject);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

        // create buffer for fragment colors
        GLuint colorsVertexBoooferObject = 0;
        glGenBuffers(1, &colorsVertexBoooferObject);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVertexBoooferObject);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        //у нас vertex шейдер принимаеи 2 парамера. Теперь нужно для них создать буфер и разрешить
        //создаем буфер
        GLuint vertexArrayObject = 0;
        glGenVertexArrays(1, &vertexArrayObject);
        glBindVertexArray(vertexArrayObject);

        //и разрешаем переменную и говорим, какой буфер в него будет падать и по сколько элементов
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, pointsVertexBoooferObject);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVertexBoooferObject);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT); // color creating with glClearColor(0, 1, 0, 1)

            // теперь в цикле используем нашу шейдер программу, говорим какой буфер используем и рисуем все
            pDefaultShaderProgram->use();
            glBindVertexArray(vertexArrayObject);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
	return 0;
}