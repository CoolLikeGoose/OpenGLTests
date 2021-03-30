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

glm::mat4 LookAtRealization(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
    glm::mat4 LookMatrix(1.0f);

    glm::vec3 camZaxis = glm::normalize(position - target);
    glm::vec3 camXaxis = glm::normalize(glm::cross(up, camZaxis));
    glm::vec3 camYaxis = glm::normalize(glm::cross(camZaxis, camXaxis));

    //column - major
    LookMatrix[0][0] = camXaxis.x;
    LookMatrix[1][0] = camXaxis.y;
    LookMatrix[2][0] = camXaxis.z;

    LookMatrix[0][1] = camYaxis.x;
    LookMatrix[1][1] = camYaxis.y;
    LookMatrix[2][1] = camYaxis.z;

    LookMatrix[0][2] = camZaxis.x;
    LookMatrix[1][2] = camZaxis.y;
    LookMatrix[2][2] = camZaxis.z;

    glm::mat4 AdditionalPosMatrix(1.0f);

    AdditionalPosMatrix[3][0] = -position.x;
    AdditionalPosMatrix[3][1] = -position.y;
    AdditionalPosMatrix[3][2] = -position.z;

    return LookMatrix * AdditionalPosMatrix;
}
