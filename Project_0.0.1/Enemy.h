#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Enemy
{
	//Private variables
	sf::RectangleShape hitbox;
	sf::Sprite sprite;
	sf::Texture texture;

	int hp, hpMax, damage, points;
	float movementSpeed;

	//Private functions
	void initVariables();
	void initHitbox();
	void initTexture();
	void initSprite();

public:

	//Public functions
	void update();
	void render(sf::RenderTarget*);
	void move(const float, const float);

	//Constructor
	Enemy(const float, const float);

	//Destructor
	virtual ~Enemy();
};

