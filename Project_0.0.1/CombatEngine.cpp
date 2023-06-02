#include "CombatEngine.h"

void CombatEngine::initVariables()
{
	this->hold = false;
	this->hold_aproved = false;
	this->bullet_type = false;
	this->points = 0;
	this->readyToShoot = 0.f;
}

void CombatEngine::initTextures()
{
	this->textures["BULLET_01"] = new sf::Texture();
	this->textures["BULLET_01"]->loadFromFile(".\\Textures\\Laser_Sprites\\11.png");

	this->textures["BULLET_02"] = new sf::Texture();
	this->textures["BULLET_02"]->loadFromFile(".\\Textures\\Laser_Sprites\\12.png");

	this->textures["ENEMY_BULLET_01"] = new sf::Texture();
	this->textures["ENEMY_BULLET_01"]->loadFromFile(".\\Textures\\Laser_Sprites\\35.png");
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
		if (bullet->getBounds().top + bullet->getBounds().height < windowSize.y - windowSize.y || bullet->getBounds().top > windowSize.y)
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
			if (bullet->getBounds().intersects(enemy->getBoundsHitbox()) && bullet->isEnemyBullet() == false)
			{
				enemy->damageEnemy(bullet->getDamage());

				if (enemy->getHP() <= 0)
				{
					//Delete enemy and add points
					this->points += enemy->getPoints();
					delete this->enemies->at(i);
					this->enemies->erase(this->enemies->begin() + i);

					//Bug fix for going out of vector range
					//break wont work becouse there are two vectors where data has been deleted
					return;
				}

				//Delete bullet
				delete this->bullets->at(j);
				this->bullets->erase(this->bullets->begin() + j);

				return;
			}

			j++;
		}

		i++;
	}

}

void CombatEngine::BulletsPlayerHit()
{
	unsigned int i = 0;

	for (auto* bullet : *this->bullets)
	{
		if (bullet->getBounds().intersects(this->player->getBounds()) && bullet->isEnemyBullet() == true)
		{
			this->player->damagePlayer(bullet->getDamage());
			delete this->bullets->at(i);
			this->bullets->erase(this->bullets->begin() + i);
			return;
		}

		i++;
	}
}

void CombatEngine::enemyIntersectPlayer()
{
	unsigned int i = 0;

	for (auto* enemy : *this->enemies)
	{
		if (enemy->getBoundsHitbox().intersects(this->player->getBounds()))
		{
			this->player->damagePlayer(enemy->getHP());
			delete this->enemies->at(i);
			this->enemies->erase(this->enemies->begin() + i);
			return;
		}

		i++;
	}
}

void CombatEngine::enemyShoot()
{
	srand(time(NULL));
	this->readyToShoot += 1 + float((std::rand() % 100)) / 100.f;

	if (this->readyToShoot >= 500 && this->enemies->size() > 0)
	{
		Enemy enemy = *this->enemies->at(std::rand() % (this->enemies->size()));
		this->bullets->push_back(new Bullet(this->textures["ENEMY_BULLET_01"], enemy.getBoundsHitbox().left + (enemy.getBoundsHitbox().width / 2.f), enemy.getBoundsHitbox().top + (enemy.getBoundsHitbox().height / 2.f), 0.f, 1.f, 1.5f, 20.f));
		this->readyToShoot = 0.f;
	}
}

CombatEngine::CombatEngine(sf::Vector2u windowSize, std::vector<Bullet*>* bullets, std::vector<Enemy*>* enemies, Player* player)
{
	this->bullets = bullets;
	this->enemies = enemies;
	this->player = player;
	this->initVariables();
	this->initTextures();
	this->windowSize = windowSize;
}

CombatEngine::~CombatEngine()
{
	for (auto& i : this->textures)
	{
		delete i.second;
	}
}