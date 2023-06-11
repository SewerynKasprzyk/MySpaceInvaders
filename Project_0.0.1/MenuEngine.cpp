#include "MenuEngine.h"

void MenuEngine::initVariables()
{
	this->cursorPointerPosition = 0;
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
	this->setPointer(0);
	
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

void MenuEngine::initMenu()
{
	this->initVariables();
	this->initText();
	this->initTextures();
	this->initSprites();
}


void MenuEngine::updateMenu()
{

}

void MenuEngine::menuRender(sf::RenderTarget* target)
{
	target->draw(this->background);
	target->draw(this->pointer);

	target->draw(this->play);
	target->draw(this->hiScore);
	target->draw(this->quit);
}

MenuEngine::MenuEngine(unsigned*& points, sf::Vector2f windowSize) : points(points)
{
	this->windowSize = windowSize;
	this->initMenu();
}

MenuEngine::~MenuEngine()
{
}
