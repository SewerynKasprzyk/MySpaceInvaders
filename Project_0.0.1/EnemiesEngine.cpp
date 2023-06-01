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
	this->speedCounter = this->enemyCounter;
	this->movementSpeed = 0.08f;
	this->enemiesInWave = 12;
	this->textureChange = 0;
	this->direction = 1;
	this->resetTimer = 0;
}

void EnemiesEngine::initEnemies()
{

	//For reseting wave direction
	this->initVariables();

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
	//Must be here to proper initialize it
	this->enemies[0][0]->setMovementSpeed(this->movementSpeed);
}

void EnemiesEngine::updateEnemies()
{
	srand(time(NULL));

	this->enemyCounter = this->enemies->size();

	//Moving waves
	for (auto* enemy : *this->enemies)
	{
		//Change direction if any of enemy touches the left or right border
		//Move down
		//And move to avoid bug
		if (enemy->getBoundsHitbox().left <= this->windowSize.x - this->windowSize.x || enemy->getBoundsHitbox().left + enemy->getBoundsHitbox().width >= this->windowSize.x)
		{
			this->direction *= -1;

			for (auto* enemydown : *this->enemies)
			{
				enemydown->move(5.f * this->direction, ((this->windowSize.y * (3.f / 36.f)) / this->movementSpeed) / 3.f);
			}

			//Break to avoid going out of vector range
			//Don't change break for return in this case!!!
			//There are major operations over loop
			break;
		}

		//Speed up
		if (this->speedCounter / 2 == this->enemyCounter)
		{
			this->speedCounter /= 2;
			this->movementSpeed *= 1.5f;

			//Static set
			enemy->setMovementSpeed(this->movementSpeed);
		}
		

		//Default move
		enemy->move(5.f * this->direction, 0.f);

		//Creates random moment of texture change to improve the animation
		if (this->textureChange <= 100 && this->textureChange >= (std::rand() % 50) + 50)
		{
			enemy->setTexture(1);
		}

		else if (this->textureChange >= (std::rand() % 50) + 150)
		{
			enemy->setTexture(0);
		}	
	}


	//Texture change timer reset
	if (this->textureChange >= 200)
	{
		this->textureChange = 0;
		resetTimer++;
	}

	//Reset wave
	else if (this->enemyCounter == 0)
	{
		if (this->resetTimer >= 10)
		{
			initEnemies();
		}
	}

	else
	{
		this->resetTimer = 0;
	}


	this->textureChange += 1 + 1 * 10 * this->movementSpeed;
	//this->textureChange++;

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