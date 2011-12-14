#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "include.h"
#include "includegl.h"
#include "model3d.h"
#include "modelmd2.h"
#include "entity.h"
#include "mathtool.h"

namespace cgl
{
	//A projectile has its own 3D model different frmo a unit/player, it has also its own projectile arc and range
	class DECLARE Projectile : public Entity
	{
	private:
		bool hasModel;
		int lifetime;				//Life span left of the projectile to live, if projectile hits soemthing, set this to 0
		int maxTimeToLive;			
		cgl::Model3D* model;		//THe projectile modelfile
		cgl::ModelMD2* modelMD;		//The projectile modelfile of MD2 type
		float maximumRange;			//Max range the projectile can move before not drawn
		float range;				//Current range the projectile has moved, if it hits objects, set this to 0
		float RGB[3];				//Colors of the projectile
		bool Projectile::Move();	//Called within Draw() automatic
	public:
		float viewingAngle;			//Current angle the projectile is currently moving towards
		int damage;					//Damage the projectile can do upon hit
		float size;					//Size of the projectile, how large scale it is been drawn to
		float projectileArc;		//The missile arc of the projectile, while flying in air
		float movespeed;			//Number of coordinates it moves each time "draw()" is called
		Projectile::Projectile();
		Projectile::Projectile(float RGBcolor[3], float projectileSize,int maxTimeToLive, float maximumRange, float projectileArcDegress, float movespeed);
		Projectile::Projectile(cgl::Model3D* modelObject, float projectileSize, int maxTimeToLive, float maximumRange, float projectileArcDegress, float movespeed);
		Projectile::Projectile(cgl::ModelMD2* modelMD2Object, float projectileSize, int maxTimeToLive, float maximumRange, float projectileArcDegress, float movespeed);
		void Projectile::Shoot(float unitPositionX, float unitPositionZ, float unitViewingAngle, int damageUponImpact);
		void Projectile::Shoot(float unitPositionX, float unitPositionY, float unitPositionZ, float unitViewingAngle, int damageUponImpact);
		void Projectile::Shoot(cgl::Vector3f unitPosition, cgl::Vector3f unitViewingDirection, int damageUponImpact);
		void Projectile::Draw();
	};
}


#endif