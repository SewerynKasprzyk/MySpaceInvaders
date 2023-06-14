#pragma once
#include "HiScoreEngine.h"

void HiScoreEngine::initVariables()
{
	this->cursorPointerPosition = 0;
	this->holdW = true;
	this->holdS = true;
	this->holdConfirm = true;

	this->backDecision = false;
	this->points = 0;
	this->visibleScores = 0;
}

void HiScoreEngine::initTextures()
{
	this->textures["SPACE_SHIP"] = new sf::Texture();
	this->textures["SPACE_SHIP"]->loadFromFile(".\\Textures\\Pointer_Sprites\\Pointer_Sprite.png");

	this->textures["BACKGROUND_02"] = new sf::Texture();
	this->textures["BACKGROUND_02"]->loadFromFile(".\\Textures\\Backgrounds\\Hi-Score_Background.png");
}

void HiScoreEngine::initSprites()
{
	this->background.setTexture(*this->textures["BACKGROUND_02"]);
	this->background.setPosition(windowSize.x - windowSize.x, windowSize.y - windowSize.y);

	float scaleX = 0.f, scaleY = 0.f;
	scaleX = windowSize.x / this->background.getGlobalBounds().width;
	scaleY = windowSize.y / this->background.getGlobalBounds().height;

	this->background.setScale(scaleX, scaleY);
	this->background.setPosition(windowSize.x - windowSize.x, windowSize.y - windowSize.y);

	this->pointer.setTexture(*this->textures["SPACE_SHIP"]);

	//This must be in fixed condition
	this->pointer.setScale(0.06f, 0.06f);
	this->setPointer(this->cursorPointerPosition);
	this->colorizeOption(this->cursorPointerPosition);
}

void HiScoreEngine::initFont()
{
	this->font.loadFromFile(".\\Fonts\\space_invaders.ttf");
}

void HiScoreEngine::initText()
{
	this->backText.setFont(this->font);
	this->backText.setCharacterSize(22);
	this->backText.setFillColor(sf::Color::White);

	this->upText = this->backText;
	this->downText = this->backText;

	this->upText.setString("U P");
	this->downText.setString("D O W N");
	this->backText.setString("B A C K");

	this->upText.setPosition(windowSize.x * (3.f / 32.f), windowSize.y * (14.f / 36.f));
	this->downText.setPosition(windowSize.x * (3.f / 32.f), windowSize.y * (17.f / 36.f));
	this->backText.setPosition(windowSize.x * (3.f / 32.f), windowSize.y * (20.f / 36.f));
}

void HiScoreEngine::initScores()
{
	HiScoreDB db;


	for (auto* i : this->hiScores)
	{
		delete i;
	}

	this->hiScores = {};

	float i = 0;

	for (auto& element : db.getVector())
	{
		std::stringstream posName;

		posName << i + 1 << ". " << element.name;
		this->hiScores.push_back(new HiScore(element.score, posName.str(), sf::Vector2f(this->windowSize.x * (8.f / 32.f), this->windowSize.y * ((6.f + i) / 18.f)), sf::Vector2f(this->windowSize.x * (14.f / 32.f), this->windowSize.y * ((6.f + i) / 18.f))));

		if (i == 0)
		{
			sf::Color greeny = sf::Color(122, 224, 124, 255);
			this->hiScores[i]->colorize(greeny);
		}

		i = i + 1.f;
	}

}

void HiScoreEngine::setPointer(int option)
{
	switch (option)
	{
	case 0:
		this->pointer.setPosition(this->upText.getGlobalBounds().left - this->pointer.getGlobalBounds().width * 1.2f, this->upText.getGlobalBounds().top - this->pointer.getGlobalBounds().height / 4.f);
		break;

	case 1:
		this->pointer.setPosition(this->downText.getGlobalBounds().left - this->pointer.getGlobalBounds().width * 1.2f, this->downText.getGlobalBounds().top - this->pointer.getGlobalBounds().height / 4.f);
		break;

	case 2:
		this->pointer.setPosition(this->backText.getGlobalBounds().left - this->pointer.getGlobalBounds().width * 1.2f, this->backText.getGlobalBounds().top - this->pointer.getGlobalBounds().height / 4.f);
		break;

	default:
		this->pointer.setPosition(this->upText.getGlobalBounds().left - this->pointer.getGlobalBounds().width * 1.2f, this->upText.getGlobalBounds().top - this->pointer.getGlobalBounds().height / 4.f);
		break;
	}
}

