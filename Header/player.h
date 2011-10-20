#ifndef _PLAYER_H
#define _PLAYER_H
#include "include.h"
#include "birch.h"

namespace cgl
{
	class DECLARE Player : public Birch
	{
	private:
		int numModels;
	public:
		Player();
		~Player();
		void Update();							// Update each frame, (also referred to as the "think" cycle for this class.
	};
}//End namespace

#endif