#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <string>
#include <sstream>

class HiScore
{
	//Private variables
	unsigned int score;
	std::string name;
	sf::Vector2f scorePosition, namePosition;

	sf::Font font;
	sf::Text scoreText, nameText;

	//Private functions
	void initFont();
	void initText();

public:

	//Public functions
	void move(const float, const float);
	void render(sf::RenderTarget*);
	void colorize(sf::Color);

	//Constructor
	HiScore(unsigned int, std::string, sf::Vector2f, sf::Vector2f);

	//Destructor
	virtual ~HiScore();
};