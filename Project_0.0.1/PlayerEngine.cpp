#include "PlayerEngine.h"

//Public functions
void PlayerEngine::Player_Input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
	{
		if (false == (this->player->getBounds().left < windowSize.x - windowSize.x))
		{
			this->player->move(-1.f, 0.f);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
	{
		if (false == (this->player->getBounds().left + this->player->getBounds().width > windowSize.x))
		{
			this->player->move(1.f, 0.f);
		}
	}
}

//Constructor
PlayerEngine::PlayerEngine(Player* player, sf::Vector2u windowSize)
{
	this->player = player;
	this->windowSize = windowSize;
}

//Destructor
PlayerEngine::~PlayerEngine()
{
}
