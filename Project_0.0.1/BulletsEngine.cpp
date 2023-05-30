#include "BulletsEngine.h"

void BulletsEngine::initVariables()
{
	this->hold = false;
	this->hold_aproved = false;
	this->bullet_type = false;
}

void BulletsEngine::initTextures()
{
	this->textures["BULLET_01"] = new sf::Texture();
	this->textures["BULLET_01"]->loadFromFile(".\\Textures\\Laser_Sprites\\11.png");

	this->textures["BULLET_02"] = new sf::Texture();
	this->textures["BULLET_02"]->loadFromFile(".\\Textures\\Laser_Sprites\\12.png");
}

void BulletsEngine::BulletsInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
	{
		if (!this->hold && this->player->readyToShoot())
		{
			if (!hold_aproved)
			{
				this->hold = true;
			}

			if (bullet_type)
			{
				this->bullets->push_back(new Bullet(this->textures["BULLET_01"], this->player->getPos().x, this->player->getPos().y, 0.f, -1.f, 5.f));
				bullet_type = false;
			}
			else
			{
				this->bullets->push_back(new Bullet(this->textures["BULLET_02"], this->player->getPos().x, this->player->getPos().y, 0.f, -1.f, 5.f));
				bullet_type = true;
			}
		}
	}

	else
	{
		this->hold = false;
	}
}

void BulletsEngine::BulletsCulling()
{
	unsigned counter = 0;
	for (auto* bullet : *this->bullets)
	{
		bullet->update();

		//Bullet culling
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete Bullet
			delete this->bullets->at(counter);
			this->bullets->erase(this->bullets->begin() + counter);
			--counter;
		}

		std::cout << "Bullets counter: " << this->bullets->size() << std::endl;

		++counter;
	}
}

BulletsEngine::BulletsEngine(std::vector<Bullet*>* bullets, Player* player)
{
	this->bullets = bullets;
	this->player = player;
	this->initVariables();
	this->initTextures();
}

BulletsEngine::~BulletsEngine()
{
	for (auto& i : this->textures)
	{
		delete i.second;
	}
}