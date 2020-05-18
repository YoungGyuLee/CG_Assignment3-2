#pragma once

#include <GL/glew.h> 
#include <GL/freeglut.h> 
#include <iostream>


class CShaderLoader
{
private:
	std::string readShader(const char* filename);
	GLuint createShader(GLenum shaderType, std::string source, const char* shaderName);
public:
	CShaderLoader(void);
	~CShaderLoader(void);
	GLuint createProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename);
};


