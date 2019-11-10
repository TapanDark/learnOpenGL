#include "window_utils.hpp"
#include <iostream>

MyWindow::MyWindow(int width, int height, const char *title) : width(width), height(height), title(title)
{
    init_window();
}

void MyWindow::init_window()
{
    std::cout << "Initializing GLFW" << std::endl;
    // Initialize and configure GLFW
    if (!glfwInit())
    {
        std::cout << "GLFW INIT Failed" << std::endl;
        throw std::exception();
    }
    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create window!" << std::endl;
        glfwTerminate();
        throw std::exception();
    }

    /* Make the window's context current */
    // TODO: Does this api need to be exposed?
    glfwMakeContextCurrent(window);
}

// set callback to resize our GL framebuffer upon window resize

void MyWindow::setFramebufferResizeCallback(void (*callback)(GLFWwindow *, int, int))
{
    glfwSetFramebufferSizeCallback(window, callback);
}

void MyWindow::setCursorPosCallback(void (*callback)(GLFWwindow *, double, double))
{
    std::cout<<"Setting cursor position callback\n";
    glfwSetCursorPosCallback(window, callback);
}

void MyWindow::setCursorDisabled()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void MyWindow::setCursorEnabled()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool MyWindow::isOpen()
{
    return !glfwWindowShouldClose(window);
}

void MyWindow::refresh()
{
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

void MyWindow::setClose()
{
    glfwSetWindowShouldClose(window, true);
}

bool MyWindow::isKeyPressed(int key)
{
    // set close intent if ESCAPE is pressed, nice.
    if (glfwGetKey(window, key) == GLFW_PRESS)
        return true;
    else
        return false;
}

MyWindow::~MyWindow()
{
    glfwTerminate();
}
