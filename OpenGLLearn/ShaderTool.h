#pragma once

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const GLchar* GetShader(string fileName);

string LoadShaderFromFile(string filename);

void CheckShaderStatus(GLuint shader);

void CheckProgramStatus(GLuint shaderProg);