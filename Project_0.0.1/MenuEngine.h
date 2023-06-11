#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <string>
#include <sstream>

class MenuEngine
{
	//private variables
	unsigned*& points;
	unsigned cursorPointerPosition;
	sf::Vector2f windowSize;
	std::map<std::string, sf::Texture*> textures;

	sf::Font font;
	sf::Text play, hiScore, quit;

	sf::Sprite pointer, background;
	sf::Texture pointerTexture, backgroundTexture;

	//PrivateFunctions
	void initVariables();
	void initText();
	void initTextures();
	void initSprites();
	void setPointer(int);

public:

	//Public functions
	void initMenu();
	void updateMenu();
	void menuRender(sf::RenderTarget*);

	//Constructor
	MenuEngine(unsigned*&, sf::Vector2f);

	//Destructor
	virtual ~MenuEngine();
};

