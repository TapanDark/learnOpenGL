#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <unistd.h>
#include <oogl/oogl.hpp>
#include <shape_generator/shape_generator.hpp>
#include <window/window_utils.hpp>
#include <camera/camera.hpp>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int curr_width = WIDTH;
int curr_height = HEIGHT;

glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), ((float)curr_width / (float)curr_height), 0.1f, 10.0f);
static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // match our GL viewport size to window dimensions.
    glViewport(0, 0, width, height);
    curr_width = width;
    curr_height = height;
    projectionMatrix = glm::perspective(glm::radians(60.0f), ((float)curr_width / (float)curr_height), 0.1f, 10.0f);
}

//TODO: DIRTY GLOBAL. FIX ME
Camera mainCamera;

static void mouse_move_callback(GLFWwindow *window, double xPos, double yPos)
{
    // std::cout << xPos << "  :  " << yPos << std::endl;
    mainCamera.mouseUpdate(glm::vec2(xPos, yPos));
}

void updateCamera(glm::mat4 projectionMatrix)
{
    glm::mat4 fullTransformationMatrices[] = {
        projectionMatrix * mainCamera.getViewTransformMatrix() *
            glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -3.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(54.0f), glm::vec3(1.0f, 1.0f, 0.0f)),
        projectionMatrix * mainCamera.getViewTransformMatrix() *
            glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -3.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(120.0f), glm::vec3(1.0f, 1.0f, 0.0f))};
    glBufferData(GL_ARRAY_BUFFER, sizeof(fullTransformationMatrices), fullTransformationMatrices, GL_DYNAMIC_DRAW);
}

int main(int argc, char *argv[])
{
    MyWindow windowObj(WIDTH, HEIGHT, "3d Demo");
    windowObj.setFramebufferResizeCallback(framebuffer_size_callback);
    windowObj.setCursorDisabled();
    windowObj.setCursorPosCallback(mouse_move_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw std::exception();
    }
    Shape cube = ShapeGenerator::makeCube();

    //create our transformation matrices:

    //enable depth test
    glEnable(GL_DEPTH_TEST);

    //Create a vertex buffer to store our vertices
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    //create a element buffer object to store element indices
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    //create element buffer to store our transformation matrices
    unsigned int TBO;
    glGenBuffers(1, &TBO);

    //Create a veretex array object to store our vertex attribute configurations.
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //copy our vertex data to buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, cube.vertexBufferSize(), cube.getVertices(), GL_STATIC_DRAW);

    //copy our element data to buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.indexBufferSize(), cube.getIndices(), GL_STATIC_DRAW);

    //Vertex attributes setup
    //position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);

    //vColor attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(sizeof(float) * 3));

    //Allocation buffer for our transformation matrices. We will send for each frame as per camera update.
    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * 2, 0, GL_DYNAMIC_DRAW);

    //transform matrix attribute
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(float) * 0));
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(float) * 4));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(float) * 8));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(float) * 12));
    //setup divisor 1 to use once per render instance
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

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

    /* Loop until the user closes the window */
    while (windowObj.isOpen())
    {
        /* Render here */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw our triangle
        myShaderProgram.useProgram();
        glBindVertexArray(VAO);

        //UGLY UGLY BIND BEFORE SEND DATA. FIX ASAP
        glBindBuffer(GL_ARRAY_BUFFER, TBO);
        updateCamera(projectionMatrix);

        glDrawElementsInstanced(GL_TRIANGLES, cube.getNumVertices(), GL_UNSIGNED_SHORT, 0, 2);

        //Actuall swap buffers so our new image is visible
        windowObj.refresh();

        //perform actions on input
        if (windowObj.isKeyPressed(GLFW_KEY_ESCAPE))
            windowObj.setClose();

        if (windowObj.isKeyPressed(GLFW_KEY_0))
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        if (windowObj.isKeyPressed(GLFW_KEY_1))
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        //Direction Input
        if (windowObj.isKeyPressed(GLFW_KEY_W))
            mainCamera.moveForward();

        if (windowObj.isKeyPressed(GLFW_KEY_S))
            mainCamera.moveBackward();

        if (windowObj.isKeyPressed(GLFW_KEY_A))
            mainCamera.strafeLeft();

        if (windowObj.isKeyPressed(GLFW_KEY_D))
            mainCamera.strafeRight();
    }

cleanup:
    std::cout << "Goodbye world!" << std::endl;
    return 0;
}