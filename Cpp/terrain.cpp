#include "../Header/terrain.h"

namespace cgl
{
	//Tar et bitmap...heightmap...BMP fil og lagrer height, width, length
	//Deretter sletter bildet, og terrenget er lagret i xyz plan
	//Kan kanskje også ta en texture, tga/bmp ...som ikke blir kastet, men
	//som blir bindet før tegning/rednering av terreng, nice nice
	Terrain::Terrain(int terrainWidth, int terrainLength)
	{
		width = terrainWidth;
		length = terrainLength;
		heights = new float*[length];		//X-Z plane
		for(int i = 0; i < length; i++)
		{
			heights[i] = new float[width];
		}
		normals = new Vector3f*[length];	//Normals in x-zplane
		for(int i = 0; i < length;i++)
		{	
			normals[i] = new Vector3f[width];
		}
		computedNormals = false;
	}

	Terrain::~Terrain()
	{
		for(int i = 0; i < length; i++)
		{
			delete[] heights[i];
		}
		delete[] heights;
		for(int i = 0; i < length; i++)
		{
			delete[] normals[i];
		}
		delete[] normals;
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

	void Terrain::ComputeNormals()
	{
		if(computedNormals == false)
		{
			computedNormals = true;
			//Compute the rough version of the normals
			Vector3f** normals2 = new Vector3f*[length];
			for(int i = 0; i < length; i++) 
			{
				normals2[i] = new Vector3f[width];
			}
			for(int z = 0; z < length; z++) 
			{
				for(int x = 0; x < width; x++) 
				{
					Vector3f sum(0.0f, 0.0f, 0.0f);
					
					Vector3f out;
					if (z > 0) 
					{
						out = Vector3f(0.0f, heights[z - 1][x] - heights[z][x], -1.0f);
					}
					Vector3f in;
					if (z < length - 1) 
					{
						in = Vector3f(0.0f, heights[z + 1][x] - heights[z][x], 1.0f);
					}
					Vector3f left;
					if (x > 0) 
					{
						left = Vector3f(-1.0f, heights[z][x - 1] - heights[z][x], 0.0f);
					}
					Vector3f right;
					if (x < width - 1) 
					{
						right = Vector3f(1.0f, heights[z][x + 1] - heights[z][x], 0.0f);
					}
					if (x > 0 && z > 0) 
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
					}
					normals2[z][x] = sum;
				}
			}

			//Smooth out the normals
			const float FALLOUT_RATIO = 0.5f;
			for(int z = 0; z < length; z++) 
			{
				for(int x = 0; x < width; x++) 
				{
					Vector3f sum = normals2[z][x];
					
					if (x > 0)
					{
						sum += normals2[z][x - 1] * FALLOUT_RATIO;
					}
					if (x < width - 1) 
					{
						sum += normals2[z][x + 1] * FALLOUT_RATIO;
					}
					if (z > 0) 
					{
						sum += normals2[z - 1][x] * FALLOUT_RATIO;
					}
					if (z < length - 1) 
					{
						sum += normals2[z + 1][x] * FALLOUT_RATIO;
					}
					
					if (sum.magnitude() == 0) 
					{
						sum = Vector3f(0.0f, 1.0f, 0.0f);
					}
					normals[z][x] = sum;
				}
			}
			
			for(int i = 0; i < length; i++)
			{
				delete[] normals2[i];
			}
			delete[] normals2;
		}
	}

	Vector3f Terrain::GetNormal(int x, int z)
	{
		if(!computedNormals)
		{
			ComputeNormals();
		}
		return normals[z][x];
	}

	void Terrain::Load(char* filename, float height)
	{
		Image2D* bmp = new Image2D();
		bmp->LoadBMP(filename);

	}
}