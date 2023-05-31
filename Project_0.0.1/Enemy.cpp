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
	this->hitbox.setSize(sf::Vector2f(11.f, 9.f));
	this->hitbox.setScale(4.f, 4.f);

	this->hitbox.setFillColor(sf::Color(0, 0, 0, 0));
	this->hitbox.setOutlineThickness(0.5f);
	this->hitbox.setOutlineColor(sf::Color(255, 255, 255, 115));

	//comment this if u want to see hitbox
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

const sf::FloatRect Enemy::getBoundsHitbox() const
{
	return this->hitbox.getGlobalBounds();
}

const sf::FloatRect Enemy::getBoundsSprite() const
{
	return this->sprite.getGlobalBounds();
}

//Constructor
Enemy::Enemy(sf::Texture* texture1, sf::Texture* texture2, const float posX, const float posY, float movementSpeed)
{
	this->initVariables();

	this->texture1 = texture1;
	this->texture2 = texture2;
	this->movementSpeed = movementSpeed;

	this->hitbox.setPosition(posX, posY);
	this->sprite.setPosition(posX, posY);

	this->initHitbox();
	this->initSprite();
}

//Destructor
Enemy::~Enemy()
{
}
