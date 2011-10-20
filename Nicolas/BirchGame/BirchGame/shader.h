#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>

class Shader
{
	GLuint vertex, fragment, geometry;
	GLuint program;

	int printOglError(char *file, int line);
	void printShaderInfoLog(unsigned int obj);
	void printProgramInfoLog(unsigned int obj);
	char *textFileRead(char *fn); 
public :
	Shader();
	~Shader();
	GLuint setShader(char *sp);
};

#endif