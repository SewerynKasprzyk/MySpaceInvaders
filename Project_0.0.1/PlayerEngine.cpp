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

void PlayerEngine::update()
{
	this->player->update();
}

void PlayerEngine::updateGUI()
{
	std::stringstream ss;
	ss << "SCORE: " << this->player->getPoints();

	this->pointsText.setString(ss.str());
}

void PlayerEngine::initPlayer()
{
	this->player = new Player(this->windowSize.x, this->windowSize.y);
}

void PlayerEngine::initGUI()
{
	this->pointsText.setPosition(5.f, 5.f);

	this->font.loadFromFile(".\\Fonts\\space_invaders.ttf");
	this->pointsText.setFont(this->font);
	this->pointsText.setCharacterSize(12);
	this->pointsText.setFillColor(sf::Color::White);
	//this->pointsText.setOutlineColor
	//this->pointsText.setOutlineThickness

	this->pointsText.setString("ERROR");
}

void PlayerEngine::renderGUI(sf::RenderTarget* target)
{
	target->draw(this->pointsText);
}

//Constructor
PlayerEngine::PlayerEngine(Player*& player, sf::Vector2u windowSize) : player(player)
{
	this->windowSize = windowSize;
}

//Destructor
PlayerEngine::~PlayerEngine()
{
}
