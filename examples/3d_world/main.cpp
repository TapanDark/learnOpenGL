#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <unistd.h>
#include <oogl/oogl.hpp>
#include <shape_generator/shape_generator.hpp>
#include <window/window_utils.hpp>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int curr_width = WIDTH;
int curr_height = HEIGHT;

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // match our GL viewport size to window dimensions.
    glViewport(0, 0, width, height);
    curr_width = width;
    curr_height = height;
}

int main(int argc, char *argv[])
{
    MyWindow windowObj(WIDTH, HEIGHT, "3d Demo");
    windowObj.setFramebufferResizeCallback(framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw std::exception();
    }
    Shape cube = ShapeGenerator::makeCube();

    //enable depth test
    glEnable(GL_DEPTH_TEST);

    //Create a vertex buffer to store our vertices
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    //create a element buffer object to store element indices
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    //Create a veretex array object to store our svertex attribute configurations.
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Bind buffer to GL_ARRAY
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //copy our data to buffer
    glBufferData(GL_ARRAY_BUFFER, cube.vertexBufferSize(), cube.getVertices(), GL_STATIC_DRAW);

    //Bind element buffer to GL_ARRAY
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //copy our data to buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.indexBufferSize(), cube.getIndices(), GL_STATIC_DRAW);

    //Vertex attribute setup
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(sizeof(float) * 3));

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
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw our triangle
        myShaderProgram.useProgram();
        glBindVertexArray(VAO);

        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -3.0f));
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(54.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotation2Matrix = glm::rotate(glm::mat4(1.0f), glm::radians(54.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), ((float)curr_width / (float)curr_height), 0.1f, 10.0f);

        glm::mat4 fullTransformMatrix = projectionMatrix * translationMatrix * rotationMatrix * rotation2Matrix;

        myShaderProgram.SetUniform(myShaderProgram.GetUniform("fullTransformMatrix"), &fullTransformMatrix, 1);

        glDrawElements(GL_TRIANGLES, cube.getNumVertices(), GL_UNSIGNED_SHORT, 0);

        translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -3.0f));
        rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-54.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotation2Matrix = glm::rotate(glm::mat4(1.0f), glm::radians(-54.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        projectionMatrix = glm::perspective(glm::radians(60.0f), ((float)curr_width / (float)curr_height), 0.1f, 10.0f);

        fullTransformMatrix = projectionMatrix * translationMatrix * rotationMatrix * rotation2Matrix;

        myShaderProgram.SetUniform(myShaderProgram.GetUniform("fullTransformMatrix"), &fullTransformMatrix, 1);

        glDrawElements(GL_TRIANGLES, cube.getNumVertices(), GL_UNSIGNED_SHORT, 0);

        //Actuall swap buffers so our new image is visible
        windowObj.refresh();
        //perform actions on input
        if (windowObj.isKeyPressed(GLFW_KEY_ESCAPE))
            windowObj.setClose();

        if (windowObj.isKeyPressed(GLFW_KEY_0))
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        if (windowObj.isKeyPressed(GLFW_KEY_1))
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

cleanup:
    std::cout << "Goodbye world!" << std::endl;
    return 0;
}