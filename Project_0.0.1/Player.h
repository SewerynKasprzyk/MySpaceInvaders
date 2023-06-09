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
	unsigned*& points;
	sf::Vector2f windowSize;
	float hp, hpMax;
	bool alive;

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
	void damagePlayer(float);
	void killPlayer();
	void addPoints(unsigned);
	void hidePlayer();

	//Accessors
	const sf::Vector2f getPos() const;
	const sf::FloatRect getBounds() const;
	float getDamage() const;
	float getHP() const;
	float getHP(bool) const;
	float getBulletSpeed() const;
	const bool getState() const;
	const unsigned getPoints() const;

	Player(unsigned, unsigned, sf::Vector2f, unsigned*&);
	virtual ~Player();
};

