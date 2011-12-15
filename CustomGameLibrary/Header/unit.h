#ifndef _UNIT_H
#define _UNIT_H

#include "model.h"
#include "projectile.h"

namespace cgl
{
	//Class with hitpoints, mana, shield, armor, damage. Normal data for "any" unit
	class DECLARE Unit : public Model
	{
	private:
	public:
		int flyheight;
		int hitpoints;
		int mana;								//Energy, Mana...
		int shield;								
		int armor;								
		int action;								//Action state, 0 is standing still, no updates... 1 is moving, 2 is attacking (and moving)...
		int damage;								//Amount of damage this player currently has
		cgl::Projectile* projectile;
		Unit::Unit();
		Unit::Unit(int hitpoints, int mana, int shield, int armor, int actionstate, int damage);

	};
}

#endif