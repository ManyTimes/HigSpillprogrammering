#ifndef _IMAGE_H
#define _IMAGE_H

#include "include.h"
#include "includegl.h"
#include "autoarray.h"

namespace cgl
{
	/**********************/
	// NOT IN USE ANYMORE
	// NOT IN USE ANYMORE
	// NOT IN USE ANYMORE
	// USE "image2d.h" INSTEAD
	/**********************/
	class DECLARE Image
	{
	private:
	public:
		char* pixels;
		int width;
		int height;
		Image::Image(char* ps, int w, int h);
		Image::~Image();
		Image* Image::LoadBMP(const char* filename);
	};

	class DECLARE Texture
	{
	private:
		AUX_RGBImageRec* texture;
		GLuint textureID;
		float red, green, blue, alpha, posX, posY, posZ;
		int width;
		int height;
	public:
		Texture::Texture();
		Texture::Texture(std::string textureFilename);
		Texture::~Texture();
		void Texture::Initialize();
		void Texture::Load(std::string textureFilename);
		void Texture::Draw();
		void Texture::SetOptions(float red, float green, float blue, float alpha, float positionX, float positionY);
		void Texture::SetOptions(float red, float green, float blue, float alpha, float positionX, float positionY, float positionZ);
	};
}

#endif