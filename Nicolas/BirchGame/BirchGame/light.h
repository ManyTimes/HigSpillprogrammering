#ifndef LIGHT_H
#define WORLD_H
#include "entity_base.h"

class Light
{
	float x,y,z,w;			// Light position
	// Extra information such as color, attenuation etc later

public:
	Light();
	Light(float x, float y, float z, float w) { this->x = x; this->y = y; this->z = z; this->w = w; }
	Light(float x, float y, float z) { this->x = x; this->y = y; this->z = z; this->w = 0; }
	Light(float light[4]) { x = light[0]; y = light[1]; z = light[2]; w = light[3]; }
	~Light();
	float *GetPosition() { float *p = &x; return p; }
	void SetPosition(float x, float y, float z, float w) { this->x = x; this->y = y; this->z = z; this->w = w;}
	void SetPosition(float x, float y, float z) { this->x = x; this->y = y; this->z = z;}
};
#endif