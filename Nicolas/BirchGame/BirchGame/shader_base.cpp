#include "shader_base.h"
#include <iostream>

Shader_base::Shader_base()
{

}

Shader_base::~Shader_base()
{ 

}

void Shader_base::SetShader(char *shadername, void (*InitShaderConfig)() )
{
	drawShader = new Shader();
	drawProgram = drawShader->setShader(shadername);

	if(!drawProgram)
	{
		std::cout << "Couldn't find shader " << shadername << std::endl;
		return;
	}
//	InitShaderConfig();


}

GLuint Shader_base::GetProgram() 
{ 
	return drawProgram; 
}