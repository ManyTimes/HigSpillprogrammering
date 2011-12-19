#include "../Header/projectilearc.h"

namespace cgl
{
	ProjectileArc::ProjectileArc(Vector3f start, Vector3f speed, projectileType type)
	{
		SetPosition(start);
		this->velocity = speed;
		this->moveType = type;
		this->model = NULL;
	}

	ProjectileArc::ProjectileArc()
	{
		this->velocity.x = this->velocity.y = this->velocity.z = 0;
		this->moveType = ARC;
		this->model = NULL;
	}

	void ProjectileArc::Initialize(Vector3f start, Vector3f speed, projectileType type)
	{
		SetPosition(start);
		this->velocity = speed;
		this->moveType = type;
	}

	ProjectileArc::~ProjectileArc()
	{
		delete model;
	}

	void ProjectileArc::Move(float gravity)
	{
		switch( moveType )
		{
		case ARC:
				AddPosition(velocity);
				velocity.y -= gravity;
				break;
		default: 
			std::cout << "Unknown Projectile Type\n";
			break;
		}
	}

	void ProjectileArc::SetModel(Model *model)
	{
		this->model = model;
	}

	void ProjectileArc::Draw()
	{
		if(model)
			model->Draw();
		else cgl::Cout("Drawing a projectileArc without a model");
	}
}