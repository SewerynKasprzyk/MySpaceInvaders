#include "CombatEngine.h"

void CombatEngine::initVariables()
{
	this->hold = false;
	this->hold_aproved = false;
	this->bullet_type = false;
	this->points = 0;
	this->readyToShoot = 0.f;
	this->sequenceTimerMax = 100.f;
	this->sequenceTimer = this->sequenceTimerMax;
}

void CombatEngine::initTextures()
{
	this->textures["BULLET_01"] = new sf::Texture();
	this->textures["BULLET_01"]->loadFromFile(".\\Textures\\Laser_Sprites\\11.png");

	this->textures["BULLET_02"] = new sf::Texture();
	this->textures["BULLET_02"]->loadFromFile(".\\Textures\\Laser_Sprites\\12.png");
	
	this->textures["ENEMY_BULLET_01"] = new sf::Texture();
	this->textures["ENEMY_BULLET_01"]->loadFromFile(".\\Textures\\Laser_Sprites\\35.png");

	this->textures["EXPLOTA_01"] = new sf::Texture();
	this->textures["EXPLOTA_01"]->loadFromFile(".\\Textures\\Explota_Sprites\\explota_1.png");

	this->textures["EXPLOTA_02"] = new sf::Texture();
	this->textures["EXPLOTA_02"]->loadFromFile(".\\Textures\\Explota_Sprites\\explota_2.png");

	this->textures["EXPLOTA_03"] = new sf::Texture();
	this->textures["EXPLOTA_03"]->loadFromFile(".\\Textures\\Explota_Sprites\\explota_3.png");
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
				this->bullets.push_back(new Bullet(this->textures["BULLET_01"], this->player->getPos().x + (this->player->getBounds().width / 2.f), this->player->getPos().y + (this->player->getBounds().height / 2.f), 0.f, -1.f, this->player->getBulletSpeed(), this->player->getDamage()));
				bullet_type = false;
			}
			else
			{
				this->bullets.push_back(new Bullet(this->textures["BULLET_02"], this->player->getPos().x + (this->player->getBounds().width/2.f), this->player->getPos().y + (this->player->getBounds().height/2.f), 0.f, -1.f, this->player->getBulletSpeed(), this->player->getDamage()));
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
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling
		if (bullet->getBounds().top + bullet->getBounds().height < windowSize.y - windowSize.y || bullet->getBounds().top > windowSize.y)
		{
			//Delete Bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		std::cout << "Bullets counter: " << this->bullets.size() << std::endl;

		++counter;
	}
}

void CombatEngine::BulletsEnemyHit()
{
	unsigned int i = 0;
	for (auto* bullet : this->bullets)
	{
		unsigned int j = 0;

		for (auto* enemy : this->enemies)
		{
			//Enemy got hit
			if (bullet->getBounds().intersects(enemy->getBoundsHitbox()) && bullet->isEnemyBullet() == false)
			{
				enemy->damageEnemy(bullet->getDamage());
				enemy->hit(sf::Vector2f(0.f, this->windowSize.y * (1.f/100.f)));

				//Enemy death
				if (enemy->getHP() <= 0)
				{
					//Create explosion
					this->explosions.push_back(new Explosion(this->textures["EXPLOTA_01"], this->textures["EXPLOTA_02"], this->textures["EXPLOTA_03"], enemy->getBoundsSprite()));

					//Delete enemy and add points
					this->points += enemy->getPoints();
					delete this->enemies.at(j);
					this->enemies.erase(this->enemies.begin() + j);

					//Bug fix for going out of vector range
					//break wont work becouse there are two vectors where data has been deleted
					return;
				}

				//Delete bullet
				delete this->bullets.at(i);
				this->bullets.erase(this->bullets.begin() + i);

				//Same case as upper bug
				return;
			}

			enemy->hitRealease(sf::Vector2f(0.f, this->windowSize.y * (1.f / 100.f)));

			j++;
		}

		//Ufo hit
 		if (this->ufo != nullptr && (bullet->getBounds().intersects(this->ufo->getBoundsSprite()) && bullet->isEnemyBullet() == false))
		{
			this->ufo->damageEnemy(bullet->getDamage());
			this->ufo->hit(sf::Vector2f(0.f, this->windowSize.y * (1.f / 100.f)));

			if (this->ufo->getHP() <= 0)
			{
				//Create explosion
				this->explosions.push_back(new Explosion(this->textures["EXPLOTA_01"], this->textures["EXPLOTA_02"], this->textures["EXPLOTA_03"], this->ufo->getBoundsSprite()));

				//Add points and delete ufo
				this->points += this->ufo->getPoints();
				delete this->ufo;
				this->ufo = nullptr;

				//Same case as upper bug
				return;
			}

			//Delete bullet
			delete this->bullets.at(i);
			this->bullets.erase(this->bullets.begin() + i);

			//Same case as upper bug
			return;
		}

		if (this->ufo != nullptr)
		{
			this->ufo->hitRealease(sf::Vector2f(0.f, this->windowSize.y * (1.f / 100.f)));
		}

		i++;
	}

}

