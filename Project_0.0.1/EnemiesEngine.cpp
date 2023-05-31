#include "EnemiesEngine.h"

void EnemiesEngine::initTextures()
{

	this->textures["INVADER_1_1"] = new sf::Texture();
	this->textures["INVADER_1_1"]->loadFromFile(".\\Textures\\Enemy_Sprites\\invader_1_1.png");

	this->textures["INVADER_1_2"] = new sf::Texture();
	this->textures["INVADER_1_2"]->loadFromFile(".\\Textures\\Enemy_Sprites\\invader_1_2.png");

	this->textures["INVADER_2_1"] = new sf::Texture();
	this->textures["INVADER_2_1"]->loadFromFile(".\\Textures\\Enemy_Sprites\\invader_2_1.png");

	this->textures["INVADER_2_2"] = new sf::Texture();
	this->textures["INVADER_2_2"]->loadFromFile(".\\Textures\\Enemy_Sprites\\invader_2_2.png");

	this->textures["INVADER_3_1"] = new sf::Texture();
	this->textures["INVADER_3_1"]->loadFromFile(".\\Textures\\Enemy_Sprites\\invader_3_1.png");

	this->textures["INVADER_3_2"] = new sf::Texture();
	this->textures["INVADER_3_2"]->loadFromFile(".\\Textures\\Enemy_Sprites\\invader_3_2.png");

	this->textures["INVADER_4_1"] = new sf::Texture();
	this->textures["INVADER_4_1"]->loadFromFile(".\\Textures\\Enemy_Sprites\\invader_4_1.png");

	this->textures["INVADER_4_2"] = new sf::Texture();
	this->textures["INVADER_4_2"]->loadFromFile(".\\Textures\\Enemy_Sprites\\invader_4_2.png");

	this->textures["UFO_1"] = new sf::Texture();
	this->textures["UFO_1"]->loadFromFile(".\\Textures\\Enemy_Sprites\\ufo_1.png");

	this->textures["UFO_2"] = new sf::Texture();
	this->textures["UFO_2"]->loadFromFile(".\\Textures\\Enemy_Sprites\\ufo_2.png");

}

void EnemiesEngine::initVariables()
{
	this->enemyCounter = 60;
	this->movementSpeed - 1.f;
	this->enemiesInWave = 12;
}

void EnemiesEngine::initEnemies()
{
	unsigned width = windowSize.x, height = windowSize.y;

	for (int i = 0; i < enemiesInWave; i++)
	{
		//wave 0
		enemiesRow0->push_back(new Enemy(this->textures["INVADER_2_1"], this->textures["INVADER_2_2"], i * (width * (2.f / 32.f)) + (width * (4.5f / 32.f)), height / 4.f, movementSpeed));
		//wave 1
		enemiesRow1->push_back(new Enemy(this->textures["INVADER_1_1"], this->textures["INVADER_1_2"], i * (width * (2.f / 32.f)) + (width * (4.5f / 32.f)), height / 3.f, movementSpeed));
		//wave 2
		enemiesRow2->push_back(new Enemy(this->textures["INVADER_1_1"], this->textures["INVADER_1_2"], i * (width * (2.f / 32.f)) + (width * (4.5f / 32.f)), height * (15.f / 36.f), movementSpeed));
		//wave 3
		enemiesRow2->push_back(new Enemy(this->textures["INVADER_4_1"], this->textures["INVADER_4_2"], i * (width * (2.f / 32.f)) + (width * (4.5f / 32.f)), height / 2.f, movementSpeed));
		//wave 4
		enemiesRow2->push_back(new Enemy(this->textures["INVADER_3_1"], this->textures["INVADER_3_2"], i * (width * (2.f / 32.f)) + (width * (4.5f / 32.f)), height * (21.f / 36.f), movementSpeed));
	}
}

EnemiesEngine::EnemiesEngine(sf::Vector2u windowSize, std::vector<Enemy*>* row0, std::vector<Enemy*>* row1, std::vector<Enemy*>* row2, std::vector<Enemy*>* row3, std::vector<Enemy*>* row4)
{
	this->initVariables();
	this->initTextures();

	this->windowSize = windowSize;

	this->enemiesRow0 = row0;
	this->enemiesRow1 = row1;
	this->enemiesRow2 = row2;
	this->enemiesRow3 = row3;
	this->enemiesRow4 = row4;
}

EnemiesEngine::~EnemiesEngine()
{
	for (auto& i : this->textures)
	{
		delete i.second;
	}
}
