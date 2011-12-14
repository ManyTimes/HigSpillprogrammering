#ifndef _PLAYER_H
#define _PLAYER_H
#include "include.h"
#include "unit.h"

namespace cgl
{
	class DECLARE Player
	{
	private:
	public:
		int ID;									//A players ID within the game
		//Public data
		Uint8* IPaddress;						//A players own IP adress
		int kills;
		int deaths;
		int score;				
		std::string playername;

		//Constructors
		Player();
		Player(int playerID, std::string playerName);
		~Player();
	};
}//End namespace

#endif