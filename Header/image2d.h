#ifndef _Image2D_H
#define _Image2D_H

#include <windows.h>									// Standard windows header
#include <stdio.h>										// Standard I/O header 
#include "include.h"
#include "includegl.h"										// Header for OpenGL32 library
#include "function.h"
#include "textureTGA.h"
#include "autoarray.h"

namespace cgl
{
	class DECLARE Image2D
	{
	private:
		AUX_RGBImageRec* texture;
		GLuint	temp;								// Temporary Variable
		GLubyte header[12];							// A normal TGA header
		GLubyte uTGAcompare[12];					// Uncompressed TGA Header
		GLubyte cTGAcompare[12];					// Compressed TGA Header
		GLubyte*dataTGA;						// Image Data (Up To 32 Bits)
		char*	dataBMP;								
		GLuint	imageSize;							// Used To Store The Image Size When Setting Aside Ram
		bool Image2D::LoadUncompressedTGA(char *, FILE *);	// Load an Uncompressed file
		bool Image2D::LoadCompressedTGA(char *, FILE *);		// Load a Compressed file
	public:
		GLubyte headerTGA[6];						//First 6 bytes from header
		GLuint	bytesPerPixel;						//Number of bytes used per pixel in this TGA file
		GLuint	type;	
		GLuint	height;								//Height of Image
		GLuint	width;								//Width ofImage
		GLuint	bpp;								//Bits Per Pixel
		GLuint  ID;									//Same as above, preferences
		Image2D::Image2D();
		Image2D::~Image2D();
		bool Image2D::LoadTGA(char* filename);
		bool Image2D::LoadBMP(char* filename);
		bool Image2D::LoadBMP2(const char* filename);
		void Image2D::Draw(int positionX, int positionY, bool TRIANGLE_STRIP);
		void Image2D::Draw(int positionX, int positionY, float width, float height);
		void Image2D::Draw(int positionX, int positionY, float width, float height, bool TRIANGLE_STRIP);
		//bool Image2D::LoadTGA(TextureTGA* texture, char* filename);
	};
}

#endif