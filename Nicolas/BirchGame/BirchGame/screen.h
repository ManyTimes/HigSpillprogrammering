#ifndef SCREEN_H
#define SCREEN_H
#include "shader_base.h"

class Screen : public Shader_base {

	GLint		screen_texture;
public:
	Screen();
	~Screen();
};

#endif