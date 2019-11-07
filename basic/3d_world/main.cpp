#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string.h>
#include <glm/glm.hpp>
#include <shader/program_object.hpp>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

//Callback methods for window resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//Method to process input, if any.
void processInput(GLFWwindow *window);

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

void init_window(GLFWwindow **window);

int main(void)
{
    GLFWwindow *window;
    init_window(&window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, //triangle left
        0.5f, -0.5f, 0.0f,  //triangle right
        0.0f, 0.5f, 0.0f,   //triangle top
        -0.5f, 0.5f, 0.0f,  //rectangle top left
        0.5f, 0.5f, 0.0f    //rectangle top right
    };

    //Create a vertex buffer to store our vertices
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    //Create a veretex array object to store our svertex attribute configurations.
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Bind buffer to GL_ARRAY
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //copy our data to buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //create and compile our shaders
    ShaderObject *vertexShader, *fragmentShader;
    ShaderProgramObject myShaderProgram;
    if (!myShaderProgram.addShader(GL_VERTEX_SHADER, "shaders/vertex.glsl"))
        goto cleanup;
    if (!myShaderProgram.addShader(GL_FRAGMENT_SHADER, "shaders/fragment.glsl"))
        goto cleanup;
    if (!myShaderProgram.link())
        goto cleanup;
    myShaderProgram.cleanupShaders();
    myShaderProgram.useProgram();

    //Vertex attribute setup

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //perform actions on input
        processInput(window);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Draw our triangle
            myShaderProgram.useProgram();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

cleanup:
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
    static bool spaceHeld = false;
    // set close intent if ESCAPE is pressed, nice.
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        std::cout << "ESCAPE KEY PRESSED!" << std::endl;
        glfwSetWindowShouldClose(window, true);
    }
}

void init_window(GLFWwindow **window)
{
    std::cout << "Initializing GLFW" << std::endl;
    // Initialize and configure GLFW
    if (!glfwInit())
    {
        std::cout << "GLFW INIT Failed" << std::endl;
        exit(-1);
    }
    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    *window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create window!" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(*window);
    // set callback to resize our GL framebuffer upon window resize
    glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
}
