#include "../Header/player.h"

namespace cgl
{
	//Constructors
	Player::Player()
	{
		this->ID = -1;
		this->kills = 0;
		this->deaths = 0;
		this->playername = "";
		this->score = 0;
	}

	Player::Player(int playerID, std::string playerName)
	{
		this->ID = playerID;
		this->playername = playerName;
		this->kills = 0;
		this->deaths = 0;
		this->score = 0;
	}

	Player::~Player()
	{
	}

	

		
}