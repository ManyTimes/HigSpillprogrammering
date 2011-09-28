#ifndef WORLD_H
#define WORLD_H
#include "light.h"
#include <vector>

class World
{
private:
	std::vector<Light*> lights;

	World();
	static World *world;
public:

	static World *GetInstance();
	~World();
	void AddLight(Light *light);
	void RemoveLight(int index);
	Light *GetLight(int index);
	Light *GetLight();					// If no parameter, return the last light added.

};

#endif