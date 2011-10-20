#include "include.h"
#include "glfw.h";

namespace cgl
{
	class DECLARE OpenGL
	{
	private:
		void OpenGL::Initialize(int width,int height, int redbits, int greenbits, int bluebits, int alphabits, int depthbits, int stencilbits, bool windowresize);
	public:
		OpenGL::OpenGL(int width,int height, int redbits, int greenbits, int bluebits, int alphabits, int depthbits, int stencilbits, bool windowresize);
		OpenGL::OpenGL(bool fullscreen, bool windowresize );
		OpenGL::OpenGL(bool fullscreen, int redbits, int greenbits, int bluebits, int alphabits, int depthbits, int stencilbits, bool windowresize);
		void OnExit(GLFWwindowclosefun function);
		void ExitGLFW();
	};
}