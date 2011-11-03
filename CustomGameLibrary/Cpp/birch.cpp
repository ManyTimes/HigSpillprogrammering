#include "../Header/birch.h"

namespace cgl
{
	//This is a built in unit  within the library, with mana, hit points, etc... You can specify the amount and model.
	Birch::Birch()
	{
	}

	Birch::Birch(int hitpoints, int mana, int shield, int armor, int actionstate, int damage)
	{
		this->hitpoints = hitpoints;
		this->mana = mana;
		this->shield = shield;
		this->armor = armor;
		this->action = actionstate;
		this->damage = damage;
	}
}