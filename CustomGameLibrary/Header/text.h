#ifndef _TEXT_H
#define _TEXT_H

#include "include.h"
#include "includegl.h"
#include "function.h"

namespace cgl
{
	class DECLARE Text
	{
	private:
		int screenWidth;
		int screenHeight;
	public:
		int x;
		int y;
		float RGB[3];
		void* font;
		Text::Text();
		Text::Text(int screenWidth, int screenHeight);
		void Text::Initialize(int screenWidth, int screenHeight);
		void Text::SetFontSize(int size);
		void Text::Draw(char* text, int textX, int textY);
		void Text::Draw(char* text);
	};
}

#endif