void CombatEngine::BulletsPlayerHit()
{
	unsigned int i = 0;

	for (auto* bullet : this->bullets)
	{
		if (bullet->getBounds().intersects(this->player->getBounds()) && bullet->isEnemyBullet() == true)
		{
			this->player->damagePlayer(bullet->getDamage());

			//TO DO PLAYER DEATH

			if (this->player->getHP() <= 0)
			{
				this->player->killPlayer();
			}

			delete this->bullets.at(i);
			this->bullets.erase(this->bullets.begin() + i);
			return;
		}

		i++;
	}
}

void CombatEngine::enemyIntersectPlayer()
{
	unsigned int i = 0;

	for (auto* enemy : this->enemies)
	{
		if (enemy->getBoundsHitbox().intersects(this->player->getBounds()))
		{
			this->player->damagePlayer(enemy->getHP());
			delete this->enemies.at(i);
			this->enemies.erase(this->enemies.begin() + i);
			return;
		}

		i++;
	}
}

void CombatEngine::enemyShoot()
{
	srand(time(NULL));
	this->readyToShoot += 1 + float((std::rand() % 100)) / 100.f;

	if (this->readyToShoot >= 500 && this->enemies.size() > 0)
	{
		Enemy enemy = *this->enemies.at(std::rand() % (this->enemies.size()));
		this->bullets.push_back(new Bullet(this->textures["ENEMY_BULLET_01"], enemy.getBoundsHitbox().left + (enemy.getBoundsHitbox().width / 2.f), enemy.getBoundsHitbox().top + (enemy.getBoundsHitbox().height / 2.f), 0.f, 1.f, 1.5f, 20.f));
		this->readyToShoot = 0.f;
	}
}

void CombatEngine::explosionsRelease()
{
	unsigned i = 0;

	for (auto* explosion : this->explosions)
	{
		if (explosion->explosionRelease() == true)
		{
			delete this->explosions.at(i);
			this->explosions.erase(this->explosions.begin() + i);
			return;
		}

		i++;
	}
}

void CombatEngine::playerDeathExplosionSequence()
{
	--this->sequenceTimer;
	sf::RectangleShape puppet;

	if (this->sequenceTimer == 99) 
	{
		puppet.setSize(sf::Vector2f(1.f, 1.f));
		puppet.setPosition(this->player->getBounds().left + this->player->getBounds().width * (4.f / 10.f), this->player->getBounds().top + this->player->getBounds().height * (8.f / 10.f));

		//Create explosion
		this->explosions.push_back(new Explosion(this->textures["EXPLOTA_01"], this->textures["EXPLOTA_02"], this->textures["EXPLOTA_03"], puppet.getGlobalBounds()));
	}

	if (this->sequenceTimer == 50)
	{
		puppet.setSize(sf::Vector2f(1.f, 1.f));
		puppet.setPosition(this->player->getBounds().left + this->player->getBounds().width * (2.f / 10.f), this->player->getBounds().top + this->player->getBounds().height * (2.f / 10.f));

		//Create explosion
		this->explosions.push_back(new Explosion(this->textures["EXPLOTA_01"], this->textures["EXPLOTA_02"], this->textures["EXPLOTA_03"], puppet.getGlobalBounds()));
	}

	if (this->sequenceTimer == 0)
	{
		puppet.setSize(sf::Vector2f(1.f, 1.f));
		puppet.setPosition(this->player->getBounds().left + this->player->getBounds().width * (8.f / 10.f), this->player->getBounds().top + this->player->getBounds().height * (3.f / 10.f));

		//Create explosion
		this->explosions.push_back(new Explosion(this->textures["EXPLOTA_01"], this->textures["EXPLOTA_02"], this->textures["EXPLOTA_03"], puppet.getGlobalBounds()));
	}

}

CombatEngine::CombatEngine(sf::Vector2u windowSize, std::vector<Bullet*>& bullets, std::vector<Enemy*>& enemies, Player* player, Enemy*& ufo, std::vector<Explosion*>& explosions) : bullets(bullets), enemies(enemies), ufo(ufo), explosions(explosions)
{
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