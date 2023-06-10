#pragma once
#include "Player.h"

class PlayerEngine
{
	//Private variables
	Player*& player;
	sf::Vector2u windowSize;

public:

	//Public functions
	void Player_Input();
	void update();
	void initPlayer();

	//Constructor
	PlayerEngine(Player*&, sf::Vector2u);

	//Destructor
	virtual ~PlayerEngine();
};