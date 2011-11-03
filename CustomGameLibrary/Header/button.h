#ifndef _BUTTON_H
#define _BUTTON_H

#include "include.h"
#include "includegl.h"
#include "image2d.h"
#include "mouse.h"

namespace cgl
{
	class DECLARE Button
	{
	private:
		int screenWidth;
		int screenHeight;
		int maxcursorY;				//Values calculated, because of opengl draws as Y = 0, is bottom
		int mincursorY;				//but mouse Y = 0 is top of screen, reversed.
		int width;
		int height;
		int minY;
		int maxY;
		int maxX;
		int minX;
		int positionX;
		int positionY;
		GLuint textureID;
		GLuint buttonClickedTextureID;
		cgl::Mouse* mouse;
	public:
		bool leftclick;		//Button activates if left click with mouse
		bool rightclick;	//Button activates if right click with mouse
		Button::Button(cgl::Mouse* mouseObject, int screenWidth, int screenHeight, int viewportWidth, int viewportHeight, int viewportStartPositionX, int viewportStartPositionY, int buttonPositionX, int buttonPositionY);
		//Button::Button(cgl::Mouse* mouseObject, int viewportWidth, int viewportHeight, int viewportStartX, int viewportStartY, int buttonPositionX, int buttonPositionY);
		void Button::SetSize(int width, int height);
		void Button::SetTexture(GLuint textureID, GLuint buttonClickedTextureID);
		//void Button::DrawClicked(GLuint textureID);
		void Button::EndDrawButtons();
		void Button::BeginDrawButtons();
		void Button::Draw();
		bool Button::isPressed();
	};
}

#endif