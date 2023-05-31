#pragma once
#include "Enemy.h"

class EnemiesEngine
{
	//Private variables
	unsigned enemyCounter, enemiesInWave;
	float movementSpeed;
	sf::Vector2u windowSize;

	 std::vector<Enemy*>* enemiesRow0;
	 std::vector<Enemy*>* enemiesRow1;
	 std::vector<Enemy*>* enemiesRow2;
	 std::vector<Enemy*>* enemiesRow3;
	 std::vector<Enemy*>* enemiesRow4;

	//Resources
	std::map<std::string, sf::Texture*> textures;

	//Private functions
	void initTextures();
	void initVariables();

public:

	//Public functions
	void initEnemies();

	//Constructor
	EnemiesEngine(sf::Vector2u, std::vector<Enemy*>*, std::vector<Enemy*>*, std::vector<Enemy*>*, std::vector<Enemy*>*, std::vector<Enemy*>*);

	//Destructor
	virtual ~EnemiesEngine();
};

