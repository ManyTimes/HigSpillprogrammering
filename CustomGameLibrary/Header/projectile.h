#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "include.h"
#include "includegl.h"
#include "model3d.h"
#include "entity.h"

namespace cgl
{
	//A projectile has its own 3D model different frmo a unit/player, it has also its own projectile arc and range
	class DECLARE Projectile : public Entity
	{
	private:
		float lifespan;				//When lifespan reaches 0, the projectile is no longer drawn, it is dead.
		int rangeTravelled;			//Increases each time the porjectile is moved
		void Projectile::Move();	//Called within Draw() automatic
	public:
		int maximumRange;			//Maximum range it travels from starting position
		int size;					//Model Size
		float missileArc;
		float movespeed;
		float angle;				//Angle, direction it is moving towards
		Projectile::Projectile(char* modelFilenam, cgl::Vector3f position, float angle, float movespeed, float missileArc);
		void Projectile::Initialize(float lifespan, float size, int maximumRange);
		void Projectile::Draw();
	};
}


#endif