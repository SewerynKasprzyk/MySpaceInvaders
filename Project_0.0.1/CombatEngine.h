#pragma once
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"

class CombatEngine
{
	//Private variables
	std::vector<Bullet*>* bullets;
	std::vector<Enemy*>* enemies;
	Player* player;
	bool hold, hold_aproved, bullet_type;

	//Resources
	std::map<std::string, sf::Texture*> textures;

	//Private functions
	void initVariables();
	void initTextures();

public:

	//Public functions
	void BulletsInput();
	void BulletsCulling();
	void BulletsEnemyHit();

	//Constructor
	CombatEngine(std::vector<Bullet*>*, std::vector<Enemy*>*, Player*);

	//Destructor
	virtual ~CombatEngine();
};