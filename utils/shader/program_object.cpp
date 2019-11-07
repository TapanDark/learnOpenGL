#include "program_object.hpp"

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
