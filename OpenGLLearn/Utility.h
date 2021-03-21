#pragma once

#include <string>
#include <GL/glew.h>
#include <iostream>

using namespace std;

void CheckShaderStatus(GLuint shader, std::string type);

void CheckProgramStatus(GLuint shaderProg);