#pragma once

#include "HiScore.h"

#include <vector>

class HiScoreEngine
{
	//Private variables
	std::vector<HiScore*> HiScores;
	unsigned int points, cursorPointerPosition;
	sf::Vector2f windowSize;
	bool holdW, holdE, holdConfirm;
	bool exportDecision, backDecision;

	sf::Sprite background, pointer;
	sf::Font font;
	sf::Text backText, exportText;
	sf::RenderWindow* window;

	//Resources
	std::map<std::string, sf::Texture*> textures;

	//Private functions
	void initVariables();
	void initTextures();
	void initSprites();
	void initFont();
	void initText();
	void setPointer(int);
	void colorizeOption(int);
	void setDecision(int);

public:

	//Public functions
	void initHiScore();
	void updateHiScore();
	void hiScoreRender(sf::RenderTarget*);

	//Accesors
	const sf::Vector2f getMousePos() const;
	const bool getDecision(int) const;

	//Constructor
	HiScoreEngine(sf::Vector2f, sf::RenderWindow*);

	//Destructor
	virtual ~HiScoreEngine();
};

