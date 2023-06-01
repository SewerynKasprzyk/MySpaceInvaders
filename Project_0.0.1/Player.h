#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{
	//Private variables
	sf::Sprite sprite;
	sf::Texture texture;
	unsigned width, height;
	sf::Vector2u windowSize;

	float movementSpeed, bulletCd, bulletCdMax, bulletCdMultipler, damage, damageMultipler, bulletSpeed, bulletSpeedMultipler;

	//Private functions
	void initVariables(unsigned, unsigned);
	void initTexture();
	void initSprite();
	void updateBulletCd();

public:

	//Public functions
	void update();
	const bool readyToShoot();
	void render(sf::RenderTarget*);
	void move(const float, const float);

	//Accessors
	const sf::Vector2f getPos() const;
	const sf::FloatRect getBounds() const;
	float getDamage() const;
	float getBulletSpeed() const;

	Player(unsigned, unsigned);
	virtual ~Player();
};

