#include "../Header/Image2D.h"
namespace cgl
{
	Image2D::Image2D()
	{
		for(int i = 0; i < 12; i++)
		{	
			this->uTGAcompare[i] = 0;		//uncompressed
			this->cTGAcompare[i] = 0;		//compressed
		}
		this->uTGAcompare[2] = 2;
		this->cTGAcompare[2] = 10;
	}
	Image2D::~Image2D()
	{
		delete [] this->cTGAcompare;
		delete [] this->uTGAcompare;
	}

	bool Image2D::LoadBMP2(const char* filename)
	{
		if(!filename)
		{
			return false;
		}
		FILE* file = NULL;
		file = fopen(filename, "r");		//Does file exists?
		if(file)
		{
			fclose(file);					//Closing handle
			wchar_t* temp = (wchar_t*)filename;
			this->texture = auxDIBImageLoad(filename);
			if(this->texture != NULL && this->texture->data != NULL)
			{
				glGenTextures(1, &this->ID);
				glBindTexture(GL_TEXTURE_2D, this->ID);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, 3, this->texture->sizeX,  this->texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,  this->texture->data);
				free(texture);
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}
	bool Image2D::LoadBMP(char* filename)
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
		switch(headerSize) 
		{
			case 40:
				//V3
				this->width = readInt(input);
				this->height = readInt(input);
				input.ignore(2);
				assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
				assert(readShort(input) == 0 || !"Image is compressed");
				break;
			case 12:
				//OS/2 V1
				this->width = readShort(input);
				this->height = readShort(input);
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
		int bytesPerRow = ((this->width * 3 + 3) / 4) * 4 - (this->width * 3 % 4);
		int size = bytesPerRow * this->height;
		cgl::auto_array<char> pixels(new char[size]);
		input.seekg(dataOffset, std::ios_base::beg);
		input.read(pixels.Get(), size);
		
		//Get the data into the right format
		cgl::auto_array<char> pixels2(new char[this->width * this->height * 3]);
		for(int y = 0; y < this->height; y++) 
		{
			for(int x = 0; x < this->width; x++) 
			{
				for(int c = 0; c < 3; c++) 
				{
					pixels2[3 * (this->width * y + x) + c] = pixels[bytesPerRow * y + 3 * x + (2 - c)];
				}
			}
		}	
		input.close();
		this->dataBMP = pixels2.Release();
		glGenTextures(1, &this->ID); //Make room for our texture
		glBindTexture(GL_TEXTURE_2D, this->ID); //Tell OpenGL which texture to edit
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
					 0,                            //0 for now
					 GL_RGB,                       //Format OpenGL uses for image
					 this->width, this->height,  //Width and height
					 0,                            //The border of the image
					 GL_RGB, //GL_RGB, because pixels are stored in RGB format
					 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
									   //as unsigned numbers
					 this->dataBMP);               //The actual pixel data*/

		return true;
	}

	bool Image2D::LoadTGA(char* filename)							// Load a TGA file
	{
		FILE * fTGA;												// File pointer to texture file
		fTGA = fopen(filename, "rb");								// Open file for reading

		if(fTGA == NULL)											// If it didn't open....
		{
			cgl::Cout("Could not open file");
			return false;														// Exit function
		}

		if(fread(&this->header, sizeof(this->header), 1, fTGA) == 0)			// Attempt to read 12 byte header from file
		{
			cgl::Cout("Could not read file header");
			if(fTGA != NULL)													// Check to seeiffile is still open
			{
				fclose(fTGA);													// If it is, close it
			}
			return false;														// Exit function
		}

		if(memcmp(this->uTGAcompare, &this->header, sizeof(this->header)) == 0)				// See if header matches the predefined header of 
		{																		// an Uncompressed TGA image
			LoadUncompressedTGA(filename, fTGA);						// If so, jump to Uncompressed TGA loading code
		}
		else if(memcmp(this->cTGAcompare, &this->header, sizeof(this->header)) == 0)		// See if header matches the predefined header of
		{																		// an RLE compressed TGA image
			LoadCompressedTGA(filename, fTGA);							// If so, jump to Compressed TGA loading code
		}
		else																	// If header matches neither type
		{
			cgl::Cout("TGA file is not compressed or uncompressed (type 2 or 10)");
			fclose(fTGA);
			return false;														// Exit function
		}
		glGenTextures(1, &this->ID);
		glBindTexture(GL_TEXTURE_2D, this->ID);
		glTexImage2D(GL_TEXTURE_2D, 0, this->bpp / 8, this->width, this->height, 0,this->type, GL_UNSIGNED_BYTE, this->dataTGA);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		if (this->dataTGA)						// If Texture Image Exists ( CHANGE )
		{
			free(this->dataTGA);					// Free The Texture Image Memory ( CHANGE )
		}
		return true;															// All went well, continue on
	}

