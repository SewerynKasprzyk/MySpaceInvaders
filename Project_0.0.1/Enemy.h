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
	sf::Texture* texture1;
	sf::Texture* texture2;

	int hp, hpMax, damage, points;
	static float movementSpeed;

	//Private functions
	void initVariables();
	void initHitbox();
	void initSprite();

public:

	//Public functions
	void update();
	void render(sf::RenderTarget*);
	void move(const float, const float);

	//Accesors
	const sf::FloatRect getBoundsHitbox() const;
	const sf::FloatRect getBoundsSprite() const;
	const int getHP() const;
	void setMovementSpeed(float);
	void setTexture(bool);
	void damageEnemy(float);

	//Constructor
	Enemy(sf::Texture*, sf::Texture*, const float, const float, float);

	//Destructor
	virtual ~Enemy();
};

