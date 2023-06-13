#pragma once
#include "HiScore.h"

void HiScore::initFont()
{
	this->font.loadFromFile(".\\Fonts\\space_invaders.ttf");
}

void HiScore::initText()
{
	this->nameText.setFont(this->font);
	this->nameText.setFillColor(sf::Color::White);
	this->nameText.setCharacterSize(18);
	this->scoreText = this->nameText;

	this->nameText.setString(this->name);
	this->scoreText.setString(std::to_string(this->score));

	this->nameText.setPosition(this->namePosition);
	this->scoreText.setPosition(this->scorePosition);
}

void HiScore::move(const float movX, const float movY)
{
	this->nameText.move(movX, movY);
	this->scoreText.move(movX, movY);
}

std::ostream& operator<<(std::ostream& output, const HiScore& hiScore)
{
	output << hiScore.name << "|" << hiScore.score << std::endl;
	return output;
}

HiScore::HiScore(unsigned int score, std::string name, sf::Vector2f namePosition, sf::Vector2f scorePosition)
{
	this->score = score;
	this->name = name;
	this->namePosition = namePosition;
	this->scorePosition = scorePosition;

	this->initFont();
	this->initText();
}

HiScore::~HiScore()
{
}
