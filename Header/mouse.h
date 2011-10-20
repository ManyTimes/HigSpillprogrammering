#ifndef _MOUSE_H
#define _MOUSE_H

#include "include.h"
#include "includegl.h"
#include "image.h"
#include <map>
#include <iostream>
#include "Image2D.h"


namespace cgl
{
	class DECLARE Mouse
	{
	private:
		int screenWidth;
		int screenHeight;
		bool outsideScreen;
		bool enableCustomMouseCursor;											//Drawing a custom picture as mouse, or not
		int cursorx;
		int cursory;
		std::map<int, bool> mousebutton;										//From 0 - 2. Left, right, middle button
		std::map<std::string, int> conversion;									//Maps string to integer
		static Mouse* instance;
		static void GLFWCALL Mouse::ButtonCallback(int button, int action);		//GL Callback
		static void GLFWCALL Mouse::PositionCallback(int x, int y);				//GL Callback
		Mouse::Mouse();
		/*{
			//Button 0 : Left button
			//Button 1 : Right button
			//Button 2 : Middle button
			//Action 1 : Press
			//Action 0 : Release
			cout  << "Mouse btn: " << button << " Act: " << action << endl;
		}*/
		void Mouse::CursorFramed();
	public:		
		bool enableMouseFrame;													//Enabling a limit of mousemovement within this window or not
		static Mouse* GetInstance(int screenWidth, int screenHeight);
		void Mouse::EnableMouseFrame(bool enable);
		int Mouse::GetCursorPositionY();
		int Mouse::GetCursorPositionX();
		void Mouse::SetCursorPosition(int x, int y);
		void Mouse::ShowCustomCursor(bool enable);
		void Mouse::ShowWindowsCursor(bool enable);
		bool Mouse::isButtonPressed(std::string buttonPressed);
		bool Mouse::isButtonPressed(int buttonPressed);
		void Mouse::Draw(GLuint textureID, int textureWidth, int textureHeight);
		void Mouse::Draw(GLuint textureID);
		void Mouse::Draw(Image2D& mouseImage, int textureWidth, int textureHeight);
	};
}

#endif

