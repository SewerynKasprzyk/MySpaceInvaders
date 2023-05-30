#include "Bullet.h"

//Private functions
void Bullet::initSprite()
{
	this->bullet.rotate(-90);
	this->bullet.setScale(0.5f, 0.2f);
	this->bullet.move(43.f, 43.f);
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

//Constructor
Bullet::Bullet(sf::Texture* texture, float posX, float posY, float movX, float movY, float movement_speed)
{
	this->bullet.setTexture(*texture);

	this->bullet.setPosition(posX, posY);

	this->direction.x = movX;
	this->direction.y = movY;
	this->movementSpeed = movement_speed;

	this->initSprite();
}

//Destructor
Bullet::~Bullet()
{
}
