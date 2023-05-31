#pragma once
#include "Player.h"

class PlayerEngine
{
	//Private variables
	Player* player;

public:

	//Public functions
	void Player_Input();

	//Constructor
	PlayerEngine(Player*);

	//Destructor
	virtual ~PlayerEngine();
};