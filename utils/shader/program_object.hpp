#ifndef LOGL_PROGRAM_UTILS
#define LOGL_PROGRAM_UTILS

#include <glad/glad.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <iostream>
#include "shader_object.hpp"
#include <vector>
#include <glm/glm.hpp>

using glm::mat3;
using glm::mat4;
using glm::vec2;
using glm::vec3;
using glm::vec4;

typedef GLint Uniform;

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
    Uniform GetUniform(const std::string &name);

    void SetUniform(const Uniform &uniform, int value);
    void SetUniform(const Uniform &uniform, float value);
    void SetUniform(const Uniform &uniform, const vec2 &value);
    void SetUniform(const Uniform &uniform, const vec3 &value);
    void SetUniform(const Uniform &uniform, const vec4 &value);
    void SetUniform(const Uniform &uniform, const float *values, uint count);
    void SetUniform(const Uniform &uniform, const vec2 *values, uint count);
    void SetUniform(const Uniform &uniform, const vec3 *values, uint count);
    void SetUniform(const Uniform &uniform, const vec4 *values, uint count);
    // void SetUniform(const Uniform &uniform, const mat3 &value);
    // void SetUniform(const Uniform &uniform, const mat4 &value);
};

#endif