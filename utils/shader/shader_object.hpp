#ifndef LOGL_SHADER_UTILS
#define LOGL_SHADER_UTILS

#include <glad/glad.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <iostream>

class ShaderObject
{
private:
    GLenum shaderType;
    const char *shaderTypeStr;
    const char *filename;
    unsigned int shaderObject;
    static void compileShader(unsigned int shaderObject, const char *filename, const char *shaderTypeStr);
    static std::string readShaderCode(const char *filename);

public:
    ShaderObject(GLenum type, const char *filename);
    ~ShaderObject();
    unsigned getGLShaderObject();
    bool isGood();
};

#endif