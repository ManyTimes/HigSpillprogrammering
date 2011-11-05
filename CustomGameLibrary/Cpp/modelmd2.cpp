#include "../Header/modelmd2.h"

namespace cgl
{
	ModelMD2::ModelMD2(char* filename, GLuint modeltextureID, float modelNormals[])
	{
		this->animationTime = 0;
		this->normals = modelNormals;
		this->textureID = modeltextureID;
		std::ifstream input;
		input.open(filename, std::istream::binary);
		char buffer[64];
		input.read(buffer,4);     //MD2 files' first bytes is "IDP2"
		if(buffer[0] != 'I' || buffer[1] != 'D' || buffer[2] != 'P' || buffer[3] != '2')
		{
			cgl::Cout("Cannot load this file as a MD2 file, header is not IPD2");
		}
		else
		{
		if(readInt(input) != 8)
		{
			cgl::Cout("Version is not 8, cannot continue");
		}
		else
		{
			int textureWidth = readInt(input); //Reads a few bytes at a time, header specific for mD2 
			int textureHeight = readInt(input);
			readInt(input);                     //Bytes per frame
			int numTextures = readInt(input);
			if(numTextures != 1)
			{
				cgl::Cout("Number of textures is not 1, trying to continue...");
			}
			int numVertices = readInt(input);
			int numTexCoords = readInt(input);
			int numTriangles = readInt(input);
			readInt(input);                     //Number of openGL commands
			int numFrames = readInt(input);
			int textureOffset = readInt(input);
			int texCoordOffset = readInt(input);
			int triangleOffset = readInt(input);
			int frameOffset = readInt(input);
			readInt(input);
			readInt(input);
			input.seekg(textureOffset, std::ios_base::beg);
			input.read(buffer, 64);
		    
			cgl::Image2D* img = new cgl::Image2D(); 
														//Extension offset for the texture?
			if(std::strlen(buffer) < 5 || std::strcmp(buffer + strlen(buffer) - 4,".bmp") != 0)
			{
			  cgl::Cout("Extension is not .bmp or buffer read for the texture is less than 5, trying to continue...");
			}       
			else
			{
			  img->LoadBMP(buffer);                                              //MD2 file contains a .BMP filename, that is attached
			  this->textureID = img->ID; 
			} //Can just skip this, if textureID has been given with it...
			delete img;

			//Load texture coordinates
			input.seekg(texCoordOffset, std::ios_base::beg);
			this->textureCoordinate = new MD2TextureCoordinate[numTexCoords];
			for(int i = 0; i < numTexCoords; i++)
			{
				MD2TextureCoordinate* texCoord=  this->textureCoordinate + i;
				texCoord->textureCoordinateX = (float)readShort(input) / textureWidth;
				texCoord->textureCoordinateY = 1 - (float)readShort(input) / textureHeight;
			}
		    
			//Load triangles
			input.seekg(texCoordOffset, std::ios_base::beg);
			this->triangles = new MD2Triangle[numTriangles];
			this->numberOfTriangles = numTriangles;
			for(int i = 0; i < numTriangles; i++)
			{
				MD2Triangle* triangle = this->triangles + i;
				for(int ii = 0; ii < 3; ii++)
				{
					triangle->vertices[ii] = this->Read2ToUnsignedShort(input);
				}
				for(int ii = 0; ii < 3; ii++)
				{
					triangle->textureCoordinates[ii] = this->Read2ToUnsignedShort(input);
				}
			}
			//Load frames
			input.seekg(frameOffset, std::ios_base::beg);
			this->frames = new MD2Frame[numFrames];
			this->numberOfFrames = numFrames;
			for(int i = 0; i < numFrames; i++)
			{
				MD2Frame* frame = this->frames + i;
				frame->vertices = new MD2Vertex[numVertices];
				cgl::Vector3f scale = this->Read4ToVector3f(input);
				cgl::Vector3f translation = this->Read4ToVector3f(input);
				input.read(frame->name, 16);
				for(int ii = 0; ii < numVertices; ii++)
				{
					MD2Vertex* vertex = frame->vertices + ii;
					input.read(buffer, 3);
					cgl::Vector3f temp((unsigned char)buffer[0],
										(unsigned char)buffer[1],
										(unsigned char)buffer[2]);
					vertex->position = translation + 
										cgl::Vector3f(scale[0] * temp[0], 
										scale[1] * temp[1], 
										scale[2] * temp[2]);
					input.read(buffer, 1);
					int normalIndex = (int)((unsigned char)buffer[0]);
					vertex->normal = cgl::Vector3f(this->normals[3*normalIndex],
						this->normals[3 * normalIndex + 1],
						this->normals[3 * normalIndex + 2]);
				}
			}
		}
	  }
	}

