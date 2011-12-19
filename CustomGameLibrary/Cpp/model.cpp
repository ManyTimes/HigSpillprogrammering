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
			this->UpdateMatrix();
			if(angleIsOffset)
				this->modelmd2->Draw(this->GetPositionRef(), this->scalingValue, (*GetMatrix() * *GetAngleMatrix()).GetMatrixf());
			else this->modelmd2->Draw(this->GetPositionRef(), this->scalingValue, GetMatrix()->GetMatrixf());
		}
		else
		{
			if(this->modeltype == 2)
			{
				if(angleIsOffset)
					this->model3d->Draw((*GetMatrix() * *GetAngleMatrix()).GetMatrixf());
				else this->model3d->Draw(GetMatrix()->GetMatrixf());
			}
		}
	}

	/////////////////COMMON
	void Model::SetAngleOffsets(float pitch, float yaw, float roll)
	{
		if(pitch == 0 && yaw == 0 && roll == 0)
			angleIsOffset = false;
		else angleIsOffset = true;

		this->angleOffset.x = pitch;
		this->angleOffset.y = yaw;
		this->angleOffset.z = roll;
		UpdateAngleMatrix();
	}

	void Model::SetAngleOffsets(float p[3])
	{
		if(p[0] == 0 && p[1] == 0 && p[2] == 0)
			angleIsOffset = false;
		else angleIsOffset = true;

		this->angleOffset.x = p[0];
		this->angleOffset.y = p[1];
		this->angleOffset.z = p[2];
		UpdateAngleMatrix();
	}

	void Model::SetAngleOffsets(Vector3f p)
	{
		if(p[0] == 0 && p[1] == 0 && p[2] == 0)
			angleIsOffset = false;
		else angleIsOffset = true;

		this->angleOffset = p;
		UpdateAngleMatrix();
	}

	Vector3f Model::GetAngleOffsets()
	{
		return this->angleOffset;
	}

	void Model::UpdateAngleMatrix()
	{
		// Convert to radians for cos and sin functions
		Vector3f r_angles;
		r_angles.x = DEG2RAD(angleOffset.x);
		r_angles.y = DEG2RAD(angleOffset.y);
		r_angles.z = DEG2RAD(angleOffset.z);

		float sa = sin(r_angles.z);
		float ca = cos(r_angles.z);
		float sb = sin(r_angles.x);
		float cb = cos(r_angles.x);
		float sh = sin(r_angles.y);
		float ch = cos(r_angles.y);

		angleMatrix[0] = ch*ca;
		angleMatrix[1] = sa;
		angleMatrix[2] = -sh*ca;

		angleMatrix[4] = -ch*sa*cb + sh*sb;
		angleMatrix[5] = ca*cb;
		angleMatrix[6] = sh*sa*cb + ch*sb;

		angleMatrix[8] = ch*sa*sb + sh*cb;
		angleMatrix[9] = -ca*sb;
		angleMatrix[10] = -sh*sa*sb + ch*cb;

		angleMatrix[3] = 0;
		angleMatrix[7] = 0;
		angleMatrix[11] = 0;
	}

	void Model::SetAngleMatrix(float m[16])
	{
		angleIsOffset = true;			// Not gonna bother checking this, it's not gonna be used by us.
		angleMatrix.SetMatrixf(m);
	}

	void Model::SetAngleMatrix(Matrix m)
	{ 
		angleIsOffset = true;			// Same here.
		angleMatrix.SetMatrixf(m.GetMatrixf());
	}

	Matrix* Model::GetAngleMatrix()
	{
		return &angleMatrix;
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
