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
	this->movementSpeed = 0.08f;
	this->enemiesInWave = 12;
	this->direction = 1;
	this->textureChange = 0;
}

void EnemiesEngine::initEnemies()
{
	unsigned width = this->windowSize.x, height = this->windowSize.y;

	for (unsigned i = 0; i < this->enemiesInWave; i++)
	{
		//Resolution is 16:9 
		//So it can be 32:18 / 64:36 for mathematically setting up position on screen
		//wave 0
		enemies->push_back(new Enemy(this->textures["INVADER_2_1"], this->textures["INVADER_2_2"], i * (width * (2.f / 32.f)) + (width * (4.5f / 32.f)), height * (7.f / 36.f), this->movementSpeed));
		//wave 1
		enemies->push_back(new Enemy(this->textures["INVADER_1_1"], this->textures["INVADER_1_2"], i * (width * (2.f / 32.f)) + (width * (4.5f / 32.f)), height * (10.f / 36.f), this->movementSpeed));
		//wave 2
		enemies->push_back(new Enemy(this->textures["INVADER_1_1"], this->textures["INVADER_1_2"], i * (width * (2.f / 32.f)) + (width * (4.5f / 32.f)), height * (13.f / 36.f), this->movementSpeed));
		//wave 3
		enemies->push_back(new Enemy(this->textures["INVADER_4_1"], this->textures["INVADER_4_2"], i * (width * (2.f / 32.f)) + (width * (4.5f / 32.f)), height * (16.f / 36.f), this->movementSpeed));
		//wave 4
		enemies->push_back(new Enemy(this->textures["INVADER_3_1"], this->textures["INVADER_3_2"], i * (width * (2.f / 32.f)) + (width * (4.5f / 32.f)), height * (19.f / 36.f), this->movementSpeed));
	}

	//Default speed to static
	this->enemies[0][0]->setMovementSpeed(this->movementSpeed);
}

void EnemiesEngine::updateEnemies()
{
	srand(time(NULL));
	//Moving waves
	for (auto* enemy : *this->enemies)
	{
		if (enemy->getBoundsHitbox().left <= this->windowSize.x - this->windowSize.x || enemy->getBoundsHitbox().left + enemy->getBoundsHitbox().width >= this->windowSize.x)
		{
			this->direction *= -1;

			for (auto* enemydown : *this->enemies)
			{
				enemydown->move(5.f * this->direction, ((this->windowSize.y * (3.f / 36.f)) / this->movementSpeed) / 3.f);
			}

			return;
		}

		enemy->move(5.f * this->direction, 0.f);

		if (this->textureChange <= 100 && this->textureChange >= (std::rand() % 50) + 50)
		{
			enemy->setTexture(1);
		}

		if (this->textureChange >= (std::rand() % 50) + 150)
		{
			enemy->setTexture(0);
		}
	}

	if (this->textureChange == 200)
	{
		this->textureChange = 0;
	}

	this->textureChange++;

}

EnemiesEngine::EnemiesEngine(sf::Vector2u windowSize, std::vector<Enemy*>* enemies)
{
	this->initVariables();
	this->initTextures();

	this->windowSize = windowSize;

	this->enemies = enemies;
}

EnemiesEngine::~EnemiesEngine()
{
	for (auto& i : this->textures)
	{
		delete i.second;
	}
}