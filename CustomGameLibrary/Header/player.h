#ifndef _PLAYER_H
#define _PLAYER_H
#include "include.h"
#include "birch.h"

namespace cgl
{
	class DECLARE Player : public Birch
	{
	private:
		int numModels;							//Whats this int used for? Hm... :)
	public:
		//Public data
		Uint8* IPaddress;						//A players own IP adress
		int kills;
		int deaths;
		std::string playername;
		//Constructors
		Player();
		~Player();
		void Update();							// Update each frame, (also referred to as the "think" cycle for this class.
	};
}//End namespace

#endif