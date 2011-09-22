#include "include.h"
#include "SDL.h"
#include "SDL_thread.h"
#include "SDL_net.h"
#include "glfw.h"

namespace cgl
{
	DECLARE int s2i(std::string value);
	DECLARE std::string i2s(int value);
	DECLARE void Error(std::string message);
	DECLARE void Cout(std::string message);
	DECLARE void Cout(std::string message, std::string message2);
	DECLARE void CoutIP(Uint8* IPaddress);
	DECLARE std::string GetIP(Uint8* IPaddress);
	DECLARE void ExitGLFW();
	DECLARE void InitGLFW(bool fullscreen, bool windowresize );
	DECLARE void InitGLFW(bool fullscreen, int redbits, int greenbits, int bluebits, int alphabits, int depthbits, int stencilbits, bool windowresize);
	DECLARE void InitGLFW(int width,int height, int redbits, int greenbits, int bluebits, int alphabits, int depthbits, int stencilbits, bool windowresize);
	DECLARE void OnExit(GLFWwindowclosefun function);
	DECLARE int GetArrayLength(int inputarray[]);
	DECLARE int GetArrayLength(char inputarray[]);
	DECLARE int GetArrayLength(std::string inputarray[]);
}