	bool Image2D::LoadUncompressedTGA(char* filename, FILE* fTGA)	// Load an uncompressed TGA (note, much of this code is based on NeHe's 
	{																			// TGA Loading code nehe.gamedev.net)
		if(fread(this->headerTGA, sizeof(this->headerTGA), 1, fTGA) == 0)					// Read TGA header
		{			
			cgl::Cout("Could not read file header");
			if(fTGA != NULL)													// if file is still open
			{
				fclose(fTGA);													// Close it
			}
			return false;														// Return failular
		}	
		this->width  = this->headerTGA[1] * 256 + this->headerTGA[0];		// Determine The TGA Width	(highbyte*256+lowbyte)
		this->height = this->headerTGA[3] * 256 + this->headerTGA[2];		// Determine The TGA Height	(highbyte*256+lowbyte)
		this->bpp	= this->headerTGA[4];									// Determine the bits per pixel

		if((this->width <= 0) || (this->height <= 0) || ((this->bpp != 24) && (this->bpp !=32)))	// Make sure all information is valid
		{
			cgl::Cout("Invalid texture information");
			if(fTGA != NULL)													// Check if file is still open
			{
				fclose(fTGA);													// If so, close it
			}
			return false;														// Return failed
		}

		if(this->bpp == 24)													// If the BPP of the image is 24...
			this->type	= GL_RGB;											// Set Image type to GL_RGB
		else																	// Else if its 32 BPP
			this->type	= GL_RGBA;											// Set image type to GL_RGBA

		this->bytesPerPixel	= (this->bpp / 8);									// Compute the number of BYTES per pixel
		this->imageSize		= (this->bytesPerPixel * this->width * this->height);// Compute the total amout ofmemory needed to store data
		this->dataTGA	= (GLubyte *)malloc(this->imageSize);				// Allocate that much memory

		if(this->dataTGA == NULL)											// If no space was allocated
		{
			cgl::Cout("Could not allocate memory for image");
			fclose(fTGA);														// Close the file
			return false;														// Return failed
		}

		if(fread(this->dataTGA, 1, this->imageSize, fTGA) != this->imageSize)	// Attempt to read image data
		{
			cgl::Cout("Could not read image data");
			if(this->dataTGA != NULL)										// If imagedata has data in it
			{
				free(this->dataTGA);										// Delete data from memory
			}
			fclose(fTGA);														// Close file
			return false;														// Return failed
		}

		// Byte Swapping Optimized By Steve Thomas
		for(GLuint cswap = 0; cswap < (int)this->imageSize; cswap += this->bytesPerPixel)
		{
			this->dataTGA[cswap] ^= this->dataTGA[cswap+2] ^=
			this->dataTGA[cswap] ^= this->dataTGA[cswap+2];
		}

		fclose(fTGA);															// Close file
		return true;															// Return success
	}

