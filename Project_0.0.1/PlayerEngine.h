#pragma once
#include "Player.h"
#include <string>
#include <sstream>

class PlayerEngine
{
	//Private variables
	Player*& player;
	sf::Vector2u windowSize;

	//GUI
	sf::Font font;
	sf::Text pointsText;
	sf::RectangleShape hpBar, hpBarBack;

public:

	//Public functions
	void Player_Input();
	void update();
	void updateGUI();
	void initPlayer();
	void initGUI();
	void renderGUI(sf::RenderTarget*);

	//Constructor
	PlayerEngine(Player*&, sf::Vector2u);

	//Destructor
	virtual ~PlayerEngine();
};