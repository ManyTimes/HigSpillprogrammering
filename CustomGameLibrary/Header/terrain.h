#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "include.h"
#include <stdlib.h>
#include <iostream>
#include "includegl.h"
#include "mathtool.h"
#include "image2d.h"

namespace cgl
{
	class DECLARE Terrain
	{
	private:
		int width;						//Width of terrain
		int length;						//Length of terrain
		Vector3f** normals;				//X-Z of normals in a 2D which contains a XYZ value for 3D
		float** heights;				//Heights
	public:
		Terrain::Terrain(char* heightMapTexture, float maximumTerrainHeight);
		Terrain::~Terrain();
		void Terrain::Load(char* filename, float height);
		int Terrain::GetWidth();
		int Terrain::GetLength();
		void Terrain::SetHeight(int x, int z, float y);
		float Terrain::GetHeight(int x, int z);
		void Terrain::ComputeNormals();
		Vector3f Terrain::GetNormal(int x, int z);
		void Terrain::Draw(float scale);
	};
}

#endif