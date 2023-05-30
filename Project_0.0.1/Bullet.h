#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Bullet
{
	//Private Variables
	sf::Sprite bullet;

	sf::Vector2f direction;
	float movementSpeed;

	//Private functions
	void initSprite();

public:

	//Public functions
	void update();
	void render(sf::RenderTarget*);

	//Accesors
	const sf::FloatRect getBounds() const;

	//Constructor
	Bullet(sf::Texture*, float, float, float, float, float);

	//Destructor
	virtual ~Bullet();
};

