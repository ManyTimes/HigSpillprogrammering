#ifndef _MODEL_H
#define _MODEL_H

#include "modelmd2.h"
#include "model3d.h"

namespace cgl
{
	class DECLARE Model : public Entity
	{
	private:
		int modeltype;								//ModelMD2 == 1, Model3D = 2, no model set/loaded = 0
		ModelMD2* modelmd2;
		Model3D* model3d;
		void (*CallbackDraw)(void);					//Pointers to functions within the model to be drawn	
		void (*CallbackLoad)(void);
		void (*CallbackSetAnimation)(char*);
		void Model::DrawNull();
	public:
		float scalingValue;
		Model::Model();
		void Model::Draw();
		/*void Model::Load();
		void Model::SetAnimation(std::string animationName);
		void Model::SetAnimation(char* animationName);
		void Model::Draw();
		void Model::Draw(float matrix[16]);*/

		//MD2 FUNCTIONS
		Model::Model(char* modelFilenameMD2, GLuint textureID, float animationSpeed);
		Model::Model(char* modelFilenameMD2, GLuint textureID, float animationSpeed, float normals[]);
		void Model::EnableNormals(bool value);
		void Model::SetAnimation(char* animationName);
		void Model::SetAnimation(std::string animationName);
		void Model::Load(char* modelFilenameMD2, GLuint textureID, float animationSpeed);
		void Model::Load(char* modelFilenameMD2, GLuint textureID, float animationSpeed, float normals[]);
		//3DS FUNCTIONS
		Model::Model(char* modelFilename3DS);
		void Model::Draw(float modelmatrix[16]);
		void Model::Load(char* modelFilename3DS);
	};

}
#endif