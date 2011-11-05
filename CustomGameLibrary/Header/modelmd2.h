#ifndef _MODELMD2_H
#define _MODELMD2_H
#include "include.h"
#include "mathtool.h"
#include "function.h"
#include "includegl.h"
#include "image2d.h"

namespace cgl
{
	struct MD2Vertex
	{
		cgl::Vector3f position;
		cgl::Vector3f normal;
	};

	struct MD2Frame
	{
		char name[16];
		MD2Vertex* vertices;
	};

	struct MD2TextureCoordinate
	{
		float textureCoordinateX;
		float textureCoordinateY;
	};

	struct MD2Triangle
	{
		int vertices[3];
		int textureCoordinates[3];
	};

	class DECLARE ModelMD2
	{
	private:
		int deltaTime;	//Increases the animation whenever "Draw()" is being called
		//Position of current animation frame, always lies between 0 and 1
		//1 is the endframe, 0 is the starting frame
		float animationTime;
		int firstFrame;
		int lastFrame;
		float* normals;
		GLuint textureID;
		int numberOfFrames;
		int numberOfTriangles;
		MD2TextureCoordinate* textureCoordinate;
		MD2Triangle* triangles;
		MD2Frame* frames;
		int ModelMD2::Bytes4ToInt(const char* bytes);
		short ModelMD2::Bytes2ToShort(const char* bytes);
		bool ModelMD2::isSystemLittleEndian();
		float ModelMD2::Bytes4ToFloat(const char* bytes);
		int ModelMD2::Read4BytesToInt(std::ifstream &input);

		cgl::Vector3f ModelMD2::Read4ToVector3f(std::ifstream &input) ;
		float ModelMD2::Read4ToFloat(std::ifstream &input);
		short ModelMD2::Read2ToShort(std::ifstream &input);
		unsigned short ModelMD2::Read2ToUnsignedShort(std::ifstream &input);
		unsigned short ModelMD2::Bytes2ToUnsignedShort(const char* bytes);
	public:
		ModelMD2::ModelMD2(char* filename, GLuint textureID, float modelNormals[]);
		void ModelMD2::Draw();
		void ModelMD2::SetAnimation(const char* animationName);
		ModelMD2::~ModelMD2();
	};
}

#endif