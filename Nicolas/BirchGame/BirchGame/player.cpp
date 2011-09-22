#include "player.h"
#include "m_3ds.h"

Player::Player()
{
	model = new M_3DS;
	numModels = 0;
	//Entity_base();
}

Player::~Player()
{
	if(numModels)
	{
		if(model != NULL)		// For now just one model.
			delete model;
	}
}

void Player::Draw()
{
	// Draw all models, might have multiple all together.
	// For now, just one model.
	model->Draw(GetMatrix());		// Pass on the entities position, angles and scale.
}

void Player::Draw(float m[16])
{
	float m2[16];

	std::cout << "Player::Draw(float m[16]) not implemented";
//	m2 = matrix*m; // Combine the matrices
//	model->Draw(m2);
	model->Draw(GetMatrix());
}

bool Player::SetModel(const char *filename)
{
	model->Load(filename);
	return true;
}

void Player::Update()
{
	CheckUpdate();
}