#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Explosion
{
	//Private variables
	sf::Sprite sprite;
	sf::Texture* expl1;
	sf::Texture* expl2;
	sf::Texture* expl3;
	sf::FloatRect objectBounds;
	int explosionTimer, explosionTimerMax;

	//Private functions
	void initVariables();
	void initSprite();
	void center();

public:

	//Public functions
	void setTexture(int);
	bool explosionRelease();
	void render(sf::RenderTarget*);

	//Constructor
	Explosion(sf::Texture*, sf::Texture*, sf::Texture*, const sf::FloatRect);

	//Destructor
	virtual ~Explosion();
};

