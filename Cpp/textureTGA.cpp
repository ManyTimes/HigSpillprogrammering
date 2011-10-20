#include "../Header/textureTGA.h"
namespace cgl
{
	TextureTGA::TextureTGA()
	{

	}
	TextureTGA::~TextureTGA()
	{

	}

	void TextureTGA::Load(char* filename)
	{
		/*if(!LoadTGA(this, filename))
		{
			cgl::Cout("Could not load file as TGA");
		}
		else
		{
			glGenTextures(1, &this->textureID);
			glBindTexture(GL_TEXTURE_2D, this->textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, this->bpp / 8, this->width, this->height, 0, this->type, GL_UNSIGNED_BYTE, this->imageData);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			free(this->imageData);
		}*/
	}
}