#include "../Header/projectile.h"


namespace cgl
{

	//Takes a model's filename on your computer, a position (xyz), angle it is viewing and move and missle arc
	Projectile::Projectile(char* modelFilename, cgl::Vector3f position, float angle, float movespeed, float missileArc)
	{
		this->SetModel(modelFilename);
		this->position = position;
		this->angle = angle;
		this->movespeed = movespeed;
		this->missileArc = missileArc;
		this->lifespan = 10;
		this->maximumRange = 10;
	}

	//If lifespan is 0, then there is no checking of lifespan within this class, you have to draw or not draw your self
	//If maximum range is set to 0 or lower, the projectile will forever move in a direction, whenever Draw() is called
	void Projectile::Initialize(float lifespan, float size, int maximumRange)
	{
		this->lifespan = lifespan;
		this->maximumRange = maximumRange;
	}

	//Moves the projectile in 3D space based on angle, movespeed and missilearc
	void Projectile::Move()
	{

	}

	//Draws the 3D model that the projectile has been set to in a 3D space
	void Projectile::Draw()
	{
		
	}

}