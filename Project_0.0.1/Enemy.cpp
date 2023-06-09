#pragma once
#include "Enemy.h"

//Static variables
float Enemy::movementSpeed = 1.f;

//Private functions
void Enemy::initVariables()
{
	this->hpMax = 15;
	this->hp = this->hpMax;
	this->damage = 5;
	this->points = 10;
	this->movementSpeed = 1.f;
	this->isUfo = false;
	this->hitTimer = 0;
	this->hitted = false;
}

void Enemy::initHitbox()
{
	this->hitbox.setSize(sf::Vector2f(11.f, 9.f));
	this->hitbox.setScale(4.f, 4.f);

	this->hitbox.setFillColor(sf::Color(0, 0, 0, 0));
	this->hitbox.setOutlineThickness(0.25f);

	//put 0 here to hide hitbox (default 115) ------------v
	this->hitbox.setOutlineColor(sf::Color(255, 255, 255, 0));
}

void Enemy::initSprite()
{
	this->sprite.setTexture(*this->texture1);
	this->sprite.setScale(4.f, 4.f);
}

//Public functions
void Enemy::update()
{
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	target->draw(this->hitbox);
}

void Enemy::move(const float movX, const float movY)
{
	this->sprite.move(this->movementSpeed * movX, this->movementSpeed * movY);
	this->hitbox.move(this->movementSpeed * movX, this->movementSpeed * movY);
}

void Enemy::move(const float movX, const float movY, bool staticMovement)
{
	if (!staticMovement)
	{
		this->sprite.move(this->movementSpeed * movX, this->movementSpeed * movY);
		this->hitbox.move(this->movementSpeed * movX, this->movementSpeed * movY);
	}
	else
	{
		this->sprite.move(movX, movY);
		this->hitbox.move(movX, movY);
	}
}

void Enemy::damageEnemy(float damage)
{
	this->hp -= damage;
}

void Enemy::setUfo()
{
	this->isUfo = true;
}

void Enemy::hit(sf::Vector2f move)
{
	if (!this->hitted)
	{
		this->move(move.x, -move.y, true);
	}

	this->hitTimer = 10;
	this->hitted = true;
}

void Enemy::hitRealease(sf::Vector2f move)
{
	if (this->hitted)
	{
		--hitTimer;
		if (hitTimer <= 0)
		{
			//Release
			this->move(move.x, move.y, true);
			this->hitted = false;
		}
	}
}




//Accesors
const sf::FloatRect Enemy::getBoundsHitbox() const
{
	return this->hitbox.getGlobalBounds();
}

const sf::FloatRect Enemy::getBoundsSprite() const
{
	return this->sprite.getGlobalBounds();
}

const int Enemy::getHP() const
{
	return this->hp;
}

const int Enemy::getPoints() const
{
	return this->points;
}

const bool Enemy::getIsUfo() const
{
	return false;
}

void Enemy::setMovementSpeed(float movementSpeed)
{
	this->movementSpeed = movementSpeed;
}

void Enemy::setTexture(bool texture)
{
	if (!texture)
	{
		sprite.setTexture(*this->texture1);
	}
	else
	{
		sprite.setTexture(*this->texture2);
	}
}

//Constructor
Enemy::Enemy(sf::Texture* texture1, sf::Texture* texture2, const float posX, const float posY, float movementSpeed, int points)
{
	this->initVariables();

	this->texture1 = texture1;
	this->texture2 = texture2;
	this->movementSpeed = movementSpeed;
	this->points = points;

	this->hitbox.setPosition(posX, posY);
	this->sprite.setPosition(posX, posY);

	this->initHitbox();
	this->initSprite();
}

//Destructor
Enemy::~Enemy()
{
}
