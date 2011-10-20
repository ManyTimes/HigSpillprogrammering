#include "../Header/opengl.h"

namespace cgl
{
	//************CONSTRUCTORS************
	void OpenGL::Initialize(int width,int height, int redbits, int greenbits, int bluebits, int alphabits, int depthbits, int stencilbits, bool windowresize)
	{
		glfwInit();
		if(windowresize == true)
		{
			glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, 1);
		}
		if(glfwInit() != 1)
		{
			exit(1);
		}
		if(height == 0 && width == 0)
		{
			if(glfwOpenWindow(0,0, redbits, greenbits, bluebits, alphabits, depthbits, stencilbits, GLFW_FULLSCREEN) != 1)
			{
				exit(1);
			}
		}
		else
		{
			if(width < 1)
			{
				width = 800;
			}
			if(height < 1)
			{
				height = 600;
			}
			if(glfwOpenWindow(width, height, redbits, greenbits, bluebits, alphabits, depthbits, stencilbits, GLFW_WINDOW) != 1)
			{
				exit(1);
			}
		}
		glfwEnable(GLFW_MOUSE_CURSOR);
		glfwEnable(GLFW_AUTO_POLL_EVENTS);
	}
	OpenGL::OpenGL(int width,int height, int redbits, int greenbits, int bluebits, int alphabits, int depthbits, int stencilbits, bool windowresize)
	{
		Initialize(0,0, redbits, greenbits, bluebits, alphabits, depthbits, stencilbits, windowresize);
	}
	OpenGL::OpenGL(bool fullscreen, bool windowresize )
	{
		if(fullscreen == true)
		{
			Initialize(0,0, 8, 8, 8, 0, 0, 0, windowresize);
		}
		else
		{
			Initialize(1024,786, 8, 8, 8, 0, 0, 0, windowresize);
		}
	}
	OpenGL::OpenGL(bool fullscreen, int redbits, int greenbits, int bluebits, int alphabits, int depthbits, int stencilbits, bool windowresize)
	{
		Initialize(0,0, redbits, greenbits, bluebits, alphabits, depthbits, stencilbits, windowresize);
	}

	//************FUNCTIONS************
	void OpenGL::OnExit(GLFWwindowclosefun function)
	{
		glfwSetWindowCloseCallback(function);
	}
	void OpenGL::ExitGLFW()
	{
		glfwTerminate();
		glfwCloseWindow();
	}
}