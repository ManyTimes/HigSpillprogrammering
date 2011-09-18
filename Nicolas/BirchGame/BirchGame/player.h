#ifndef _PLAYER_H
#define _PLAYER_H
#include "entity_base.h"
#include "m_3ds.h"

class Player : public Entity_base
{
	M_3DS *model;
	int numModels;

public:
	Player();
	~Player();
	void Draw();
	void Draw(float m[16]);
	bool SetModel(const char* filename);
};
#endif