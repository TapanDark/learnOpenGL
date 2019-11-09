#ifndef OOGL_SHAPE_PRIMITIVE
#define OOGL_SHAPE_PRIMITIVE

#include <glad/glad.h>
#include "vertex.hpp"
#include <vector>

struct Shape
{
private:
    std::vector<Vertex> vertices;
    // GLuint numVertices;
    std::vector<GLushort> indices;
    // GLuint numIndices;

public:
    // Shape() : vertices(NULL), indices(NULL) {}
    GLsizeiptr vertexBufferSize() const
    {
        return vertices.size() * sizeof(Vertex);
    }
    GLsizeiptr indexBufferSize() const
    {
        return indices.size() * sizeof(GLushort);
    }
    void addVertices(Vertex *newVertices, int count)
    {
        std::copy(newVertices, newVertices + count, std::back_inserter(vertices));
    }

    void addIndices(GLushort *newIndices, int count)
    {
        std::copy(newIndices, newIndices + count, std::back_inserter(indices));
    }

    Vertex *getVertices()
    {
        return &vertices[0];
    }

    GLushort *getIndices()
    {
        return &indices[0];
    }

    void clear()
    {
        vertices.clear();
        indices.clear();
    }

    ~Shape()
    {
        clear();
    }
};

#endif