	void ModelMD2::Draw()
	{
		//Advancing model animation
		if(deltaTime < 0)
		{
			return;
		}
		animationTime += deltaTime;
		if(animationTime < 1000000000)
		{
			animationTime -= (int) animationTime;
		}
		else
		{
			this->animationTime = 0;
		}

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int frameIndex1 = (int)(this->animationTime * (this->lastFrame - this->firstFrame + 1)) + this->firstFrame;
		int frameIndex2;
		if(frameIndex1 > this->lastFrame)
		{	
			frameIndex1 = this->firstFrame;
		}
		if(frameIndex1 < this->lastFrame)
		{
			frameIndex2 = frameIndex1 + 1;
		}
		else
		{
			frameIndex2 = this->firstFrame;
		}

		MD2Frame* frame1 = frames + frameIndex1;
		MD2Frame* frame2 = frames + frameIndex2;
		float fraction = 	(this->animationTime - (float)(frameIndex1 - this->firstFrame) /
							(float)(this->lastFrame - this->firstFrame + 1)) * (this->lastFrame - this->firstFrame + 1);

		glBegin(GL_TRIANGLES);
		for(int i = 0; i < this->numberOfTriangles; i++)
		{
			MD2Triangle* triangle = this->triangles + i;
			for(int ii = 0; ii < 3; ii++)
			{
				MD2Vertex* v1 = frame1->vertices + triangle->vertices[ii];
				MD2Vertex* v2 = frame2->vertices + triangle->vertices[ii];
				cgl::Vector3f pos = v1->position * (1 - fraction) + v2->normal * fraction;
				cgl::Vector3f normal = v1->normal * (1 - fraction) + v2->normal + fraction;
				if(normal[0] == 0 && normal[1] == 0 && normal[2] == 0)
				{
					normal = cgl::Vector3f(0,0, 1);
				}
				glNormal3f(normal[0], normal[1], normal[2]);
				MD2TextureCoordinate* texCoord = this->textureCoordinate + triangle->textureCoordinates[ii];
				glTexCoord2f(texCoord->textureCoordinateX, texCoord->textureCoordinateY);
				glVertex3f(pos[0], pos[1], pos[2]);
			}
		}
	}

	void ModelMD2::SetAnimation(const char* animationName)
	{
		bool found = false;
		for(int i = 0; i < this->numberOfFrames; i++)
		{
			MD2Frame* frame = this->frames + i;
			if(std::strlen(frame->name) > std::strlen(animationName) 
				&& strncmp(frame->name, animationName, std::strlen(animationName)) == 0
				&& !isalpha(frame->name[std::strlen(animationName)]))
			{
				if(found == false)
				{
					found = true;
					this->firstFrame = i;
				}
				else
				{
					this->lastFrame = i;
				}
			}
			else
			{
				if(found == true)
				{
					break;
				}
			}
		}
	}

	
	//Converts 4 byres char to integer value
	int ModelMD2::Bytes4ToInt(const char* bytes)
	{
		return (int)(((unsigned char)bytes[3] << 24) |
					 ((unsigned char)bytes[2] << 16) |
					 ((unsigned char)bytes[1] << 8) |
					  (unsigned char)bytes[0]);
	}

	//Converts 2 byres char to integer value
	short ModelMD2::Bytes2ToShort(const char* bytes)
	{
	  return (short)(((unsigned char)bytes[1] << 8) |
					  (unsigned char)bytes[0]);
	}

	//Reads 4 bytes within the input stream and returns an integer value of those 4 bytes
	int ModelMD2::Read4BytesToInt(std::ifstream &input)
	{
		char buffer[4];
		input.read(buffer, 4);
		return this->Bytes4ToInt(buffer);
	}

	unsigned short ModelMD2::Read2ToUnsignedShort(std::ifstream &input)
	{
		char buffer[2];
		input.read(buffer, 2);
		return this->Bytes2ToUnsignedShort(buffer);
	}

	unsigned short ModelMD2::Bytes2ToUnsignedShort(const char* bytes)
	{
		return (unsigned short)(((unsigned char)bytes[1] << 8) |
								(unsigned char)bytes[0]);
	}

	float ModelMD2::Bytes4ToFloat(const char* bytes)
	{
		float f;
		if(this->isSystemLittleEndian() == true)
		{
			((char*)&f)[0] = bytes[0];
			((char*)&f)[1] = bytes[1];
			((char*)&f)[2] = bytes[2];
			((char*)&f)[3] = bytes[3];
		}
		else
		{
			((char*)&f)[0] = bytes[3];
			((char*)&f)[1] = bytes[2];
			((char*)&f)[2] = bytes[1];
			((char*)&f)[3] = bytes[0];
		}
		return f;
	}
	bool ModelMD2::isSystemLittleEndian()
	{
	  short s = 1;
	  return (((char*)&s)[0]) == 1;
	}

	//Calls readFloat three times and returns the results as a Vec3f object
	cgl::Vector3f ModelMD2::Read4ToVector3f(std::ifstream &input) 
	{
		float x = this->Read4ToFloat(input);
		float y = this->Read4ToFloat(input);
		float z = this->Read4ToFloat(input);
		return cgl::Vector3f(x, y, z);
	}

	//Reads the next four bytes as a float, using little-endian form
	float ModelMD2::Read4ToFloat(std::ifstream &input) 
	{
		char buffer[4];
		input.read(buffer, 4);
		return this->Bytes4ToFloat(buffer);
	}
	//Reads the next two bytes as a short, using little-endian form
	short ModelMD2::Read2ToShort(std::ifstream &input) 
	{
		char buffer[2];
		input.read(buffer, 2);
		return Bytes2ToShort(buffer);
	}

	ModelMD2::~ModelMD2()
	{
		if(this->frames != NULL)
		{
			for(int i = 0; i < this->numberOfFrames; i++)
			{
				delete[] this->frames[i].vertices;
			}
			delete[] this->frames;
		}		
		if(this->textureCoordinate != NULL)
		{
			delete[] this->textureCoordinate;
		}
		if(this->triangles != NULL)
		{
			delete[] this->triangles;
		}
	}
	
}
