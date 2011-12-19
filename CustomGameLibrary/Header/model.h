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
		Vector3f angleOffset;						// Euler angles for angle offset, incase the model isn't loaded the way you want it.
		Matrix angleMatrix;							// A matrix that holds the offset corrections. We don't want to mess with the other matrix.
		bool angleIsOffset;							// I want a quick check to see if this is used, if it's not then I don't wanna multiply the angleMatrix each time.
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

		// Common functions
		void Model::SetAngleOffsets(float pitch, float yaw, float roll);
		void Model::SetAngleOffsets(float p[3]);
		void Model::SetAngleOffsets(Vector3f p);
		Vector3f Model::GetAngleOffsets();
		void Model::SetAngleMatrix(float m[16]);
		void Model::SetAngleMatrix(Matrix m);
		Matrix* Model::GetAngleMatrix();
		void Model::UpdateAngleMatrix();

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
		void Model::Draw(Matrix modelmatrix);
		void Model::Load(char* modelFilename3DS);
	};

}
#endif