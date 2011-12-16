#ifndef _PROJECTILEBULLET_H
#define _PROJECTILEBULLET_H
#include "include.h"
#include "opengl.h"
#include "entity.h"
#include "model.h"

namespace cgl
{
	class DECLARE ProjectileBullet : public Entity
	{
	private:
		cgl::Model* bulletmodel;
		float PIdiv180;
		cgl::Vector3f viewdirection;
	public:
		float speed;
		int lifespan;				//How many frames (calls to "Draw()") it lasts
		int playerID;				//Owner of the player that shoots
		int damage;					//Damage the bullet does upon impact
		float size;
		ProjectileBullet::ProjectileBullet();
		void ProjectileBullet::SetModel(cgl::Model* model);
		void ProjectileBullet::Draw();
		void ProjectileBullet::Move();
		void ProjectileBullet::Shoot(cgl::Vector3f startposition, cgl::Vector3f view, int lifespan);
	};
}

#endif