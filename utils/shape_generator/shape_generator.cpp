#include "shape_generator.hpp"

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)

Shape ShapeGenerator::makeTriangle()
{
    Shape shapeObj;
    // shapeObj->clear();
    Vertex triVertices[] = {
        glm::vec3(-0.5f, -0.5f, +0.0f), //triangle left
        glm::vec3(+1.0f, +0.0f, +0.0f), //red

        glm::vec3(+0.5f, -0.5f, +0.0f), //triangle right
        glm::vec3(+0.0f, +1.0f, +0.0f), //green

        glm::vec3(+0.0f, +0.5f, +0.0f), //triangle top
        glm::vec3(+0.0f, +0.0f, +1.0f)  //blue
    };

    GLushort triIndices[] = {0, 1, 2};

    shapeObj.addVertices(triVertices, NUM_ARRAY_ELEMENTS(triVertices));
    shapeObj.addIndices(triIndices, NUM_ARRAY_ELEMENTS(triIndices));
    return shapeObj;
}

Shape ShapeGenerator::makeCube()
{
    Shape shapeObj;
    // shapeObj->clear();
    Vertex cubeVertices[] = {
        //set 1
        glm::vec3(-0.5f, -0.5f, -0.5f), //front bottom left
        glm::vec3(+1.0f, +0.0f, +0.0f), //color

        glm::vec3(+0.5f, -0.5f, -0.5f), //front bottom right
        glm::vec3(+0.0f, +1.0f, +0.0f), //color

        glm::vec3(-0.5f, +0.5f, -0.5f), //front top left
        glm::vec3(+0.0f, +0.0f, +1.0f), //color

        glm::vec3(+0.5f, +0.5f, -0.5f), //front top right
        glm::vec3(+1.0f, +1.0f, +0.0f), //color

        glm::vec3(-0.5f, -0.5f, +0.5f), //rear bottom left
        glm::vec3(+1.0f, +1.0f, +1.0f), //color

        glm::vec3(+0.5f, -0.5f, +0.5f), //rear bottom right
        glm::vec3(+0.0f, +1.0f, +1.0f), //color

        glm::vec3(-0.5f, +0.5f, +0.5f), //rear top left
        glm::vec3(+1.0f, +1.0f, +0.0f), //color

        glm::vec3(+0.5f, +0.5f, +0.5f), //rear top right
        glm::vec3(+0.1f, +0.1f, +0.1f), //color

        //set 2
        glm::vec3(-0.5f, -0.5f, -0.5f), //front bottom left
        glm::vec3(+0.0f, +1.0f, +0.0f), //color

        glm::vec3(+0.5f, -0.5f, -0.5f), //front bottom right
        glm::vec3(+0.0f, +0.0f, +1.0f), //color

        glm::vec3(-0.5f, +0.5f, -0.5f), //front top left
        glm::vec3(+1.0f, +0.0f, +0.0f), //color

        glm::vec3(+0.5f, +0.5f, -0.5f), //front top right
        glm::vec3(+0.0f, +1.0f, +0.3f), //color

        glm::vec3(-0.5f, -0.5f, +0.5f), //rear bottom left
        glm::vec3(+1.0f, +0.0f, +1.0f), //color

        glm::vec3(+0.5f, -0.5f, +0.5f), //rear bottom right
        glm::vec3(+0.0f, +3.0f, +1.0f), //color

        glm::vec3(-0.5f, +0.5f, +0.5f), //rear top left
        glm::vec3(+1.0f, +1.0f, +0.0f), //color

        glm::vec3(+0.5f, +0.5f, +0.5f), //rear top right
        glm::vec3(+1.0f, +1.0f, +1.0f), //color

        //set 3
        glm::vec3(-0.5f, -0.5f, -0.5f), //front bottom left
        glm::vec3(+0.0f, +0.0f, +1.0f), //color

        glm::vec3(+0.5f, -0.5f, -0.5f), //front bottom right
        glm::vec3(+1.0f, +0.0f, +0.0f), //color

        glm::vec3(-0.5f, +0.5f, -0.5f), //front top left
        glm::vec3(+0.0f, +1.0f, +0.0f), //color

        glm::vec3(+0.5f, +0.5f, -0.5f), //front top right
        glm::vec3(+0.6f, +0.2f, +0.8f), //color

        glm::vec3(-0.5f, -0.5f, +0.5f), //rear bottom left
        glm::vec3(+0.2f, +0.8f, +0.6f), //color

        glm::vec3(+0.5f, -0.5f, +0.5f), //rear bottom right
        glm::vec3(+0.8f, +0.2f, +0.6f), //color

        glm::vec3(-0.5f, +0.5f, +0.5f), //rear top left
        glm::vec3(+0.8f, +0.6f, +0.2f), //color

        glm::vec3(+0.5f, +0.5f, +0.5f), //rear top right
        glm::vec3(+0.2f, +0.6f, +0.8f)  //color

    };

    // GLushort cubeIndices[] = {
    //     0, 1, 2, 2, 3, 1, // front
    //     1, 5, 3, 3, 7, 5, // right
    //     5, 4, 7, 7, 6, 4, // rear
    //     4, 0, 6, 6, 2, 0, // left
    //     0, 1, 4, 4, 5, 1, // bottom
    //     2, 3, 6, 6, 7, 3  // top
    // };

    GLushort cubeIndices[] = {
        0, 1, 2, 2, 3, 1,     // front
        9, 5, 11, 11, 7, 5,   // right
        13, 4, 15, 15, 6, 4,    // rear
        12, 0, 14, 14, 10, 0, // left
        0, 17, 20, 20, 21, 17, // bottom
        18, 19, 22, 22, 23, 19  // top
    };

    shapeObj.addVertices(cubeVertices, NUM_ARRAY_ELEMENTS(cubeVertices));
    shapeObj.addIndices(cubeIndices, NUM_ARRAY_ELEMENTS(cubeIndices));
    return shapeObj;
}