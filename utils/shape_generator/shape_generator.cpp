#include "shape_generator.hpp"
#include <iostream>

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