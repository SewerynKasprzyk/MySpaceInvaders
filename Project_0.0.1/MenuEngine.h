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
	bool holdW, holdE, holdConfirm;
	bool playDecision, hiScoreDecision, quitDecision;
	sf::RenderWindow* window;

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
	void colorizeOption(int);
	void setDecision(int);


public:

	//Public functions
	void initMenu();
	void updateMenu();
	void menuRender(sf::RenderTarget*);

	//Accesors
	const sf::Vector2f getMousePos() const;
	const bool getDecision(int) const;

	//Constructor
	MenuEngine(unsigned*&, sf::Vector2f, sf::RenderWindow*);

	//Destructor
	virtual ~MenuEngine();
};

