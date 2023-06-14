#pragma once

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Explosion.h"
#include "HiScore.h"

#include "PlayerEngine.h"
#include "CombatEngine.h"
#include "EnemiesEngine.h"
#include "MenuEngine.h"
#include "HiScoreEngine.h"

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
	bool paused, pauseHold;
	bool UserRunGame, userInMenu, UserInHiScore, UserInGameOver;
	bool deathExplosionEnded;
	unsigned* points;

	//Helper engines
	MenuEngine* menuEngine;
	HiScoreEngine* hiScoreEngine;
	PlayerEngine* playerEngine;
	CombatEngine* combatEngine;
	EnemiesEngine* enemiesEngine;

	//Bullets vector
	std::vector<Bullet*> bullets;

	//Enemies vector
	std::vector<Enemy*> enemies;

	//Explosions vector
	std::vector<Explosion*> explosions;

	//Player
	Player* player;

	//Enemy
	Enemy* enemy;
	Enemy* ufo;

	//private functions
	void initVariables();
	void initWindow();

	void initMenu();
	void initHiScore();
	void initPlayer();
	void initEnemy();
	void initCombat();
	void restartInit();
	//void gameOverSequence();

public:
	//Public Functions
	void run();

	void update();
	void updatePollEvents();
	void updateInput();
	void updatePlayer();
	void updateEnemy();
	void updateCombat();

	void updateGame();
	void updateMenu();
	void updateHiScore();

	void render();
	void renderGame();
	void renderMenu();
	void renderHiScore();

	//Constructors
	GameEngine();

	//Destructors
	virtual ~GameEngine();
};

