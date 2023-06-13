#pragma once
#include "HiScoreEngine.h"

void HiScoreEngine::initVariables()
{
	this->cursorPointerPosition = 0;
	this->holdW = true;
	this->holdE = true;
	this->holdConfirm = true;

	this->exportDecision = false;
	this->backDecision = false;
	this->points = 0;
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
	this->exportText.setFont(this->font);
	this->exportText.setCharacterSize(22);
	this->exportText.setFillColor(sf::Color::White);

	this->backText = this->exportText;

	this->exportText.setString("EXPORT");
	this->backText.setString("B A C K");

	this->exportText.setPosition(windowSize.x * (3.f / 32.f), windowSize.y * (14.f / 36.f));
	this->backText.setPosition(windowSize.x * (3.f / 32.f), windowSize.y * (17.f / 36.f)); 
}

void HiScoreEngine::setPointer(int option)
{
	switch (option)
	{
	case 0:
		this->pointer.setPosition(this->exportText.getGlobalBounds().left - this->pointer.getGlobalBounds().width * 1.2f, this->exportText.getGlobalBounds().top - this->pointer.getGlobalBounds().height / 4.f);
		break;

	case 1:
		this->pointer.setPosition(this->backText.getGlobalBounds().left - this->pointer.getGlobalBounds().width * 1.2f, this->backText.getGlobalBounds().top - this->pointer.getGlobalBounds().height / 4.f);
		break;

	default:
		this->pointer.setPosition(this->exportText.getGlobalBounds().left - this->pointer.getGlobalBounds().width * 1.2f, this->exportText.getGlobalBounds().top - this->pointer.getGlobalBounds().height / 4.f);
		break;
	}
}

void HiScoreEngine::colorizeOption(int option)
{
	this->exportText.setFillColor(sf::Color::White);
	this->backText.setFillColor(sf::Color::White);

	sf::Color greeny = sf::Color(122, 224, 124, 255);

	switch (option)
	{
	case 0:
		this->exportText.setFillColor(greeny);
		break;

	case 1:
		this->backText.setFillColor(greeny);
		break;
	}
}

void HiScoreEngine::setDecision(int decision)
{
	switch (decision)
	{
	case 0:
		this->exportDecision = true;
		break;

	case 1:
		this->backDecision = true;
		break;
	}
}

void HiScoreEngine::initHiScore()
{
	this->initVariables();
	this->initFont();
	this->initText();
	this->initTextures();
	this->initSprites();
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
		holdW = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
	{
		if (!this->holdE)
		{
			if (this->cursorPointerPosition != 1)
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

	if (this->exportText.getGlobalBounds().contains(this->getMousePos()))
	{
		this->cursorPointerPosition = 0;

		this->setPointer(this->cursorPointerPosition);
		this->colorizeOption(this->cursorPointerPosition);
	}

	if (this->backText.getGlobalBounds().contains(this->getMousePos()))
	{
		this->cursorPointerPosition = 1;

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

	target->draw(this->exportText);
	target->draw(this->backText);
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
	case 0:
		return this->exportDecision;
		break;

	case 1:
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
}