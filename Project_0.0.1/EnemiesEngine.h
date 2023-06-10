#pragma once
#include "Enemy.h"
#include <time.h>

class EnemiesEngine
{
	//Private variables
	unsigned int enemyCounter, enemiesInWave, speedCounter, textureChange, ufoTextureChange, resetTimer, ufoSpawnTimer;
	int direction;
	float movementSpeed;
	sf::Vector2u windowSize;
	std::vector<Enemy*>& enemies;
	Enemy*& ufo;

	//Resources
	std::map<std::string, sf::Texture*> textures;

	//Private functions
	void initTextures();
	void initVariables();

public:

	//Public functions
	void initEnemies();
	void SpawnUfo();
	void updateEnemies();
	void ufoUpdate();

	//Constructor
	EnemiesEngine(sf::Vector2u, std::vector<Enemy*>&, Enemy*&);

	//Destructor
	virtual ~EnemiesEngine();
};

