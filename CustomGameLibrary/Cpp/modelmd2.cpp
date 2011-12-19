#include "../Header/modelmd2.h"

namespace cgl
{
	//Converts a four-character array to an integer, using little-endian form
	int ModelMD2::toInt(const char* bytes)
	{
		return (int)(((unsigned char)bytes[3] << 24) |
					 ((unsigned char)bytes[2] << 16) |
					 ((unsigned char)bytes[1] << 8) |
					 (unsigned char)bytes[0]);
	}
		
	//Converts a two-character array to a short, using little-endian form
	short ModelMD2::toShort(const char* bytes)
	{
		return (short)(((unsigned char)bytes[1] << 8) | (unsigned char)bytes[0]);
	}
		
	//Converts a two-character array to an unsigned short, using little-endian//form
	unsigned short ModelMD2::toUShort(const char* bytes) 
	{
		return (unsigned short)(((unsigned char)bytes[1] << 8) | (unsigned char)bytes[0]);
	}
		
	//Converts a four-character array to a float, using little-endian form
	float ModelMD2::toFloat(const char* bytes) 
	{
		float f;
		if (isSystemLittleEndian()) 
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
		
	//Reads the next four bytes as an integer, using little-endian form
	int ModelMD2::readInt(std::ifstream &input) 
	{
		char buffer[4];
		input.read(buffer, 4);
		return toInt(buffer);
	}
		
	//Reads the next two bytes as a short, using little-endian form
	short ModelMD2::readShort(std::ifstream &input) 
	{
		char buffer[2];
		input.read(buffer, 2);
		return toShort(buffer);
	}
		
	//Reads the next two bytes as an unsigned short, using little-endian form
	unsigned short ModelMD2::readUShort(std::ifstream &input) 
	{
		char buffer[2];
		input.read(buffer, 2);
		return toUShort(buffer);
	}

	//Reads the next four bytes as a float, using little-endian form

	float ModelMD2::readFloat(std::ifstream &input) 
	{
		char buffer[4];
		input.read(buffer, 4);
		return toFloat(buffer);
	}

	//Calls readFloat three times and returns the results as a Vec3f object
	cgl::Vector3f ModelMD2::readVec3f(std::ifstream &input) 
	{
		float x = readFloat(input);
		float y = readFloat(input);
		float z = readFloat(input);
		//std::cout << "WITHIN FUNC:  X Y Z " << std::endl;
		return cgl::Vector3f(x, y, z);
	}

	ModelMD2::ModelMD2()
	{
	}

	ModelMD2::ModelMD2(char* modelFilename, GLuint textureID, float normals[], float animationSpeed)
	{
		this->animations = "";
		this->useNormals = true;
		this->animationSpeed = animationSpeed;
		this->textureID = textureID;
		this->normals = normals;
		this->file.open(modelFilename, std::istream::binary);
		if(Initialize() == false)
		{
			cgl::Cout("During initialization something went wrong.");
		}
	}


	ModelMD2::ModelMD2(char* modelFilename, GLuint textureID, float animationSpeed)
	{
		this->animations = "";
		this->useNormals = true;
		this->animationSpeed = animationSpeed;
		this->textureID = textureID;
		this->normals = NULL;
		this->file.open(modelFilename, std::istream::binary);
		if(Initialize() == false)
		{
			cgl::Cout("During initialization something went wrong.");
		}
	}

	void ModelMD2::Load(char* modelFileName, GLuint textureID, float normals[], float animationSpeed)
	{
		this->animations = "";
		this->useNormals = true;
		this->animationSpeed = animationSpeed;
		this->textureID = textureID;
		this->normals = normals;
		this->file.open(modelFileName, std::istream::binary);
		if(Initialize() == false)
		{
			cgl::Cout("During initialization something went wrong.");
		}
	}

	void ModelMD2::Load(char* modelFileName, GLuint textureID, float animationSpeed)
	{
		this->animations = "";
		this->useNormals = true;
		this->animationSpeed = animationSpeed;
		this->textureID = textureID;
		this->normals = NULL;
		this->file.open(modelFileName, std::istream::binary);
		if(Initialize() == false)
		{
			cgl::Cout("During initialization something went wrong.");
		}
	}


	ModelMD2::~ModelMD2() 
	{
		if (this->frames != NULL) 
		{
			for(int i = 0; i < this->numberOfFrames; i++) 
			{
				delete[] this->frames[i].vertices;
			}
			delete[] this->frames;
		}
		
		if (this->textureCoordinates != NULL) 
		{
			delete[] this->textureCoordinates;
		}
		if (this->triangles != NULL) 
		{
			delete[] this->triangles;
		}
	}



	bool ModelMD2::Initialize()
	{
		char buffer[64];
		this->file.read(buffer, 4);								//Reads the first 4 bytes, should be IDP2, if this is an md2 file
		if(buffer[0] != 'I' || buffer[1] != 'D' || buffer[2] != 'P' || buffer[3] != '2')
		{
			cgl::Cout("This file's head is not IDP2, cannot read the file, sure it is a MD2 File? Sure that the path given is correct?");
			return false;
		}
		if(readInt(this->file) != 8)
		{
			cgl::Cout("Cannot continue, version number is not 8 within this file");
			return false;
		}

		int textureWidth = readInt(this->file);
		int textureHeight = readInt(this->file);
		readInt(this->file);
		int numTextures = readInt(this->file);
		if(numTextures != 1)
		{
			cgl::Cout("Number of textures is not 1, trying to continue anyways...");
		}
		int numVertices = readInt(this->file);
		int numTexCoords = readInt(this->file);
		this->numberOfTriangles = readInt(this->file);
		readInt(this->file);							//Number of opengl commands
		this->numberOfFrames = readInt(this->file);

		int textureOffset = readInt(this->file);
		int texCoordOffset = readInt(this->file);
		int triangleOffset = readInt(this->file);
		int frameOffset = readInt(this->file);
		readInt(this->file);						//Offset of gl commands
		readInt(this->file);						//Offset to end of file


		//Load texture ID
		this->file.seekg(textureOffset, std::ios_base::beg);
		this->file.read(buffer, 64);
		if(this->textureID == NULL)
		{
			if(strlen(buffer) < 5 || strcmp(buffer + strlen(buffer)-4, ".bmp") != 0)
			{
				cgl::Cout("Filename of the texture is too short, or texture attached to the md2 file is not of type .bmp, trying to continue...");
			}
			else
			{
				cgl::Cout("Trying to load the attached image's path and data: ");
				std::cout << buffer;
				cgl::Image2D* img = new cgl::Image2D();
				if(img->LoadBMP((char*)std::string(buffer).c_str()))
				{
					this->textureID = img->ID;
				}
				else
				{
					cgl::Cout("Could not load the image: " + (std::string)buffer);
				}
				delete img;
			}
		}
		
		//Load texture
		this->file.seekg(texCoordOffset, std::ios_base::beg);
		this->textureCoordinates = new MD2TexCoord[numTexCoords];
		for(int i = 0; i < numTexCoords; i++)
		{
			MD2TexCoord* texCoord = this->textureCoordinates + i;
			texCoord->texCoordX = (float) readShort(this->file) / textureWidth;
			texCoord->texCoordY = 1 - (float) readShort(this->file) / textureHeight;
		}

		//Load triangles
		this->file.seekg(triangleOffset, std::ios_base::beg);
		this->triangles = new MD2Triangle[this->numberOfTriangles];
		for(int i = 0; i < this->numberOfTriangles; i++)
		{
			MD2Triangle* triangle = this->triangles + i;
			for(int ii = 0; ii < 3; ii++)
			{
				triangle->vertices[ii] = readUShort(this->file);
			}
			for(int ii = 0; ii < 3; ii++)
			{
				triangle->texCoords[ii] = readUShort(this->file);
			}
		}

		//Load frames
		this->file.seekg(frameOffset, std::ios_base::beg);
		this->frames = new MD2Frame[this->numberOfFrames];
		std::string anim[15];					//Maximum 10 animations
		for(int i = 0; i < 15; i++)
		{
			anim[i] = "";
		}
		int animNumber = 0;
		bool animBool = false;
		for(int i = 0; i < this->numberOfFrames; i++)
		{
			MD2Frame* frame = this->frames + i;
			frame->vertices = new MD2Vertex[numVertices];
			cgl::Vector3f scale = readVec3f(this->file);
			cgl::Vector3f translation = readVec3f(this->file);
			this->file.read(frame->name, 16);
			animBool = false;
			if(anim[0] == "")				//Read animation names from the file
			{
				for(int aa = 0; aa < strlen(frame->name); aa++)
				{
					if(frame->name[aa] != '_' && frame->name[aa] != '1' && frame->name[aa] != '2')
					{
						anim[animNumber] += frame->name[aa];
					}
					else
					{
						break;
					}
				}
				animNumber ++;
			}
			else
			{
				if(animNumber < 15)
				{
					std::string temp = "";
					for(int a = 0; a < animNumber; a ++)
					{
						temp = "";
						for(int aa = 0; aa < strlen(frame->name); aa++)
						{
							if(frame->name[aa] != '_' && frame->name[aa] != '1' && frame->name[aa] != '2')
							{
								temp += frame->name[aa];
							}
							else
							{
								break;
							}
						}
						if(strcmp(anim[a].c_str(), temp.c_str()) == 0)
						{
							animBool = true;								//Animation exist
							a = animNumber;
						}
					}
					if(animBool == false)
					{
						anim[animNumber] = temp;
						this->animations += temp + ", ";
						animNumber++;
					}
				}
			}
		//	this->animations += cgl::i2s(i) + " - " + frame->name + ", ";
			for(int ii = 0; ii < numVertices; ii++)
			{
				MD2Vertex* vertex = frame->vertices + ii;
				this->file.read(buffer, 3);
				cgl::Vector3f v((unsigned char)buffer[0], (unsigned char)buffer[1], (unsigned char)buffer[2]);
				vertex->pos.x = translation.x + (scale[0] * v[0]);
				vertex->pos.y = translation.y + (scale[1] * v[1]);
				vertex->pos.z = translation.z + (scale[2] * v[2]);
				this->file.read(buffer, 1);
				int normalIndex = (int) ((unsigned char)buffer[0]);
				if(this->normals != NULL)
				{
					vertex->normal = cgl::Vector3f(this->normals[3 * normalIndex], this->normals[3 * normalIndex +1], this->normals[3 * normalIndex +2 ]);
				}
			}
		}
		this->firstFrame = 0;
		this->lastFrame = this->numberOfFrames-1;
		return true;
	}


	void ModelMD2::SetAnimation(char* animationName)
	{
		bool found = false;
		for(int i = 0; i < this->numberOfFrames; i++)
		{
			MD2Frame* frame = frames + i;
			if(strlen(frame->name) > strlen(animationName) 
				&& strncmp(frame->name, animationName, strlen(animationName)) == 0 
				&& !isalpha(frame->name[strlen(animationName)]))
			{
				if(!found)
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
				if (found) 
				{
					break;
				}
			}
		}
	}



	void ModelMD2::Animate()
	{
		if (this->animationSpeed < 0) 
		{
			cgl::Cout("Animation speed is too low, it cannot be negative");
			return;
		}
		this->time += this->animationSpeed;
		if (this->time < 1000000000)
		{
			this->time -= (int)this->time;
		}
		else
		{
			this->time = 0;
		}
	}

	void ModelMD2::EnableNormals(bool value)
	{
		this->useNormals = value;
	}

	void ModelMD2::Draw(cgl::Vector3f& position, float& scale, float *m)
	{
		this->Animate();
		glPushMatrix();
		//glTranslatef(position.x, position.y, position.z);
		//if(m != NULL)
			glMultMatrixf(m);
		glScalef(scale, scale, scale);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		//Should try to call PUSH and POP, and in between translatef(positionx, position.y, position.z)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int frameIndex1 = (int)(this->time * (this->lastFrame - this->firstFrame + 1)) + this->firstFrame;
		if (frameIndex1 > this->lastFrame) 
		{
			frameIndex1 = this->firstFrame;
		}
		
		int frameIndex2;
		if (frameIndex1 < this->lastFrame) 
		{
			frameIndex2 = frameIndex1 + 1;
		}
		else 
		{
			frameIndex2 = this->firstFrame;
		}
		
		MD2Frame* frame1 = frames + frameIndex1;
		MD2Frame* frame2 = frames + frameIndex2;
		float frac =(this->time - (float)(frameIndex1 - this->firstFrame) /(float)(this->lastFrame - this->firstFrame + 1)) * (this->lastFrame - this->firstFrame + 1);
		MD2Vertex* v1;
		MD2Vertex* v2;
		MD2TexCoord* texCoord;
		MD2Triangle* triangle;
		cgl::Vector3f pos(0,0,0);
		cgl::Vector3f normal(0,0,0);
		glBegin(GL_TRIANGLES);
		if(this->useNormals == true)
		{
			for(int i = 0; i < this->numberOfTriangles; i++) 
			{
				triangle = this->triangles + i;
				for(int j = 0; j < 3; j++) 
				{
					v1 = frame1->vertices + triangle->vertices[j];
					v2 = frame2->vertices + triangle->vertices[j];
					pos = v1->pos * (1 - frac) + v2->pos * frac;
					normal = v1->normal * (1 - frac) + v2->normal * frac;
					if (normal[0] == 0 && normal[1] == 0 && normal[2] == 0) 
					{
						normal.z = 1;
					}
					glNormal3f(normal[0], normal[1], normal[2]);
					texCoord = textureCoordinates + triangle->texCoords[j];
					glTexCoord2f(texCoord->texCoordX, texCoord->texCoordY);
					glVertex3f(pos[0], pos[1], pos[2]);
				}
			}
		}
		else
		{
			for(int i = 0; i < this->numberOfTriangles; i++) 
			{
				triangle = this->triangles + i;
				for(int j = 0; j < 3; j++) 
				{
					v1 = frame1->vertices + triangle->vertices[j];
					v2 = frame2->vertices + triangle->vertices[j];
					pos = v1->pos * (1 - frac) + v2->pos * frac;
					texCoord = textureCoordinates + triangle->texCoords[j];
					glTexCoord2f(texCoord->texCoordX, texCoord->texCoordY);
					glVertex3f(pos[0], pos[1], pos[2]);
				}
			}
		}
		glEnd();
		glPopMatrix();
	}

}
