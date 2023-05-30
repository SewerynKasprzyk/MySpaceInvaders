#pragma once

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

#include <iostream>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class GameEngine
{
	//private variables
	sf::RenderWindow* window;
	unsigned width, height;
	bool hold, hold_aproved, bullet_type;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//Player
	Player* player;
	Enemy* enemy;

	//private functions
	void initVariables();
	void initWindow();
	void initTextures();
	void initPlayer();
	void initEnemy();

public:
	//Public Functions
	void run();
	void update();
	void updatePollEvents();
	void updateInput();
	void updateBullets();
	void updateEnemy();
	void render();

	//Constructors
	GameEngine();

	//Destructors
	virtual ~GameEngine();
};

