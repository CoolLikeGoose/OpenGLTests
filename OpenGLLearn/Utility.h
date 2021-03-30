#pragma once

#include <string>
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <iostream>


void CheckShaderStatus(GLuint shader, std::string type);

void CheckProgramStatus(GLuint shaderProg);

void ShowMatrix4(glm::mat4 matrix);

glm::mat4 LookAtRealization(glm::vec3 position, glm::vec3 target, glm::vec3 up);