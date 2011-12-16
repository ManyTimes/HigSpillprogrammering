#include "../Header/model.h"

namespace cgl
{
	Model::Model()
	{
		this->modeltype = 0;
		this->model3d = NULL;
		this->modelmd2 = NULL;
		this->scalingValue = 1.0f;
	}
	
	void Model::DrawNull()
	{
		
	}

	void Model::Draw()
	{
		if(this->modeltype == 1)
		{
			this->modelmd2->Draw(this->GetPositionRef(), this->scalingValue);
		}
		else
		{
			if(this->modeltype == 2)
			{
				this->model3d->Draw();
			}
		}
	}

	/////////////////MD2 LOADING
	void Model::EnableNormals(bool value)
	{
		if(this->modeltype == 1)
		{
			this->modelmd2->EnableNormals(value);
		}
	}

	void Model::SetAnimation(char* animationName)
	{
		if(this->modeltype == 1)
		{
			this->modelmd2->SetAnimation(animationName);
		}
		else
		{
			cgl::Cout("SetAnimation can only be called on MD2 models");
		}
	}

	void Model::SetAnimation(std::string animationName)
	{
		if(this->modeltype == 1)
		{
			this->modelmd2->SetAnimation((char*)animationName.c_str());
		}
		else
		{
			cgl::Cout("SetAnimation can only be called on MD2 models");
		}
	}

	void Model::Load(char* modelFilenameMD2, GLuint textureID, float animationSpeed)
	{
		if(this->modeltype == 1)
		{
			this->modelmd2->Load(modelFilenameMD2, textureID, animationSpeed);
		}
		else
		{
			if(this->modeltype == 0)
			{
				this->modelmd2 = new ModelMD2(modelFilenameMD2, textureID, animationSpeed);
				this->modeltype = 1;
			}
			else
			{
				cgl::Cout("Cannot load MD2. This object has already been set to a different modeltype");
			}
		}
	}
	void Model::Load(char* modelFilenameMD2, GLuint textureID, float animationSpeed, float normals[])
	{
		if(this->modeltype == 1)
		{
			this->modelmd2->Load(modelFilenameMD2, textureID, animationSpeed);
		}
		else
		{
			if(this->modeltype == 0)
			{
				this->modelmd2 = new ModelMD2(modelFilenameMD2, textureID, animationSpeed);
				this->modeltype = 1;
			}
			else
			{
				cgl::Cout("Cannot load MD2. This object has already been set to a different modeltype");
			}
		}
	}
	Model::Model(char* modelFilenameMD2, GLuint textureID, float animationSpeed)
	{
		this->modelmd2 = new ModelMD2(modelFilenameMD2, textureID, animationSpeed);
		this->modeltype = 1;
		this->scalingValue = 1.0f;
	}

	Model::Model(char* modelFilenameMD2, GLuint textureID, float animationSpeed, float normals[])
	{
		this->modelmd2 = new ModelMD2(modelFilenameMD2, textureID, animationSpeed);
		this->modeltype = 1;
		this->scalingValue = 1.0f;
	}
	/////////////////////// MD2 MODEL END

	////////////////////// 3DS MODEL
	Model::Model(char* modelFilename3DS)
	{
		this->model3d = new Model3D(modelFilename3DS);
		this->modeltype = 2;
		this->scalingValue = 1.0f;
	}
	
	void Model::Load(char* modelFilename3DS)
	{
		if(this->modeltype == 0)
		{
			this->model3d = new Model3D(modelFilename3DS);
			this->modeltype = 2;
		}
		else
		{
			if(this->modeltype == 2)
			{
				this->model3d->Load(modelFilename3DS);
			}
			else
			{
				cgl::Cout("Cannot load 3Ds model, this object has already been set to a different model-file-type");
			}
		}
	}

	void Model::Draw(float modelmatrix[16])
	{
		this->model3d->Draw(modelmatrix);
	}

	void Model::Draw(Matrix modelmatrix)
	{
		this->model3d->Draw(modelmatrix.GetMatrixf());
	}
	/////////////////////// 3DS MODEL END
}
