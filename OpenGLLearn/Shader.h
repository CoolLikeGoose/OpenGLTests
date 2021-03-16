#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
	GLuint Program;
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void Use();
};

#endif
