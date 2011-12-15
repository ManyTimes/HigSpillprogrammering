#include "../Header/unit.h"

namespace cgl
{
	//This is a built in unit  within the library, with mana, hit points, etc... You can specify the amount and model.
	Unit::Unit()
	{
		this->flyheight = 0.0f;
	}

	Unit::Unit(int hitpoints, int mana, int shield, int armor, int actionstate, int damage)
	{
		this->hitpoints = hitpoints;
		this->mana = mana;
		this->shield = shield;
		this->armor = armor;
		this->action = actionstate;
		this->damage = damage;
		this->flyheight = 0.0f;
	}
	
}