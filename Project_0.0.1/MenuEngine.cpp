#pragma once
#include "MenuEngine.h"

void MenuEngine::initVariables()
{
	this->cursorPointerPosition = 0;
	this->holdW = true;
	this->holdE = true;
	this->holdConfirm = true;

	this->playDecision = false;
	this->hiScoreDecision = false;
	this->quitDecision = false;
}

void MenuEngine::initText()
{
	this->font.loadFromFile(".\\Fonts\\space_invaders.ttf");
	this->play.setFont(this->font);
	this->play.setCharacterSize(22);
	this->play.setFillColor(sf::Color::White);

	this->hiScore = this->play;
	this->quit = this->play;

	this->play.setString("P L A Y");
	this->hiScore.setString("HI-SCORE");
	this->quit.setString("E X I T");

	this->play.setPosition(windowSize.x * (3.f / 32.f), windowSize.y * (14.f / 36.f));
	this->hiScore.setPosition(windowSize.x * (3.f / 32.f), windowSize.y * (17.f / 36.f));
	this->quit.setPosition(windowSize.x * (3.f / 32.f), windowSize.y * (20.f / 36.f));
}

void MenuEngine::initTextures()
{
	this->textures["SPACE_SHIP"] = new sf::Texture();
	this->textures["SPACE_SHIP"]->loadFromFile(".\\Textures\\Pointer_Sprites\\Pointer_Sprite.png");

	this->textures["BACKGROUND_01"] = new sf::Texture();
	this->textures["BACKGROUND_01"]->loadFromFile(".\\Textures\\Backgrounds\\Menu_Background.png");
}

void MenuEngine::initSprites()
{
	this->background.setTexture(*this->textures["BACKGROUND_01"]);
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

void MenuEngine::setPointer(int option)
{
	switch (option)
	{
	case 0:
		this->pointer.setPosition(this->play.getGlobalBounds().left - this->pointer.getGlobalBounds().width * 1.2f, this->play.getGlobalBounds().top - this->pointer.getGlobalBounds().height / 4.f);
		break;

	case 1:
		this->pointer.setPosition(this->hiScore.getGlobalBounds().left - this->pointer.getGlobalBounds().width * 1.2f, this->hiScore.getGlobalBounds().top - this->pointer.getGlobalBounds().height / 4.f);
		break;

	case 2:
		this->pointer.setPosition(this->quit.getGlobalBounds().left - this->pointer.getGlobalBounds().width * 1.2f, this->quit.getGlobalBounds().top - this->pointer.getGlobalBounds().height / 4.f);
		break;

	default:
		this->pointer.setPosition(this->play.getGlobalBounds().left - this->pointer.getGlobalBounds().width * 1.2f, this->play.getGlobalBounds().top - this->pointer.getGlobalBounds().height / 4.f);
		break;
	}
}

void MenuEngine::colorizeOption(int option)
{
	this->play.setFillColor(sf::Color::White);
	this->hiScore.setFillColor(sf::Color::White);
	this->quit.setFillColor(sf::Color::White);

	sf::Color greeny = sf::Color(122, 224, 124, 255);

	switch (option)
	{
	case 0:
		this->play.setFillColor(greeny);
		break;

	case 1:
		this->hiScore.setFillColor(greeny);
		break;

	case 2:
		this->quit.setFillColor(greeny);
		break;
	}
}

void MenuEngine::setDecision(int decision)
{
	switch (decision)
	{
	case 0:
		this->playDecision = true;
		break;

	case 1:
		this->hiScoreDecision = true;
		break;

	case 2:
		this->quitDecision = true;
		break;
	}
}

const sf::Vector2f MenuEngine::getMousePos() const
{
	sf::Vector2i pos = sf::Mouse::getPosition(*this->window);
	return this->window->mapPixelToCoords(pos);
}

const bool MenuEngine::getDecision(int decision) const
{
	switch (decision)
	{
	case 0:
		return this->playDecision;
		break;

	case 1:
		return this->hiScoreDecision;
		break;

	case 2:
		return this->quitDecision;
		break;
	}
}

void MenuEngine::initMenu()
{
	this->initVariables();
	this->initText();
	this->initTextures();
	this->initSprites();
}

void MenuEngine::updateMenu()
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
		if (!this->holdE)
		{
			if (this->cursorPointerPosition != 2)
			{
				++this->cursorPointerPosition;
			}

			this->setPointer(this->cursorPointerPosition);
			this->colorizeOption(this->cursorPointerPosition);
			this->holdE = true;
		}
	}
	else
	{
		this->holdE = false;
	}

	if (this->play.getGlobalBounds().contains(this->getMousePos()))
	{
		this->cursorPointerPosition = 0;

		this->setPointer(this->cursorPointerPosition);
		this->colorizeOption(this->cursorPointerPosition);
	}

	if (this->hiScore.getGlobalBounds().contains(this->getMousePos()))
	{
		this->cursorPointerPosition = 1;

		this->setPointer(this->cursorPointerPosition);
		this->colorizeOption(this->cursorPointerPosition);
	}

	if (this->quit.getGlobalBounds().contains(this->getMousePos()))
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

void MenuEngine::menuRender(sf::RenderTarget* target)
{
	target->draw(this->background);
	target->draw(this->pointer);

	target->draw(this->play);
	target->draw(this->hiScore);
	target->draw(this->quit);
}

MenuEngine::MenuEngine(unsigned*& points, sf::Vector2f windowSize, sf::RenderWindow* window) : points(points)
{
	this->windowSize = windowSize;
	this->window = window;
	this->initMenu();
}

MenuEngine::~MenuEngine()
{
	for (auto& i : this->textures)
	{
		delete i.second;
	}
}