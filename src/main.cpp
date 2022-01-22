#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer/ShaderPropgram.hpp"

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

const char* vertexShader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position, 1.0);"
"}";

const char* fragmentShader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(color, 1.0);"
"}";

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

    const std::string strVertexShader(vertexShader);
    const std::string strFragmentShader(fragmentShader);

    // Renderer::ShaderPropgram program = Renderer::ShaderPropgram(vertexShader, fragmentShader);
    // shortcat
    Renderer::ShaderPropgram shaderProgram(vertexShader, fragmentShader);
    if (!shaderProgram.isCompiled())
    {
        std::cerr << "ERROR:PROGRAM_CREATOR => Can`t create shader program" << std::endl;
        return -1;
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
        shaderProgram.use();
        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
	return 0;
}