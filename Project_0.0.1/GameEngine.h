#pragma once

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "PlayerEngine.h"
#include "BulletsEngine.h"
#include "EnemiesEngine.h"

#include <iostream>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class GameEngine
{
	//Private variables
	sf::RenderWindow* window;
	unsigned width, height;

	//Helper engines
	PlayerEngine* playerEngine;
	BulletsEngine* bulletsEngine;
	EnemiesEngine* enemiesEngine;

	//Bullets vector
	std::vector<Bullet*> bullets;

	//Enemies vector
	std::vector<Enemy*> enemiesRow0;
	std::vector<Enemy*> enemiesRow1;
	std::vector<Enemy*> enemiesRow2;
	std::vector<Enemy*> enemiesRow3;
	std::vector<Enemy*> enemiesRow4;

	//Player
	Player* player;

	//Enemy
	Enemy* enemy;

	//private functions
	void initVariables();
	void initWindow();
	void initPlayer();
	void initEnemy();

	void initEngines();

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

