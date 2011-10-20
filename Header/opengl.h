#ifndef _OPENGL_H
#define _OPENGL_H

#include "include.h"			//Includes standard stuff, string, math, etc.
#include "function.h"
#include "includegl.h";
#include "camera.h"
#include "keyboard.h"
#include "textureTGA.h"

namespace cgl
{
	class DECLARE OpenGL
	{
	private:
		enum GLCALLBACK { WINDOWCLOSE, KEYBOARD, MOUSEBUTTON, MOUSEMOVEMENT };
		Keyboard* keyboard;
		int width;
		int height;
		void GLFWCALL OpenGL::KeyboardCallback(int key, int action);
		void OpenGL::InitializeCallback();
	public:
		OpenGL::OpenGL();
		OpenGL::OpenGL(int width,int height, int redbits, int greenbits, int bluebits, int alphabits, int depthbits, int stencilbits, bool windowresize, bool fullscreen);
		void OpenGL::Initialize(std::string windowTitle, bool enableLighting, bool enableCullFace, bool enableDepthTest, bool enable2D, bool enableLineSmoothing);
		void OpenGL::SetWindowTitle(std::string title);
		void OpenGL::Callback(GLCALLBACK functionType, void (*function)(int, int));
		void OpenGL::Callback(GLCALLBACK functionType, int (*function)(void));
		void OpenGL::EnableVerticalSync(bool value);
		void OpenGL::EnableFog(bool value);
		void OpenGL::Enable(int token);
		void OpenGL::Disable(int token);
		void OpenGL::Translatef(float x, float y, float z);
		void OpenGL::CreateViewport3D(int viewWidth, int viewHeight, int startPositionX, int startPositionY, float zNear, float zFar);
		void OpenGL::CreateViewport2D(int viewWidth, int viewHeight, int startPositionX, int startPositionY, float zNear, float zFar);
		void OpenGL::CreateViewPort(bool dimenion_3D, int viewWidth, int viewHeight, int startPositionX, int startPositionY, float zNear, float zFar);
		void OpenGL::StartDraw();						//Clears buffer bit, loads identity
		void OpenGL::DrawImage(GLuint textureID, float posX, float posY, int width, int height);
		void OpenGL::EndDraw();
		void OpenGL::Exit();
	};
}

#endif