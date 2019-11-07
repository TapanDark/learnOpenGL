#include "shader_util.hpp"
#include <string.h>
#include <fstream>

ShaderObject::ShaderObject(GLenum type, const char *filename) : shaderType(type), filename(filename)
{
    shaderObject = glCreateShader(shaderType);
    if (type == GL_VERTEX_SHADER)
        shaderTypeStr = "VERTEX";
    else if (type == GL_FRAGMENT_SHADER)
        shaderTypeStr = "FRAGMENT";
    else
    {
        std::cout << "UNKNOWN SHADER TYPE! SHADER COMPILATION MAY FAIL";
        shaderTypeStr = "UNKNOWN";
    }
    compileShader(shaderObject, filename, shaderTypeStr);
}

ShaderObject::~ShaderObject()
{
    glDeleteShader(shaderObject);
}

void ShaderObject::compileShader(unsigned int shaderObject, const char *filename, const char *shaderTypeStr)
{
    std::string shaderCodeString;
    const GLchar *shaderCode[1];

    shaderCodeString = ShaderObject::readShaderCode(filename);
    shaderCode[0] = shaderCodeString.c_str();

    glShaderSource(shaderObject, 1, shaderCode, NULL);
    glCompileShader(shaderObject);
}

std::string ShaderObject::readShaderCode(const char *filename)
{
    std::fstream shaderFile(filename);
    if (!shaderFile.good())
    {
        std::cout << "Shader file failed to open : " << filename;
        exit(1);
    }
    std::string out = std::string(
        std::istreambuf_iterator<char>(shaderFile),
        std::istreambuf_iterator<char>());
    return out;
}

unsigned ShaderObject::getGLShaderObject()
{
    return shaderObject;
}

bool ShaderObject::isGood()
{
    int success;
    char infoLog[512];
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << shaderTypeStr << "::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        return false;
    }
    return true;
}