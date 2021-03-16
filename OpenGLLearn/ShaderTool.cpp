#include "ShaderTool.h"

// TODO: delete this or fix
const GLchar* GetShader(string fileName)
{
    string shaderSourceRaw = LoadShaderFromFile(fileName);
    const char* shaderSource = shaderSourceRaw.c_str();

    return shaderSource;
}

string LoadShaderFromFile(string fileName)
{
    ifstream file(fileName, ios::in);
    string content;
    if (file.good())
    {
        stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();
    }
    return content;
}

void CheckShaderStatus(GLuint shader)
{
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void CheckProgramStatus(GLuint shaderProg)
{
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProg, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}