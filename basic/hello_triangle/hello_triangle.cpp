#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unistd.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

//Callback methods for window resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//Method to process input, if any.
void processInput(GLFWwindow *window);

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

enum displayMode
{
    SOLID = 0,
    WIREFRAME,
    NUM_MODES
};

enum displayShape
{
    TRIANGLE = 0,
    RECTANGLE,
    DOUBLE_TRIANGLE,
    TRIPLE_TRIANGLE,
    COLORED_TRIANGLES,
    NUM_SHAPES
};

displayMode seletectedMode = SOLID;
displayShape selectedShape = TRIANGLE;

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
    "}\n";

int main(void)
{
    GLFWwindow *window;

    //declare variables for storing shader compile process info
    int success;
    char infoLog[512];

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

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Define the triangle that we want to draw:
    //                     * 0,0.5)
    //                    /|\
    //                   / | \
    //                  /  |  \
    //                 /   |   \
    //   _____________/____|____\___________
    //               /     |     \
    //              /      |      \
    //             *_______|_______*
    //       (-0.5,-0.5)   |  (0.5,-0.5)
    //                     |
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.05,
        0.0f, 0.5f, 0.0f};

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

    //create and compile our vertext shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Moment of truth:
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        goto cleanup;
    }

    // Create and compile our fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        goto cleanup;
    }

    //Create our shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    //attach our shaders and link
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //Check for errors:
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glad_glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n"
                  << infoLog << std::endl;
        goto cleanup;
    }

    //Use our program
    glUseProgram(shaderProgram);

    //delete our shaders.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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
        switch(selectedShape)
        {
            case TRIANGLE:
                glUseProgram(shaderProgram);
                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 3);
                break;
            case RECTANGLE:
                break;
            case DOUBLE_TRIANGLE:
                break;
            case TRIPLE_TRIANGLE:
                break;
            case COLORED_TRIANGLES:
                break;
            default:
                break;
        }
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
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spaceHeld)
    {
        spaceHeld = true;
        std::cout << "SPACE KEY PRESSED!" << std::endl;
        selectedShape = static_cast<displayShape>((selectedShape + 1) % NUM_SHAPES);
    }
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE && spaceHeld)
        spaceHeld=false;
}