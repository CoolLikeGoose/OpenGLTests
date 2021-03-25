#include "Utility.h"

void CheckShaderStatus(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
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

void ShowMatrix4(glm::mat4 matrix)
{
    float arr[16];

    const float* source = (const float*)glm::value_ptr(matrix);

    for (int i = 0; i < 16; i++)
        arr[i] = source[i];

    for (int x = 0; x < 4; x++)
    {
        std::cout << '\n' << '[';
        for (int y = 0; y < 3; y++)
        {
            std::cout << source[x * y] << '\t';
        }
        std::cout << source[x * 3];
        std::cout << ']' << '\n' << std::endl;
    }
}