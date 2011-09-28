#include "world.h"
#include <iostream>
#include "common.h"

World::World()
{

}

World::~World()
{
	//for (std::vector<Light*>::iterator it = lights.begin(); it!=lights.end(); ++it) {
	//	delete *it;
	//}
}

// Initialize the singleton object:
World *World::world = NULL;

World *World::GetInstance()
{
	if(!world)
	{
		world = new World();
	}
	return world;
}

void World::AddLight(Light *light)
{
	if(lights.size() == MAX_LIGHTS)
	{
		std::cout << "Max number of lights hit. (MAX_LIGHTS = " << MAX_LIGHTS << ")\n";
		return;
	}
	lights.push_back(light);
}

void World::RemoveLight(int index)
{
	if(index > lights.size())
	{
		std::cout << "Tried to remove light #" << index << " while size is " << lights.size() << std::endl;
		return;
	}

	lights.erase(lights.begin()+index);
}

Light *World::GetLight(int index)
{
	if(index >= lights.size())
	{
		std::cout << "GetLight() failed, index out of range ( " << index << " of " << lights.size() << ")\n";
		return NULL;
	}
	return lights[index];
}

Light *World::GetLight()
{
	if(lights.empty())
	{
		std::cout << "GetLight() failed, there are no lights.\n";
		return NULL;
	}
	return lights.back();
}