	bool Image2D::LoadCompressedTGA(char* filename, FILE* fTGA)		// Load COMPRESSED TGAs
	{ 
		if(fread(this->headerTGA, sizeof(this->headerTGA), 1, fTGA) == 0)					// Attempt to read header
		{
			cgl::Cout("Could not read info header");
			if(fTGA != NULL)													// If file is open
			{
				fclose(fTGA);													// Close it
			}
			return false;														// Return failed
		}

		this->width  = this->headerTGA[1] * 256 + this->headerTGA[0];		// Determine The TGA Width	(highbyte*256+lowbyte)
		this->height = this->headerTGA[3] * 256 + this->headerTGA[2];		// Determine The TGA Height	(highbyte*256+lowbyte)
		this->bpp	= this->headerTGA[4];									// Determine Bits Per Pixel

		if((this->width <= 0) || (this->height <= 0) || ((this->bpp != 24) && (this->bpp !=32)))	//Make sure all texture info is ok
		{
			cgl::Cout("Invalid texture information");
			if(fTGA != NULL)													// Check if file is open
			{
				fclose(fTGA);													// Ifit is, close it
			}
			return false;														// Return failed
		}

		if(this->bpp == 24)													// If the BPP of the image is 24...
			this->type	= GL_RGB;											// Set Image type to GL_RGB
		else																	// Else if its 32 BPP
			this->type	= GL_RGBA;											// Set image type to GL_RGBA

		this->bytesPerPixel	= (this->bpp / 8);									// Compute BYTES per pixel
		this->imageSize		= (this->bytesPerPixel * this->width * this->height);		// Compute amout of memory needed to store image
		this->dataTGA	= (GLubyte *)malloc(this->imageSize);					// Allocate that much memory

		if(this->dataTGA == NULL)											// If it wasnt allocated correctly..
		{
			cgl::Cout("Could not allocate memory for image");
			fclose(fTGA);														// Close file
			return false;														// Return failed
		}

		GLuint pixelcount	= this->height * this->width;							// Nuber of pixels in the image
		GLuint currentpixel	= 0;												// Current pixel being read
		GLuint currentbyte	= 0;												// Current byte 
		GLubyte * colorbuffer = (GLubyte *)malloc(this->bytesPerPixel);			// Storage for 1 pixel

		do
		{
			GLubyte chunkheader = 0;											// Storage for "chunk" header
			if(fread(&chunkheader, sizeof(GLubyte), 1, fTGA) == 0)				// Read in the 1 byte header
			{
				cgl::Cout("Could not read RLE header");
				if(fTGA != NULL)												// If file is open
				{
					fclose(fTGA);												// Close file
				}
				if(this->dataTGA != NULL)									// If there is stored image data
				{
					free(this->dataTGA);									// Delete image data
				}
				return false;													// Return failed
			}

			if(chunkheader < 128)												// If the ehader is < 128, it means the that is the number of RAW color packets minus 1
			{																	// that follow the header
				chunkheader++;													// add 1 to get number of following color values
				for(short counter = 0; counter < chunkheader; counter++)		// Read RAW color values
				{
					if(fread(colorbuffer, 1, this->bytesPerPixel, fTGA) != this->bytesPerPixel) // Try to read 1 pixel
					{
						cgl::Cout("Could not read image data");
						if(fTGA != NULL)													// See if file is open
						{
							fclose(fTGA);													// If so, close file
						}
						if(colorbuffer != NULL)												// See if colorbuffer has data in it
						{
							free(colorbuffer);												// If so, delete it
						}
						if(this->dataTGA != NULL)										// See if there is stored Image data
						{
							free(this->dataTGA);										// If so, delete it too
						}
						return false;														// Return failed
					}
																							// write to memory
					this->dataTGA[currentbyte		] = colorbuffer[2];				    // Flip R and B vcolor values around in the process 
					this->dataTGA[currentbyte + 1	] = colorbuffer[1];
					this->dataTGA[currentbyte + 2	] = colorbuffer[0];

					if(this->bytesPerPixel == 4)												// if its a 32 bpp image
					{
						this->dataTGA[currentbyte + 3] = colorbuffer[3];				// copy the 4th byte
					}

					currentbyte += this->bytesPerPixel;										// Increase thecurrent byte by the number of bytes per pixel
					currentpixel++;															// Increase current pixel by 1

					if(currentpixel > pixelcount)											// Make sure we havent read too many pixels
					{
						cgl::Cout("Too many pixels being read");
						if(fTGA != NULL)													// If there is a file open
						{
							fclose(fTGA);													// Close file
						}	
						if(colorbuffer != NULL)												// If there is data in colorbuffer
						{
							free(colorbuffer);												// Delete it
						}
						if(this->dataTGA != NULL)										// If there is Image data
						{
							free(this->dataTGA);										// delete it
						}
						return false;														// Return failed
					}
				}
			}
			else																			// chunkheader > 128 RLE data, next color reapeated chunkheader - 127 times
			{
				chunkheader -= 127;															// Subteact 127 to get rid of the ID bit
				if(fread(colorbuffer, 1, this->bytesPerPixel, fTGA) != this->bytesPerPixel)		// Attempt to read following color values
				{	
					cgl::Cout("Could not read from file");
					if(fTGA != NULL)														// If thereis a file open
					{
						fclose(fTGA);														// Close it
					}
					if(colorbuffer != NULL)													// If there is data in the colorbuffer
					{
						free(colorbuffer);													// delete it
					}
					if(this->dataTGA != NULL)											// If thereis image data
					{
						free(this->dataTGA);											// delete it
					}
					return false;															// return failed
				}

				for(short counter = 0; counter < chunkheader; counter++)					// copy the color into the image data as many times as dictated 
				{																			// by the header
					this->dataTGA[currentbyte		] = colorbuffer[2];					// switch R and B bytes areound while copying
					this->dataTGA[currentbyte + 1	] = colorbuffer[1];
					this->dataTGA[currentbyte + 2	] = colorbuffer[0];

					if(this->bytesPerPixel == 4)												// If TGA images is 32 bpp
					{
						this->dataTGA[currentbyte + 3] = colorbuffer[3];				// Copy 4th byte
					}

					currentbyte += this->bytesPerPixel;										// Increase current byte by the number of bytes per pixel
					currentpixel++;															// Increase pixel count by 1

					if(currentpixel > pixelcount)											// Make sure we havent written too many pixels
					{
						cgl::Cout("Too many pixels read");
						if(fTGA != NULL)													// If there is a file open
						{
							fclose(fTGA);													// Close file
						}	
						if(colorbuffer != NULL)												// If there is data in colorbuffer
						{
							free(colorbuffer);												// Delete it
						}

						if(this->dataTGA != NULL)										// If there is Image data
						{
							free(this->dataTGA);										// delete it
						}
						return false;														// Return failed
					}
				}
			}
		}
		while(currentpixel < pixelcount);													// Loop while there are still pixels left
		fclose(fTGA);																		// Close the file
		return true;																		// return success
	}

