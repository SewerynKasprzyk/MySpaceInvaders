#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <string>
#include <sstream>

class GameOverEngine
{
	//private variables
	unsigned*& points;
	unsigned cursorPointerPosition;
	sf::Vector2f windowSize;

	bool inSave, inNickname;

	bool hold, holdConfirm;

	sf::Font font;
	sf::Text yesText, noText, confirmTextm, cancelText;
	sf::Text score;

	sf::Text letter1, letter2, letter3, letter4, letter5;

	sf::Sprite pointer, background;

	//Resources
	std::map<std::string, sf::Texture*> textures;

	//Private functions
	void initVariables();
	void initFont();
	void initText();
	void initTextures();
	void initSprites();
	void setPointer(int);
	void colorizeOption(int);
	void setDecision(int);

public:

	//Public functions
	void initGameOver();
	void updateGameOver();
	void renderGameOver();

	//Accesors
	const sf::Vector2f getMousePos() const;

	//Constructor
	GameOverEngine(unsigned*&, sf::Vector2f, sf::RenderWindow*);

	//Destructor
	virtual ~GameOverEngine();
};