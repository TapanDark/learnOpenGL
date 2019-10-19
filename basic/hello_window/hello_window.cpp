#include <GLFW/glfw3.h>
#include <iostream>

//Callback methods for window resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//Method to process input, if any.
void processInput(GLFWwindow *window);

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int main(void)
{
    GLFWwindow *window;

    std::cout << "Initializing GLFW" << std::endl;
    // Initialize and configure GLFW
    if (!glfwInit())
    {
        std::cout << "GLFW INIT Failed" << std::endl;
        return -1;
    }
    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    // set callback to resize our GL framebuffer upon window resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //perform actions on input
        processInput(window);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    std::cout << "Goodbye world!" << std::endl;
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // match our GL viewport size to window dimensions.
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    // set close intent if ESCAPE is pressed, nice.
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        std::cout<<"ESCAPE KEY PRESSED!"<<std::endl;
        glfwSetWindowShouldClose(window, true);
    }
}