	void Image2D::Draw(int positionX, int positionY, float width, float height)
	{
		this->Draw(positionX, positionY, height, width, true);
	}
	void Image2D::Draw(int positionX, int positionY, float width, float height, bool TRIANGLE_STRIP)
	{
		glBindTexture(GL_TEXTURE_2D, this->ID);
		if(TRIANGLE_STRIP)
		{
			glBegin(GL_TRIANGLE_STRIP);
		}
		else
		{
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f,1.0f); 
			glVertex3i(positionX, positionY + height,-100);

			glTexCoord2f(0.0f,0.0f); 
			glVertex3i(positionX, positionY,-100);

			glTexCoord2f(1.0f,0.0f); 
			glVertex3i(positionX + width, positionY,-100);

			glTexCoord2f(1.0f,1.0f); 
			glVertex3i(positionX + width, positionY+height,-100);
		}
		glEnd();
	}

	void Image2D::Draw(int positionX, int positionY, bool TRIANGLE_STRIP)
	{
		glBindTexture(GL_TEXTURE_2D, this->ID);
		if(TRIANGLE_STRIP)
		{
			glBegin(GL_TRIANGLE_STRIP);
		}
		else
		{
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f,1.0f); 
			glVertex3i(positionX, positionY + this->height,-100);

			glTexCoord2f(0.0f,0.0f); 
			glVertex3i(positionX, positionY,-100);

			glTexCoord2f(1.0f,0.0f); 
			glVertex3i(positionX + this->width, positionY,-100);

			glTexCoord2f(1.0f,1.0f); 
			glVertex3i(positionX + this->width, positionY + this->height,-100);
		}
		glEnd();
	}
}