#include "../Header/projectilebullet.h"

namespace cgl
{
	//Constructor
	ProjectileBullet::ProjectileBullet()
	{
		this->size = 1;
		this->PIdiv180 = PI / 180;
		this->speed = 1.0f;
		this->lifespan = 0;
		this->playerID = -1;
		this->damage = 0;
		this->bulletmodel = NULL;
	}

	//Functions
	void ProjectileBullet::SetModel(cgl::Model* model)
	{
		this->bulletmodel = model;
	}

	void ProjectileBullet::Draw()
	{
		if(this->lifespan > 0)
		{
			this->Move();
			if(this->bulletmodel == NULL)
			{
				glPushMatrix();
				glTranslatef(position.x, position.y, position.z);
				glutSolidSphere(size, 10, 10);
				glPopMatrix();
			}
			else
			{
				this->bulletmodel->scalingValue = size;
				this->bulletmodel->position.x = this->position.x;
				this->bulletmodel->position.y = this->position.y;
				this->bulletmodel->position.z = this->position.z;
				this->bulletmodel->Draw();
			}
			lifespan -= 1;
		}
	}

	void ProjectileBullet::Move()
	{
		this->position.x = this->position.x + (viewdirection.x * speed);
		this->position.y = this->position.y + (viewdirection.y * speed);
		this->position.z = this->position.z + (viewdirection.z * speed);
		
	}

	void ProjectileBullet::Shoot(cgl::Vector3f startposition, cgl::Vector3f view, int lifespan)
	{
		this->viewdirection.x = view.x;
		this->viewdirection.y = view.y;
		this->viewdirection.z = view.z;
		this->SetPosition(startposition.x, startposition.y, startposition.z);
		this->lifespan = lifespan;
		//Moves two frames behind
		
		//CoutVec(this->position, "pos");
		//CoutVec(this->viewdirection, "view");
	}

}