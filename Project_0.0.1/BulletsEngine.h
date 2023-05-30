#pragma once
#include "Bullet.h"
#include "Player.h"

class BulletsEngine
{
	//Private variables
	std::vector<Bullet*>* bullets;
	Player* player;

	std::map<std::string, sf::Texture*> textures;
	bool hold, hold_aproved, bullet_type;

	//Private functions
	void initVariables();
	void initTextures();

public:

	//Public functions
	void BulletsInput();

	//Constructor
	BulletsEngine(std::vector<Bullet*>*, Player*);

	//Destructor
	virtual ~BulletsEngine();
};

