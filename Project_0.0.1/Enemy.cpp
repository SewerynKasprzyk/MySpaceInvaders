#include "Enemy.h"

//Private functions
void Enemy::initVariables()
{
	this->hpMax = 15;
	this->hp = this->hpMax;
	this->damage = 5;
	this->points = 10;
	this->movementSpeed = 1.f;
}

void Enemy::initHitbox()
{
	this->hitbox.setSize(sf::Vector2f(50.f, 50.f));
	this->hitbox.setFillColor(sf::Color(0, 0, 0, 0));
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(sf::Color(255, 255, 255, 115));
}

void Enemy::initTexture()
{
	this->texture;
}

void Enemy::initSprite()
{
	this->sprite;
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

//Constructor
Enemy::Enemy(const float posX, const float movY)
{
	this->initVariables();
	this->initHitbox();
	this->initSprite();

	this->hitbox.setPosition(posX, movY);
	this->sprite.setPosition(posX, movY);
}

//Destructor
Enemy::~Enemy()
{
}
