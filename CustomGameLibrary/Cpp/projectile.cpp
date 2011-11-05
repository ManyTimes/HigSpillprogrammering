#include "../Header/projectile.h"

namespace cgl
{

	//Constructor of a projectile takes a model object, a maximum time the projectile will live (time as in number of calls to "draw()"
	//before it is not drawn, maximumRange it reaches based on movespeed per Draw()-call and its arc angle from 0-89
	Projectile::Projectile(cgl::Model3D* modelObject, float projectileSize, int maxTimeToLive, float maximumRange, float projectileArcDegrees, float movespeed)
	{
		this->size = projectileSize;
		this->hasModel = true;
		this->model = modelObject;
		this->maxTimeToLive = maxTimeToLive;
		this->maximumRange = maximumRange;
		this->projectileArc = projectileArcDegrees;
		this->movespeed = movespeed;
		//Initialize other values so they will never contain "trash"
		this->SetPosition(0.0f, 1.0f ,0.0f);
		this->range = 0;
		this->RGB[0] = this->RGB[1] = this->RGB[2] = 1.0f;
		this->damage = 1;
	}

	//Constructor of a projectile takes a color (the projectile is a sphere obj), a maximum time the projectile will live (time as in number of calls to "draw()"
	//before it is not drawn, maximumRange it reaches based on movespeed per Draw()-call and its arc angle from 0-89
	Projectile::Projectile(float RGBcolor[3], float projectileSize,int maxTimeToLive, float maximumRange, float projectileArcDegrees, float movespeed)
	{
		this->hasModel = false;
		this->model = NULL;
		this->maxTimeToLive = maxTimeToLive;
		this->maximumRange = maximumRange;
		this->projectileArc = projectileArcDegrees;
		this->movespeed = movespeed;
		this->RGB[0] = RGBcolor[0];
		this->RGB[1] = RGBcolor[1];
		this->RGB[2] = RGBcolor[2];
		//Initialize other values so they will never contain "trash"
		this->SetPosition(0.0f, 1.0f, 0.0f);
		this->model = NULL;
		this->damage = 1;
	}


	//Call this when a unit shoots       
	//How to convert a viewingAngle 0-360 to a matrix position (x,y,z)?
	void Projectile::Shoot(float unitPositionX, float unitPositionZ, float unitViewingAngle, int damageUponImpact)
	{
		this->SetPosition(unitPositionX, 1.0f, unitPositionZ);
		this->lifetime = this->maxTimeToLive;		  //Lifetime is larger than 0, draw obj.
		this->SetAngles(cgl::Vector3f(0.0f,unitViewingAngle, 0.0f));
		this->viewangle = unitViewingAngle;
		this->damage = damageUponImpact;
	}

	//Call this when a unit shoots
	void Projectile::Shoot(float unitPositionX, float unitPositionY, float unitPositionZ, float unitViewingAngle, int damageUponImpact)
	{
		this->SetPosition(unitPositionX, unitPositionY, unitPositionZ);
		this->lifetime = this->maxTimeToLive;		  //Lifetime is larger than 0, draw obj.
		this->viewangle = unitViewingAngle;
		this->SetAngles(cgl::Vector3f(0.0f,unitViewingAngle, 0.0f));
		this->damage = damageUponImpact;
	}

	void Projectile::Shoot(cgl::Vector3f unitPosition, cgl::Vector3f unitViewingDirection, int damageUponImpact)
	{
		this->SetAngles(unitViewingDirection);
		this->position = unitPosition;	
		this->damage = damageUponImpact;
	}

	void Projectile::Draw()
	{
		if(this->Move() == true)
		{
			if(this->hasModel == true)
			{                                          
				this->model->Draw();  		
			}
			else
			{
				float material[] = {0.50, 0.50, 0.50, 1.0};
				glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
				glutSolidSphere(0.5, this->size, this->size);
				GLfloat bulletlightColor[] = { 1.5f, 1.9f, 1.1f, 1.0f};
				GLfloat bulletlightPos[] = { 0.0f, 5.0f, 0.0f, 1.0f};
				glLightfv(GL_LIGHT4, GL_DIFFUSE, bulletlightColor);
				glLightfv(GL_LIGHT4, GL_POSITION, bulletlightPos);
			}
		}
	}


	bool Projectile::Move()
	{
	  if(this->lifetime > 0 && this->range < this->maximumRange)
	  {
		this->range = this->range + this->movespeed;//Movespeed is number of "floats" forward
		this->position += (this->viewingAngle * this->movespeed);
		this->lifetime --;                         //Number of "frames (calls)" it can live  
		return true;  
	  }
	  return false;
	}

}