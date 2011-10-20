#include "glfw_callbacks.h"
#include "common.h"
#include <iostream>

using namespace std;

bool keys[KEY_MAX] = { 0 };				// Keys

/*
==================
void GLFWCALL Size
	Called upon size of window changing
	Callback for glfwSetWindowSizeCallback()
Args
	int width	width of screen
	int height	height of screen
==================
*/
void GLFWCALL Size( int width, int height )
{
	glViewport(0, 0, width, height);
}


/*
==================
void GLFWCALL CloseWindow
	Called upon window closing
	Callback for glfwSetWindowCloseCallback()
==================
*/
int GLFWCALL CloseWindow( void )
{
	Running = false;									// Turn off the program.
	return GL_TRUE;										// Return GL_TRUE to close window.
}


/*
==================
void GLFWCALL Keyboard
	Called upon special key events.
	Callback for glfwSetKeyCallback()
Args
	int key				key code, glfw.h line 196 to 268
	int action			is either GLFW_PRESS or GLFW_RELEASE.
==================
*/
void GLFWCALL Keyboard( int key, int action )
{
	switch (key) {
		case 'A' : keys[KEY_LEFT] = action == GLFW_PRESS ? true : false; break;
		case 'D' : keys[KEY_RIGHT] = action == GLFW_PRESS ? true : false; break;
		case 'S' : keys[KEY_BACK] = action == GLFW_PRESS ? true : false; break;
		case 'W' : keys[KEY_FORWARD] = action == GLFW_PRESS ? true : false; break;
		case ' ' : keys[KEY_UP] = action == GLFW_PRESS ? true : false; break;
		case 'C' : keys[KEY_DOWN] = action == GLFW_PRESS ? true : false; break;
		case GLFW_KEY_ESC : { CloseWindow(); glfwCloseWindow(); } break;
		case GLFW_KEY_KP_ADD : keys[KEY_PLUS] = action == GLFW_PRESS ? true : false; break;
		case GLFW_KEY_KP_SUBTRACT : keys[KEY_MINUS] = action == GLFW_PRESS ? true : false; break;
	}
}

/*
==================
void GLFWCALL Text
	Called upon text based keyboard events. 
	Callback for glfwSetCharCallback()
Args
	int character		is a unicode(ISO 10646) character
	int action			is either GLFW_PRESS or GLFW_RELEASE.
==================
*/
void GLFWCALL Text( int character, int action )			
{
	if(/*character == 'G' &&*/ action == GLFW_RELEASE)
	{
		CloseWindow();
		glfwCloseWindow();
	}
}

/*
==================
void GLFWCALL MouseButton
	Called upon mousebutton pressed or released. 
	Callback for glfwSetMouseButtonCallback()
Args
	int button			is a unicode(ISO 10646) character
	int action			is either GLFW_PRESS or GLFW_RELEASE.
==================
*/
void GLFWCALL MouseButton( int button, int action )
{

}

/*
==================
void GLFWCALL MousePosition
	Called upon mouse position changing. 
	Callback for glfwSetMousePosCallback()
Args
	int x	x position on screen
	int y	y position on screen
==================
*/
void GLFWCALL MousePosition( int x, int y )
{
	static bool first = true;							// First time mouse enters screen.
	static int old_x, old_y;							// The previous frame mouse positions.
	int pos_x, pos_y;

//	short pos_x = glutGet(GLUT_WINDOW_WIDTH)/2;			// Might change if we resize the window.
//  short pos_y = glutGet(GLUT_WINDOW_HEIGHT)/2;		// Should make them global and move this code to the reshape function.
														// But this works for now, just not very nicely done.

	glfwGetWindowSize( &pos_x, &pos_y);
	pos_x /= 2;
	pos_y /= 2;

/*	if(!window_state)									// Checks if window is active.
	{
		first = true;									// If it isn't, treat next time as first time to center mouse.
		return;
	}*/

	if(first)											// First time, center the mouse.
	{
		//SetCursorPos(pos_x + glutGet(GLUT_WINDOW_X), pos_y + glutGet(GLUT_WINDOW_Y));
		glfwSetMousePos(pos_x,pos_y);
		old_x = pos_x;
		old_y = pos_y;
		first = false;
		return;
	}

	// Only setting the mouse to the middle if it goes too near edges.
	// Gave smoother result.

	if((x-old_x) != 0)
		camera.yaw_axis((old_x-x)/20.0f, Vector3(0,1,0));	// yaw rotation, but around a fixed up vector.
	if((y-old_y) != 0)
		camera.pitch((old_y-y)/20.0f);			// Pitch.

	if(x != old_x || y != old_y)
	{
		glfwSetMousePos(pos_x,pos_y);
        x = old_x=pos_x;
        y = old_y=pos_y;
	}

	old_x = x;
	old_y = y;
}