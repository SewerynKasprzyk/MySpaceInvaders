#include "PlayerEngine.h"

//Public functions
void PlayerEngine::Player_Input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
	{
		this->player->move(-1.f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
	{
		this->player->move(1.f, 0.f);
	}
}

//Constructor
PlayerEngine::PlayerEngine(Player* player)
{
	this->player = player;
}

//Destructor
PlayerEngine::~PlayerEngine()
{
}
