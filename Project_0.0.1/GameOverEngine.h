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
	unsigned cursorPointerPosition, currentLetter;
	std::stringstream nickname;

	sf::Vector2f windowSize;
	sf::RenderWindow* window;

	bool inSave, inNickname;
	bool quitDecision, saveDecision;

	bool hold, holdConfirm, holdBack;
	bool holdTable[36];

	sf::Font font;
	sf::Text yesText, noText, confirmText, cancelText;
	sf::Text scoreText;

	sf::Text letter1, letter2, letter3, letter4, letter5;

	sf::Sprite pointer, backgroundSave, backgroundName;

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
	void setCurrentLetter(std::string);

public:

	//Public functions
	void initGameOver();
	void updateGameOver();
	void renderGameOver(sf::RenderTarget*);
	const bool getDecision(int decision) const;
	const std::string getNickName() const;

	//Accesors
	const sf::Vector2f getMousePos() const;

	//Constructor
	GameOverEngine(unsigned*&, sf::Vector2f, sf::RenderWindow*);

	//Destructor
	virtual ~GameOverEngine();
};