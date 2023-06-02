#include "CombatEngine.h"

void CombatEngine::initVariables()
{
	this->hold = false;
	this->hold_aproved = false;
	this->bullet_type = false;
}

void CombatEngine::initTextures()
{
	this->textures["BULLET_01"] = new sf::Texture();
	this->textures["BULLET_01"]->loadFromFile(".\\Textures\\Laser_Sprites\\11.png");

	this->textures["BULLET_02"] = new sf::Texture();
	this->textures["BULLET_02"]->loadFromFile(".\\Textures\\Laser_Sprites\\12.png");
}

void CombatEngine::BulletsInput()
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
				this->bullets->push_back(new Bullet(this->textures["BULLET_01"], this->player->getPos().x + (this->player->getBounds().width / 2.f), this->player->getPos().y + (this->player->getBounds().height / 2.f), 0.f, -1.f, this->player->getBulletSpeed(), this->player->getDamage()));
				bullet_type = false;
			}
			else
			{
				this->bullets->push_back(new Bullet(this->textures["BULLET_02"], this->player->getPos().x + (this->player->getBounds().width/2.f), this->player->getPos().y + (this->player->getBounds().height/2.f), 0.f, -1.f, this->player->getBulletSpeed(), this->player->getDamage()));
				bullet_type = true;
			}
		}
	}

	else
	{
		this->hold = false;
	}
}

void CombatEngine::BulletsCulling()
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

void CombatEngine::BulletsEnemyHit()
{
	unsigned int i = 0;

	for (auto* enemy : *this->enemies)
	{
		unsigned int j = 0;

		for (auto* bullet : *this->bullets)
		{
			if (bullet->getBounds().intersects(enemy->getBoundsHitbox()))
			{
				enemy->damageEnemy(bullet->getDamage());

				if (enemy->getHP() <= 0)
				{
					delete this->enemies->at(i);
					this->enemies->erase(this->enemies->begin() + i);

					//Bug fix for going out of vector range
					//break wont work becouse there are two vectors where data has been deleted
					return;
				}

				delete this->bullets->at(j);
				this->bullets->erase(this->bullets->begin() + j);

				return;
			}

			j++;
		}

		i++;
	}

}

CombatEngine::CombatEngine(std::vector<Bullet*>* bullets, std::vector<Enemy*>* enemies, Player* player)
{
	this->bullets = bullets;
	this->enemies = enemies;
	this->player = player;
	this->initVariables();
	this->initTextures();
}

CombatEngine::~CombatEngine()
{
	for (auto& i : this->textures)
	{
		delete i.second;
	}
}