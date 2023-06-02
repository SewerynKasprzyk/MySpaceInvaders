#include "Bullet.h"

//Private functions
void Bullet::initSprite()
{
	this->bullet.rotate(-90);
	this->bullet.setScale(0.25f, 0.1f);
	this->bullet.move((- bullet.getGlobalBounds().width / 2.f) - 2.f, -15.f);
}

void Bullet::update()
{
	//Movement
	this->bullet.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->bullet);
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->bullet.getGlobalBounds();
}

const float Bullet::getDamage() const
{
	return this->damage;
}

const bool Bullet::isEnemyBullet() const
{
	if (this->direction.y < 0.f)
	{
		return false;
	}

	else
	{
		return true;
	}
}

//Constructor
Bullet::Bullet(sf::Texture* texture, float posX, float posY, float movX, float movY, float movement_speed, float damage)
{
	this->bullet.setTexture(*texture);

	this->bullet.setPosition(posX, posY);

	this->direction.x = movX;
	this->direction.y = movY;
	this->movementSpeed = movement_speed;

	this->damage = damage;

	this->initSprite();

	if (isEnemyBullet())
	{
		this->bullet.rotate(180);
	}
}

//Destructor
Bullet::~Bullet()
{
}
