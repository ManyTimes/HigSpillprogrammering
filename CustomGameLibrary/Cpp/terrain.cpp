#include "../Header/terrain.h"

namespace cgl
{
	//Constructor, loads a heightmap.BMP file into memory ready to be drawn. Maximum terrain height, is the heighest "cliff" possible (y value)
	Terrain::Terrain(char* heightMapTexture, float maximumTerrainHeight)
	{
		cgl::Image2D* tempImg = new cgl::Image2D();
		tempImg->LoadBMP(heightMapTexture);
		this->width = tempImg->width;
		this->length = tempImg->height;

		this->heights = new float*[this->length];		//X-Z plane
		for(int i = 0; i < this->length; i++)
		{
			this->heights[i] = new float[this->width];
		}
		this->normals = new Vector3f*[this->length];	//Normals in x-zplane
		for(int i = 0; i < this->length;i++)
		{	
			this->normals[i] = new Vector3f[this->width];
		}

		for(int y = 0; y < tempImg->height; y++)
		{
			for(int x = 0; x < tempImg->width; x++)
			{
				unsigned char color = (unsigned char)tempImg->dataBMP[3 * (y*tempImg->width + x)];
				float h = maximumTerrainHeight * ((color/255.0f)-0.5f);
				this->SetHeight(x,y,h);
			}
		}

		delete tempImg;
		ComputeNormals();
	}

	Terrain::~Terrain()
	{
		for(int i = 0; i < length; i++)
		{
			delete[] this->heights[i];
		}
		delete[] heights;
		for(int i = 0; i < length; i++)
		{
			delete[] this->normals[i];
		}
		delete[] this->normals;
	}

	int Terrain::GetWidth()
	{
		return width;
	}

	int Terrain::GetLength()
	{
		return length;
	}

	void Terrain::SetHeight(int positionX, int positionZ, float height)
	{
		heights[positionZ][positionX] = height;
	}

	float Terrain::GetHeight(int x, int z)
	{
		return heights[z][x];
	}

	//Computing normals, this is done automatically through constructor of this class
	void Terrain::ComputeNormals()
	{
		//Compute the rough version of the normals
		Vector3f** normals2 = new Vector3f*[length];
		for(int i = 0; i < this->length; i++) 
		{
			normals2[i] = new Vector3f[width];
		}
		for(int z = 0; z < this->length; z++) 
		{
			for(int x = 0; x < this->width; x++) 
			{
				cgl::Vector3f sum(0.0f, 0.0f, 0.0f);
				cgl::Vector3f out;
				if (z > 0) 
				{
					out = cgl::Vector3f(0.0f, heights[z - 1][x] - heights[z][x], -1.0f);
				}
				cgl::Vector3f in;
				if (z < this->length - 1) 
				{
					in = cgl::Vector3f(0.0f, heights[z + 1][x] - heights[z][x], 1.0f);
				}
				cgl::Vector3f left;
				if (x > 0) 
				{
					left = cgl::Vector3f(-1.0f, heights[z][x - 1] - heights[z][x], 0.0f);
				}
				cgl::Vector3f right;
				if (x < this->width - 1) 
				{
					right = cgl::Vector3f(1.0f, heights[z][x + 1] - heights[z][x], 0.0f);
				}
				if (x > 0 && z > 0) 
				{
					sum += out.Cross(left).NormalizeNew();
				}
				if (x > 0 && z < this->length - 1) 
				{
					sum += left.Cross(in).NormalizeNew();
				}
				if (x < this->width - 1 && z < this->length - 1) 
				{
					sum += in.Cross(right).NormalizeNew();
				}
				if (x < this->width - 1 && z > 0) 
				{
					sum += right.Cross(out).NormalizeNew();
				}

				/*if (x > 0 && z > 0) 
				{
					sum += out.Cross(left).Normalize(0);
				}
				if (x > 0 && z < length - 1) 
				{
					sum += left.Cross(in).Normalize(0);
				}
				if (x < width - 1 && z < length - 1) 
				{
					sum += in.Cross(right).Normalize(0);
				}
				if (x < width - 1 && z > 0) 
				{
					sum += right.Cross(out).Normalize(0);
				}*/
				normals2[z][x] = sum;
			}
		}

		//Smooth out the normals
		const float FALLOUT_RATIO = 0.5f;
		for(int z = 0; z < this->length; z++) 
		{
			for(int x = 0; x < this->width; x++) 
			{
				cgl::Vector3f sum = normals2[z][x];
				
				if (x > 0) 
				{
					sum += normals2[z][x - 1] * FALLOUT_RATIO;
				}
				if (x < this->width - 1) 
				{
					sum += normals2[z][x + 1] * FALLOUT_RATIO;
				}
				if (z > 0) 
				{
					sum += normals2[z - 1][x] * FALLOUT_RATIO;
				}
				if (z < this->length - 1) 
				{
					sum += normals2[z + 1][x] * FALLOUT_RATIO;
				}
				
				if (sum.magnitude() == 0) 
				{
					sum = cgl::Vector3f(0.0f, 1.0f, 0.0f);
				}
				normals[z][x] = sum;
			}
		}
		
		for(int i = 0; i < this->length; i++)
		{
			delete[] normals2[i];
		}
		delete[] normals2;
	}

	Vector3f Terrain::GetNormal(int x, int z)
	{
		return normals[z][x];
	}

	void Terrain::Load(char* filename, float height)
	{
		Image2D* bmp = new Image2D();
		bmp->LoadBMP(filename);
	}

	//Draws the terrain/heightmap using GL TRIANGLE STRIP
	void Terrain::Draw(float scale)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(int z = 0; z < this->length - 1; z++)
		{
			for(int x = 0; x < this->width; x++)
			{
				/*cgl::Vector3f normal = this->normals[x][z];
				glNormal3f(normal[0], normal[1], normal[2]);
				glVertex3f(x, this->heights[x][z], z);
				normal = this->normals[x][z+1];
				glNormal3f(normal[0], normal[1], normal[2]);
				glVertex3f(x, this->GetHeight(x, z+1), z+1);*/

				//Optimized
				glNormal3f(this->normals[x][z].x, this->normals[x][z].y, this->normals[x][z].z);
				glVertex3f(x, this->heights[x][z], z);
				glNormal3f(this->normals[x][z + 1].x, this->normals[x][z + 1].y, this->normals[x][z + 1].y);
				glVertex3f(x, this->heights[x][z+1], z+1);
				//glVertex3f(x, _terrain->getHeight(x,z), z);
				//normal = _terrain->getNormal(x, z+1);
				//glNormal3f(normal[0], normal[1], normal[2]);
				//glVertex3f(x, _terrain->getHeight(x,z+1), z+1);*/
			}
		}
		glEnd();
	}

}