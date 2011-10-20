#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <windows.h>										// Standard windows header
#include <stdio.h>											// Standard I/O header 
#include "include.h"
#include "includegl.h"										// Header for OpenGL32 library
#include "function.h"

namespace cgl
{
	class DECLARE TextureTGA
	{
	public:
		GLubyte	* imageData;									// Image Data (Up To 32 Bits)
		GLuint	bpp;											// Image Color Depth In Bits Per Pixel
		GLuint	width;											// Image Width
		GLuint	height;											// Image Height
		GLuint	textureID;										// Texture ID Used To Select A Texture
		GLuint	type;											// Image Type (GL_RGB, GL_RGBA)
		TextureTGA::TextureTGA();
		TextureTGA::~TextureTGA();
		void TextureTGA::Load(char* filename);
	};

}

#endif