#include "../Header/image.h"

namespace cgl
{
	/**********************/
	// NOT IN USE ANYMORE
	// NOT IN USE ANYMORE
	// NOT IN USE ANYMORE
	// USE "image2d.h" INSTEAD
	/**********************/
	Image::Image(char* ps, int w, int h)
	{
		pixels = ps;
		width = w;
		height = h;
	}

	Image::~Image() 
	{
		delete[] pixels;
	}

	Image* Image::LoadBMP(const char* filename) 
	{
		std::ifstream input;
		input.open(filename, std::ifstream::binary);
		assert(!input.fail() || !"Could not find file");
		char buffer[2];
		input.read(buffer, 2);
		assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
		input.ignore(8);
		int dataOffset = readInt(input);
		
		//Read the header
		int headerSize = readInt(input);
		int width;
		int height;
		switch(headerSize) 
		{
			case 40:
				//V3
				width = readInt(input);
				height = readInt(input);
				input.ignore(2);
				assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
				assert(readShort(input) == 0 || !"Image is compressed");
				break;
			case 12:
				//OS/2 V1
				width = readShort(input);
				height = readShort(input);
				input.ignore(2);
				assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
				break;
			case 64:
				//OS/2 V2
				assert(!"Can't load OS/2 V2 bitmaps");
				break;
			case 108:
				//Windows V4
				assert(!"Can't load Windows V4 bitmaps");
				break;
			case 124:
				//Windows V5
				assert(!"Can't load Windows V5 bitmaps");
				break;
			default:
				assert(!"Unknown bitmap format");
		}
		
		//Read the data
		int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
		int size = bytesPerRow * height;
		cgl::auto_array<char> pixels(new char[size]);
		input.seekg(dataOffset, std::ios_base::beg);
		input.read(pixels.Get(), size);
		
		//Get the data into the right format
		cgl::auto_array<char> pixels2(new char[width * height * 3]);
		for(int y = 0; y < height; y++) 
		{
			for(int x = 0; x < width; x++) 
			{
				for(int c = 0; c < 3; c++) 
				{
					pixels2[3 * (width * y + x) + c] = pixels[bytesPerRow * y + 3 * x + (2 - c)];
				}
			}
		}	
		input.close();
		return new Image(pixels2.Release(), width, height);
	}

	Texture::Texture()
	{
		Initialize();
	}

	Texture::Texture(std::string textureFilename)
	{
		Load(textureFilename);
		Initialize();
	}

	void Texture::Initialize()
	{
		red = green = blue = posX = posY = posZ = 0.0f;
		alpha = 1.0f;
	}

	//Takes a file (.BMP) and loads it first as a texture type, then loads it into the GPU and returns an ID, unique INT of the texture.
	//Drawing just uses the ID of the texture
	void Texture::Load(std::string textureFilename)									
	{
		/*wchar_t* temp = (wchar_t*)textureFilename.c_str();
		this->texture = auxDIBImageLoad(temp);
		glGenTextures(1, &this->textureID);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, this->texture->sizeX,  this->texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,  this->texture->data);
		free(texture);*/
	}

	Texture::~Texture()
	{
		if(this->texture != NULL)
		{
			delete [] this->texture;
		}
	}

	void Texture::SetOptions(float red, float green, float blue, float alpha, float positionX, float positionY)
	{
		this->posX = positionX;
		this->posY = positionY;
		this->alpha = alpha;
		this->red = red;
		this->blue = blue;
		this->green = green;
	}	
	void Texture::SetOptions(float red, float green, float blue, float alpha, float positionX, float positionY, float positionZ)
	{
		this->posX = positionX;
		this->posY = positionY;
		this->posZ = positionZ;
		this->alpha = alpha;
		this->red = red;
		this->blue = blue;
		this->green = green;
	}

	void Texture::Draw()
	{
		glColor4f(red, green, blue, alpha);
		glEnable(GL_TEXTURE_2D);
		if(this->posZ == 0)
		{
			glDisable(GL_DEPTH);
			glBindTexture(GL_TEXTURE_2D, this->textureID);
			glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2i(0, 0);
			glVertex2f(this->posX, this->posY);
				
			glTexCoord2i(1, 0);
			glVertex2f(this->posX + this->width, this->posY);
					
			glTexCoord2i(0, 1);
			glVertex2f(this->posX, this->posY + this->height);
				
			glTexCoord2i(1, 1);
			glVertex2f(this->posX + this->width, this->posY + this->height);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, this->textureID);
			glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2i(0, 0);
			glVertex3f(this->posX, this->posY, this->posZ);
				
			glTexCoord2i(1, 0);
			glVertex3f(this->posX + this->width, this->posY, this->posZ);
					
			glTexCoord2i(0, 1);
			glVertex3f(this->posX, this->posY + this->height, this->posZ);
				
			glTexCoord2i(1, 1);
			glVertex3f(this->posX + this->width, this->posY + this->height, this->posZ);
		}
			
		glEnd();
		glDisable(GL_TEXTURE_2D);
		if(this->posZ == 0)
		{
			glEnable(GL_DEPTH);
		}
	}

}