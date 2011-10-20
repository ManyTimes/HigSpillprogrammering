#include "screen.h"


Screen::Screen()
{
	SetShader("Shaders/Screen", 0);

	glUseProgram(GetProgram());
	screen_texture = glGetUniformLocation(GetProgram(), "Screen_Texture");

	glUniform1i(screen_texture, 0);

	glUseProgram(0);
}

Screen::~Screen()
{
}