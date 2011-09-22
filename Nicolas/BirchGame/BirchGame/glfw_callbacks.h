#ifndef _GLFW_CALLBACKS_H
#define _GLFW_CALLBACKS_H
#include "GL/glfw.h"

void	GLFWCALL Size( int width, int height );
int		GLFWCALL CloseWindow( void );
void	GLFWCALL Keyboard( int key, int action );
void	GLFWCALL Text( int character, int action );
void	GLFWCALL MouseButton( int button, int action );
void	GLFWCALL MousePosition( int x, int y );

#endif