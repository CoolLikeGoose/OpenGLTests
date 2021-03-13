#pragma once

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <fstream>

using namespace std;

const char* LoadShaderFromFile(string filename);

void CheckShaderStatus(GLuint shader);

void CheckProgramStatus(GLuint shaderProg);