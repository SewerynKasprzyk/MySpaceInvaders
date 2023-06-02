#pragma once
#include "Enemy.h"
#include <time.h>

class EnemiesEngine
{
	//Private variables
	unsigned enemyCounter, enemiesInWave, speedCounter;
	int direction;
	float movementSpeed;
	sf::Vector2u windowSize;
	int textureChange, resetTimer;

	std::vector<Enemy*>* enemies;

	//Resources
	std::map<std::string, sf::Texture*> textures;

	//Private functions
	void initTextures();
	void initVariables();

public:

	//Public functions
	void initEnemies();
	void updateEnemies();

	//Constructor
	EnemiesEngine(sf::Vector2u, std::vector<Enemy*>*);

	//Destructor
	virtual ~EnemiesEngine();
};

