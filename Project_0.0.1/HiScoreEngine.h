#pragma once

#include "HiScore.h"
#include "HiScoreDB.h"
#include "HiScoreDbElement.h"

#include <vector>

class HiScoreEngine
{
	//Private variables
	std::vector<HiScore*> hiScores;
	unsigned int points, cursorPointerPosition;
	sf::Vector2f windowSize;
	bool holdW, holdS, holdConfirm;
	bool exportDecision, backDecision;
	int visibleScores;

	sf::Sprite background, pointer;
	sf::Font font;
	sf::Text backText, upText, downText;
	sf::RenderWindow* window;

	//Resources
	std::map<std::string, sf::Texture*> textures;

	//Private functions
	void initVariables();
	void initTextures();
	void initSprites();
	void initFont();
	void initText();
	void initScores();

	void setPointer(int);
	void colorizeOption(int);
	void setDecision(int);

	//If true -> up | if false -> down
	void moveUpDown(bool);

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

