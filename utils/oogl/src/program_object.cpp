#include "oogl/program_object.hpp"

ShaderProgramObject::ShaderProgramObject()
{
    programObject = glCreateProgram();
}
ShaderProgramObject::~ShaderProgramObject()
{
}
bool ShaderProgramObject::addShader(GLenum type, const char *filename)
{
    ShaderObject *shaderObjectPtr = new ShaderObject(type, filename);
    if (!shaderObjectPtr->isGood())
        return false;
    glAttachShader(programObject, shaderObjectPtr->getGLShaderObject());
    shaderList.push_back(shaderObjectPtr);
    return true;
}
bool ShaderProgramObject::link()
{
    int success;
    char infoLog[512];
    glLinkProgram(programObject);
    //Check for errors:
    glGetProgramiv(programObject, GL_LINK_STATUS, &success);
    if (!success)
    {
        glad_glGetProgramInfoLog(programObject, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n"
                  << infoLog << std::endl;
        return false;
    }
    return true;
}

void ShaderProgramObject::useProgram()
{
    glUseProgram(programObject);
}

void ShaderProgramObject::cleanupShaders()
{
    shaderList.clear();
}

Uniform ShaderProgramObject::GetUniform(const std::string &name)
{
    Uniform location = glGetUniformLocation(programObject, name.c_str());
    if (location < 0)
        std::cout << "WARNING: Unable to get uniform location for " << name << std::endl;

    return location;
}

void ShaderProgramObject::SetUniform(const Uniform &uniform, int value)
{
    useProgram();
    glUniform1i(uniform, value);
}
void ShaderProgramObject::SetUniform(const Uniform &uniform, float value)
{
    useProgram();
    glUniform1f(uniform, value);
}
void ShaderProgramObject::SetUniform(const Uniform &uniform, const vec2 &value)
{
    useProgram();
    glUniform2f(uniform, value.x, value.y);
}
void ShaderProgramObject::SetUniform(const Uniform &uniform, const vec3 &value)
{
    useProgram();
    glUniform3f(uniform, value.x, value.y, value.z);
}

void ShaderProgramObject::SetUniform(const Uniform &uniform, const vec4 &value)
{
    useProgram();
    glUniform4f(uniform, value.x, value.y, value.z, value.w);
}
void ShaderProgramObject::SetUniform(const Uniform &uniform, const float *values, unsigned int count)
{
    useProgram();
    glUniform1fv(uniform, count, values);
}
void ShaderProgramObject::SetUniform(const Uniform &uniform, const vec2 *values, unsigned int count)
{
    useProgram();
    glUniform2fv(uniform, count, (GLfloat *)values);
}

void ShaderProgramObject::SetUniform(const Uniform &uniform, const vec3 *values, unsigned int count)
{
    useProgram();
    glUniform3fv(uniform, count, (GLfloat *)values);
}

void ShaderProgramObject::SetUniform(const Uniform &uniform, const vec4 *values, unsigned int count)
{
    useProgram();
    glUniform4fv(uniform, count, (GLfloat *)values);
}

void ShaderProgramObject::SetUniform(const Uniform &uniform, const mat3 *values, unsigned int count, bool transpose)
{
    useProgram();
    GLboolean gl_normalize = transpose ? GL_TRUE : GL_FALSE;
    glUniformMatrix3fv(uniform, count, gl_normalize, (GLfloat *)values);
}

void ShaderProgramObject::SetUniform(const Uniform &uniform, const mat4 *values, unsigned int count, bool transpose)
{
    useProgram();
    GLboolean gl_normalize = transpose ? GL_TRUE : GL_FALSE;
    glUniformMatrix4fv(uniform, count, gl_normalize, (GLfloat *)values);
}
