#ifndef _BIRCH_H
#define _BIRCH_H

#include "entity.h"
#include "projectile.h"

namespace cgl
{
	class DECLARE Birch : public Entity
	{
	private:
	public:
		int hitpoints;
		int mana;								//Energy, Mana...
		int shield;								
		int armor;								
		int action;								//Action state, 0 is standing still, no updates... 1 is moving, 2 is attacking (and moving)...
		int damage;								//Amount of damage this player currently has
		cgl::Projectile* projectile;
		Birch::Birch();
		Birch::Birch(int hitpoints, int mana, int shield, int armor, int actionstate, int damage);

	};
}

#endif