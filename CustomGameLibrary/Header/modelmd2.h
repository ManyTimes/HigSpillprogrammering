#ifndef _MODELMD2_H
#define _MODELMD2_H
#include "function.h"
#include "includegl.h"
#include "entity.h"
#include "image2d.h"

namespace cgl
{
	struct MD2Vertex
	{
		cgl::Vector3f pos;
		cgl::Vector3f normal;
	};

	struct MD2Frame 
	{
		char name[16];
		MD2Vertex* vertices;
	};

	struct MD2TexCoord 
	{
		float texCoordX;
		float texCoordY;
	};

	struct MD2Triangle 
	{
		int vertices[3];  //The indices of the vertices in this triangle
		int texCoords[3]; //The indices of the texture coordinates of the triangle
	};

	class DECLARE ModelMD2 //: public Entity
	{
		private:				//Privates that are used only once should not be members, clean it up? :(
			std::ifstream file;
			bool useNormals;
			int firstFrame;		//First frame of current animation
			int lastFrame;		//Last frame of current animation
			int numberOfFrames;	//Frames in animation
			int numberOfTriangles;
			MD2TexCoord* textureCoordinates;
			MD2Triangle* triangles;
			MD2Frame* frames;
			float animationSpeed;
			float time;
			GLuint textureID;
			float* normals;
			void Animate();
			bool Initialize();
			float ModelMD2::toFloat(const char* bytes);
			float ModelMD2::readFloat(std::ifstream &input);
			int ModelMD2::toInt(const char* bytes);
			int ModelMD2::readInt(std::ifstream &input);
			unsigned short ModelMD2::toUShort(const char* bytes);
			unsigned short ModelMD2::readUShort(std::ifstream &input);
			short ModelMD2::toShort(const char* bytes);
			short ModelMD2::readShort(std::ifstream &input);
			cgl::Vector3f ModelMD2::readVec3f(std::ifstream &input);
		public:
			std::string animations;
			ModelMD2::ModelMD2();
			ModelMD2::ModelMD2(char* modelFilename, GLuint textureID, float normals[], float animationSpeed);
			ModelMD2::ModelMD2(char* modelFilename, GLuint textureID, float animationSpeed);
			ModelMD2::~ModelMD2();
			void ModelMD2::Load(char* modelFileName, GLuint textureID, float normals[], float animationSpeed);
			void ModelMD2::Load(char* modelFileName, GLuint textureID, float animationSpeed);
			void ModelMD2::SetAnimation(char* animationName);
			//void ModelMD2::Draw();
			void ModelMD2::Draw(cgl::Vector3f& position, float& scale, float *m = NULL);
			void ModelMD2::EnableNormals(bool value);
	};
}

#endif