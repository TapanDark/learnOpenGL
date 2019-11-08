#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string.h>
#include <glm/glm.hpp>
#include <shader/program_object.hpp>
#include <window/window_utils.hpp>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int main(int argc, char *argv[])
{
    MyWindow windowObj(WIDTH, HEIGHT, "3d Demo");

    float vertices[] = {
        -0.5f, -0.5f,     //triangle left
        1.0f, 0.0f, 0.0f, //red
        0.5f, -0.5f,      //triangle right
        0.0f, 1.0f, 0.0f, //green
        0.0f, 0.5f,       //triangle top
        0.0f, 0.0f, 1.0f  //blue
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

    //Vertex attribute setup
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(sizeof(float) * 2));

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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Draw our triangle
        myShaderProgram.useProgram();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Actuall swap buffers so our new image is visible
        windowObj.draw();
        //perform actions on input
        if (windowObj.isKeyPressed(GLFW_KEY_ESCAPE))
            windowObj.setClose();
    }

cleanup:
    std::cout << "Goodbye world!" << std::endl;
    return 0;
}