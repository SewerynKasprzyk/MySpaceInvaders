#pragma once
#include "Player.h"

//Private functions
void Player::initVariables(unsigned width, unsigned height)
{
	this->width = width;
	this->height = height;
	this->movementSpeed = 7.f;
	this->bulletCdMultipler = 3.f;
	this->bulletCdMax = 100.f * (1.f/bulletCdMultipler);
	this->bulletCd = this->bulletCdMax;
	this->damage = 5.f;
	this->damageMultipler = 1.f;
	this->bulletSpeed = 5.f;
	this->bulletSpeedMultipler = 1.f;
	this->hpMax = 100.f;
	this->hp = this->hpMax;
	this->alive = true;
	*this->points = 0;
}

void Player::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile(".\\Textures\\Ship_Sprites\\Ship_texture.png"))
	{
		std::cout << "ERROR::PLAYER_H::INITTEXTURE::Loading texture was failed!" << std::endl;
	}
}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//Resize the sprite
	this->sprite.scale(0.075f, 0.075f);

	this->sprite.setPosition(((this->width/2.f) - 50.f), (this->height - 100.f));
}

//Public functions
void Player::update()
{
	this->updateBulletCd();
}

void Player::updateBulletCd()
{
	if (this->bulletCd < this->bulletCdMax)
	{
		this->bulletCd += 1.f;
	}
}

const bool Player::readyToShoot()
{
	if (this->alive && this->bulletCd >= this->bulletCdMax)
	{
		this->bulletCd = 0.f;
		return true;
	}

	this->bulletCd += 0.2f;
	return false;
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

void Player::move(const float movX, const float movY)
{
	this->sprite.move(this->movementSpeed * movX, this->movementSpeed * movY);
}

void Player::damagePlayer(float damage)
{
	this->hp -= damage;
}

void Player::killPlayer()
{
	this->alive = false;
}

void Player::addPoints(unsigned points)
{
	*this->points += points;
}

void Player::hidePlayer()
{
	this->sprite.setPosition(this->windowSize.x, this->windowSize.y);
}

//Accessors
const sf::Vector2f Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

float Player::getDamage() const
{
	return this->damage * this->damageMultipler;
}

float Player::getHP() const
{
	return this->hp;
}

float Player::getHP(bool max) const
{
	if (max == true)
	{
		return this->hpMax;
	}
	else
	{
		return this->hp;
	}
}

float Player::getBulletSpeed() const
{
	return this->bulletSpeed * this->bulletSpeedMultipler;
}

const bool Player::getState() const
{
	return this->alive;
}

const unsigned Player::getPoints() const
{
	return *this->points;
}


Player::Player(unsigned posX, unsigned posY, sf::Vector2f windowSize, unsigned*& points) : points(points)
{
	this->windowSize = windowSize;
	this->initVariables(posX, posY);
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
	
}