void HiScoreEngine::colorizeOption(int option)
{
	this->upText.setFillColor(sf::Color::White);
	this->downText.setFillColor(sf::Color::White);
	this->backText.setFillColor(sf::Color::White);

	sf::Color greeny = sf::Color(122, 224, 124, 255);

	switch (option)
	{
	case 0:
		this->upText.setFillColor(greeny);
		break;

	case 1:
		this->downText.setFillColor(greeny);
		break;

	case 2:
		this->backText.setFillColor(greeny);
		break;
	}
}

void HiScoreEngine::setDecision(int decision)
{
	switch (decision)
	{
	case 0:
		this->moveUpDown(true);
		break;

	case 1:
		this->moveUpDown(false);
		break;

	case 2:
		this->backDecision = true;
		break;
	}
}

void HiScoreEngine::moveUpDown(bool moveUpDown)
{
	if (moveUpDown)
	{
		float move = 9.f;

		if (this->visibleScores - 9 < 0)
		{
			move = this->visibleScores;
			this->visibleScores = 0;
		}
		else
		{
			this->visibleScores -= 9;
		}

		for (auto& hiScore : this->hiScores)
		{
			hiScore->move(0.f, this->windowSize.y * (move / 18.f));
		}
	}
	else
	{
		float move = 9.f;

		if (this->visibleScores + 9 > this->hiScores.size())
		{
			move = 0.f;
		}
		else
		{
			this->visibleScores += 9;
		}

		for (auto& hiScore : this->hiScores)
		{
			hiScore->move(0.f, -this->windowSize.y * (move / 18.f));
		}
	}
}

void HiScoreEngine::initHiScore()
{
	this->initVariables();
	this->initFont();
	this->initText();
	this->initTextures();
	this->initSprites();
	this->initScores();
}


void HiScoreEngine::updateHiScore()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
	{
		if (!this->holdW)
		{
			if (this->cursorPointerPosition != 0)
			{
				--this->cursorPointerPosition;
			}

			this->setPointer(this->cursorPointerPosition);
			this->colorizeOption(this->cursorPointerPosition);
			this->holdW = true;
		}
	}
	else
	{
		this->holdW = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
	{
		if (!this->holdS)
		{
			if (this->cursorPointerPosition != 2)
			{
				++this->cursorPointerPosition;
			}

			this->setPointer(this->cursorPointerPosition);
			this->colorizeOption(this->cursorPointerPosition);
			this->holdS = true;
		}
	}
	else
	{
		this->holdS = false;
	}

	if (this->upText.getGlobalBounds().contains(this->getMousePos()))
	{
		this->cursorPointerPosition = 0;

		this->setPointer(this->cursorPointerPosition);
		this->colorizeOption(this->cursorPointerPosition);
	}

	if (this->downText.getGlobalBounds().contains(this->getMousePos()))
	{
		this->cursorPointerPosition = 1;

		this->setPointer(this->cursorPointerPosition);
		this->colorizeOption(this->cursorPointerPosition);
	}

	if (this->backText.getGlobalBounds().contains(this->getMousePos()))
	{
		this->cursorPointerPosition = 2;

		this->setPointer(this->cursorPointerPosition);
		this->colorizeOption(this->cursorPointerPosition);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!this->holdConfirm)
		{
			this->holdConfirm = true;
			this->setDecision(this->cursorPointerPosition);
		}
	}
	else
	{
		this->holdConfirm = false;
	}
}

void HiScoreEngine::hiScoreRender(sf::RenderTarget* target)
{
	target->draw(this->background);
	target->draw(this->pointer);

	target->draw(this->upText);
	target->draw(this->downText);
	target->draw(this->backText);

	if (this->hiScores.size() != 0)
	{
		for (int i = this->visibleScores; i < 9 + this->visibleScores; i++)
		{
			if (i >= this->hiScores.size())
			{
				break;
			}

			this->hiScores[i]->render(target);
		}
	}
}

const sf::Vector2f HiScoreEngine::getMousePos() const
{
	sf::Vector2i pos = sf::Mouse::getPosition(*this->window);
	return this->window->mapPixelToCoords(pos);
}

const bool HiScoreEngine::getDecision(int decision) const
{
	switch (decision)
	{
	case 2:
		return this->backDecision;
		break;
	}
}

HiScoreEngine::HiScoreEngine(sf::Vector2f windowSize, sf::RenderWindow* window)
{
	this->initVariables();
	this->windowSize = windowSize;
	this->window = window;
}

HiScoreEngine::~HiScoreEngine()
{
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	for (auto* i : this->hiScores)
	{
		delete i;
	}
}