#ifndef SHADER_BASE_H
#define SHADER_BASE_H
#include "GL/glew.h"
#include "shader.h"

class Shader_base {
	// Shader details
	GLuint			drawProgram;
	Shader			*drawShader;
//	ShaderConfig	*shaderConfig;

public:
	Shader_base();
	~Shader_base();
	GLuint GetProgram();
	void SetShader(char *shadername, void (*InitShaderConfig)() );

};
#endif