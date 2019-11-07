#include <glad/glad.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <iostream>
#include "shader_object.hpp"
#include <vector>

class ShaderProgramObject
{
private:
    unsigned int programObject;
    std::vector<ShaderObject *> shaderList;

public:
    ShaderProgramObject();
    ~ShaderProgramObject();
    bool addShader(GLenum type, const char *filename);
    bool link();
    void useProgram();
    void cleanupShaders();
};