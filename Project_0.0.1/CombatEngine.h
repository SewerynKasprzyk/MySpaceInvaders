#pragma once
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Explosion.h"

class CombatEngine
{
	//Private variables
	sf::Vector2u windowSize;

	std::vector<Bullet*>& bullets;
	std::vector<Enemy*>& enemies;
	std::vector<Explosion*>& explosions;

	Player* player;
	Enemy*& ufo;
	bool hold, hold_aproved, bullet_type;
	int points, sequenceTimer, sequenceTimerMax;
	float readyToShoot;

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
	void BulletsPlayerHit();
	void enemyIntersectPlayer();
	void enemyShoot();
	void explosionsRelease();
	void playerDeathExplosionSequence();

	//Constructor
	CombatEngine(sf::Vector2u, std::vector<Bullet*>&, std::vector<Enemy*>&, Player*, Enemy*&, std::vector<Explosion*>&);

	//Destructor
	virtual ~CombatEngine();
};