#pragma once
#include "Explosion.h"

void Explosion::initVariables()
{
	this->explosionTimerMax = 70;
	this->explosionTimer = this->explosionTimerMax;
}

void Explosion::initSprite()
{
	this->setTexture(0);
}

void Explosion::center()
{
	float centerX = 0, centerY = 0;
	sf::FloatRect spriteBounds = this->sprite.getGlobalBounds();
	centerX = (objectBounds.left + objectBounds.width / 2.f) - spriteBounds.width / 2;
	centerY = (objectBounds.top + objectBounds.height / 2.f) - spriteBounds.height / 2;

	this->sprite.setPosition(centerX, centerY);
}

void Explosion::setTexture(int change)
{
	if (change <= 0)
	{
		this->sprite.setTexture(*this->expl1);
	}
	else if (change == 1)
	{
		this->sprite.setTexture(*this->expl2);
	}
	else if (change >= 2)
	{
		this->sprite.setTexture(*this->expl3);
	}

	this->sprite.setScale(3.f, 3.f);
	this->center();
}

bool Explosion::explosionRelease()
{
	--this->explosionTimer;

	if (this->explosionTimer <= this->explosionTimerMax * (2.f / 3.f) && this->explosionTimer >= this->explosionTimerMax * (1.f / 3.f))
	{
		this->setTexture(1);
	}

	else if (this->explosionTimer <= this->explosionTimerMax * (1.f / 3.f))
	{
		this->setTexture(2);
	}

	if (this->explosionTimer > 0)
	{
		return false;
	}

	else if (this->explosionTimer <= 0)
	{
		return true;
	}
}

void Explosion::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

Explosion::Explosion(sf::Texture* expl1, sf::Texture* expl2, sf::Texture* expl3, const sf::FloatRect objectBounds)
{
	this->initVariables();

	this->expl1 = expl1;
	this->expl2 = expl2;
	this->expl3 = expl3;
	this->objectBounds = objectBounds;

	this->initSprite();
}

Explosion::~Explosion()
{
}
