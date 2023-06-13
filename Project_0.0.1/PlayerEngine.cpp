#pragma once
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

	float hpPercentage = this->player->getHP() / this->player->getHP(true);
	this->hpBar.setScale(hpPercentage, 1.f);
}

void PlayerEngine::initPlayer()
{
	this->player = new Player(this->windowSize.x, this->windowSize.y, sf::Vector2f(this->windowSize));
}

void PlayerEngine::initGUI()
{
	//Score
	this->pointsText.setPosition(5.f, 5.f);

	this->font.loadFromFile(".\\Fonts\\space_invaders.ttf");
	this->pointsText.setFont(this->font);
	this->pointsText.setCharacterSize(16);
	this->pointsText.setFillColor(sf::Color::White);
	//this->pointsText.setOutlineColor
	//this->pointsText.setOutlineThickness

	this->pointsText.setString("ERROR");

	//HP Bar
	this->hpBar.setSize(sf::Vector2f(200.f, 10.f));
	this->hpBar.setOutlineThickness(1.f);
	this->hpBar.setFillColor(sf::Color(209, 52, 52, 255));
	this->hpBar.setOutlineColor(sf::Color(54, 47, 47, 255));
	this->hpBar.setPosition(windowSize.x - windowSize.x + this->hpBar.getGlobalBounds().width / 5.f, windowSize.y - this->hpBar.getGlobalBounds().height * (2.f));

	this->hpBarBack = this->hpBar;
	this->hpBarBack.setFillColor(sf::Color(209, 52, 52, 70));
}

void PlayerEngine::renderGUI(sf::RenderTarget* target)
{
	target->draw(this->pointsText);
	target->draw(this->hpBarBack);
	target->draw(this->hpBar);
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
