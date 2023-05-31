#pragma once
#include "Bullet.h"
#include "Player.h"

class BulletsEngine
{
	//Private variables
	std::vector<Bullet*>* bullets;
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

	//Constructor
	BulletsEngine(std::vector<Bullet*>*, Player*);

	//Destructor
	virtual ~BulletsEngine();
};