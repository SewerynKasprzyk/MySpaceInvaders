#pragma once
#include "Player.h"

class PlayerEngine
{
	Player* player;

public:

	void Player_input();

	//Constructor
	PlayerEngine(Player*);

	//Destructor
	virtual ~PlayerEngine();
};