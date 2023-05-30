#include "Player.h"

//Private functions
void Player::initVariables(unsigned width, unsigned height)
{
	this->width = width;
	this->height = height;
	this->movementSpeed = 7.f;
	this->bulletCdMultipler = 0.5;
	this->bulletCdMax = 100.f * bulletCdMultipler;
	this->bulletCd = this->bulletCdMax;
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
	this->sprite.scale(0.1f, 0.1f);

	this->sprite.setPosition(((this->width/2.f) - 50), (this->height - 100.f));
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
	if (this->bulletCd >= this->bulletCdMax)
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

//Accessors
const sf::Vector2f Player::getPos() const
{
	return this->sprite.getPosition();
}

Player::Player(unsigned posX, unsigned posY)
{
	this->initVariables(posX, posY);
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
	
}
