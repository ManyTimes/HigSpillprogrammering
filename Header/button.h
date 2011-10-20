#ifndef _BUTTON_H
#define _BUTTON_H

#include "include.h"
#include "includegl.h"
#include "image2d.h"

namespace cgl
{
	class DECLARE Button
	{
	private:
		int width;
		int height;
		std::string text;
		GLuint backgroundImage;	//Background image, type "image2d.h"->ID
	public:
		bool leftclick;		//Button activates if left click with mouse
		bool rightclick;	//Button activates if right click with mouse
		Button::Button(std::string text, int width, int height);
		void Button::SetBackground(GLuint backgroundImage);
		void Button::SetBackground(Image2D backgroundImage);
		void Button::Draw();
		void Button::Draw(GLuint backgroundImage);
	};
}

#endif