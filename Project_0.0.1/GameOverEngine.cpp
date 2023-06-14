#include "GameOverEngine.h"

void GameOverEngine::initVariables()
{
	this->cursorPointerPosition = 0;
	this->inSave = true;
	this->inNickname = false;
	this->hold = true;
	this->holdConfirm = true;
	this->holdBack = true;
	this->quitDecision = false;
	this->saveDecision = false;
	this->currentLetter = 0;

	for (auto& element : this->holdTable)
	{
		element = true;
	}
}

void GameOverEngine::initFont()
{
	this->font.loadFromFile(".\\Fonts\\space_invaders.ttf");
}

void GameOverEngine::initText()
{
	this->yesText.setFont(this->font);
	this->yesText.setCharacterSize(22);
	this->yesText.setFillColor(sf::Color::White);

	this->noText = this->yesText;
	this->confirmText = this->yesText;
	this->cancelText = this->yesText;
	this->scoreText = this->yesText;

	this->letter1 = this->yesText;

	this->yesText.setString("Y E S");
	this->noText.setString("N O");
	this->confirmText.setString("CONFIRM");
	this->cancelText.setString("CANCEL");

	std::stringstream ss;

	ss << "SCORE: " << "0";

	this->scoreText.setString(ss.str());

	this->letter1.setString("");
	this->letter2 = this->letter1;
	this->letter3 = this->letter1;
	this->letter4 = this->letter1;
	this->letter5 = this->letter1;

	this->yesText.setPosition(this->windowSize.x * (13.f / 32.f), this->windowSize.y * (10.f / 18.f));
	this->noText.setPosition(this->windowSize.x * (18.f / 32.f), this->windowSize.y * (10.f / 18.f));
	this->confirmText.setPosition(this->windowSize.x * (13.f / 32.f), this->windowSize.y * (14.f / 18.f));
	this->cancelText.setPosition(this->windowSize.x * (18.f / 32.f), this->windowSize.y * (14.f / 18.f));

	this->scoreText.setPosition(5.f, 5.f);

	this->letter1.setPosition(this->windowSize.x * (11.75f / 32), this->windowSize.y * (10.f / 18.f));
	this->letter2.setPosition(this->windowSize.x * (13.75f / 32), this->windowSize.y * (10.f / 18.f));
	this->letter3.setPosition(this->windowSize.x * (15.75f / 32), this->windowSize.y * (10.f / 18.f));
	this->letter4.setPosition(this->windowSize.x * (17.75f / 32), this->windowSize.y * (10.f / 18.f));
	this->letter5.setPosition(this->windowSize.x * (19.75f / 32), this->windowSize.y * (10.f / 18.f));
}

void GameOverEngine::initTextures()
{
	this->textures["BACKGROUND_01"] = new sf::Texture;
	this->textures["BACKGROUND_01"]->loadFromFile(".\\Textures\\Backgrounds\\Game_Over_Background_01.png");

	this->textures["BACKGROUND_02"] = new sf::Texture;
	this->textures["BACKGROUND_02"]->loadFromFile(".\\Textures\\Backgrounds\\Game_Over_Background_02.png");

	this->textures["SPACE_SHIP"] = new sf::Texture();
	this->textures["SPACE_SHIP"]->loadFromFile(".\\Textures\\Pointer_Sprites\\Pointer_Sprite.png");
}

void GameOverEngine::initSprites()
{
	this->backgroundSave.setTexture(*this->textures["BACKGROUND_01"]);
	this->backgroundSave.setPosition(windowSize.x - windowSize.x, windowSize.y - windowSize.y);

	float scaleX = 0.f, scaleY = 0.f;
	scaleX = windowSize.x / this->backgroundSave.getGlobalBounds().width;
	scaleY = windowSize.y / this->backgroundSave.getGlobalBounds().height;

	this->backgroundSave.setScale(scaleX, scaleY);
	this->backgroundSave.setPosition(windowSize.x - windowSize.x, windowSize.y - windowSize.y);

	this->backgroundName.setTexture(*this->textures["BACKGROUND_02"]);
	this->backgroundName.setPosition(windowSize.x - windowSize.x, windowSize.y - windowSize.y);

	scaleX = windowSize.x / this->backgroundName.getGlobalBounds().width;
	scaleY = windowSize.y / this->backgroundName.getGlobalBounds().height;

	this->backgroundName.setScale(scaleX, scaleY);
	this->backgroundName.setPosition(windowSize.x - windowSize.x, windowSize.y - windowSize.y);

	this->pointer.setTexture(*this->textures["SPACE_SHIP"]);

	//This must be in fixed condition
	this->pointer.setScale(0.06f, 0.06f);
	this->setPointer(this->cursorPointerPosition);
	this->colorizeOption(this->cursorPointerPosition);
}

void GameOverEngine::setPointer(int option)
{
	if (this->inSave)
	{
		switch (option)
		{
		case 0:
			this->pointer.setPosition(this->yesText.getGlobalBounds().left - this->pointer.getGlobalBounds().width * 1.2f, this->yesText.getGlobalBounds().top - this->pointer.getGlobalBounds().height / 4.f);
			break;

		case 1:
			this->pointer.setPosition(this->noText.getGlobalBounds().left - this->pointer.getGlobalBounds().width * 1.2f, this->noText.getGlobalBounds().top - this->pointer.getGlobalBounds().height / 4.f);
			break;
		}
	}

	if (this->inNickname)
	{
		switch (option)
		{
		case 0:
			this->pointer.setPosition(this->confirmText.getGlobalBounds().left - this->pointer.getGlobalBounds().width * 1.2f, this->confirmText.getGlobalBounds().top - this->pointer.getGlobalBounds().height / 4.f);
			break;

		case 1:
			this->pointer.setPosition(this->cancelText.getGlobalBounds().left - this->pointer.getGlobalBounds().width * 1.2f, this->cancelText.getGlobalBounds().top - this->pointer.getGlobalBounds().height / 4.f);
			break;
		}
	}
}

void GameOverEngine::colorizeOption(int option)
{
	this->yesText.setFillColor(sf::Color::White);
	this->noText.setFillColor(sf::Color::White);
	this->confirmText.setFillColor(sf::Color::White);
	this->cancelText.setFillColor(sf::Color::White);

	sf::Color greeny = sf::Color(122, 224, 124, 255);

	if (this->inSave)
	{
		switch (option)
		{
		case 0:
			this->yesText.setFillColor(greeny);
			break;

		case 1:
			this->noText.setFillColor(greeny);
			break;
		}
	}

	if (this->inNickname)
	{
		switch (option)
		{
		case 0:
			this->confirmText.setFillColor(greeny);
			break;

		case 1:
			this->cancelText.setFillColor(greeny);
			break;
		}
	}
}

void GameOverEngine::setDecision(int decision)
{
	if (this->inSave)
	{
		switch (decision)
		{
		case 0:
			this->inSave = false;
			this->inNickname = true;
			this->setPointer(this->cursorPointerPosition);
			this->colorizeOption(this->cursorPointerPosition);
			return;
			break;

		case 1:
			this->quitDecision = true;
			this->inSave = false;
			this->inNickname = false;
			return;
			break;
		}
	}

	if (this->inNickname)
	{
		switch (decision)
		{
		case 0:
			this->saveDecision = true;
			this->inSave = false;
			this->inNickname = false;
			break;

		case 1:
			this->quitDecision = true;
			this->inSave = false;
			this->inNickname = false;
			break;
		}
	}
}

void GameOverEngine::setCurrentLetter(std::string letter)
{
	switch (this->currentLetter)
	{
	case 0:
		this->letter1.setString(letter);
		this->nickname << letter;
		this->currentLetter++;
		break;

	case 1:
		this->letter2.setString(letter);
		this->nickname << letter;
		this->currentLetter++;
		break;

	case 2:
		this->letter3.setString(letter);
		this->nickname << letter;
		this->currentLetter++;
		break;

	case 3:
		this->letter4.setString(letter);
		this->nickname << letter;
		this->currentLetter++;
		break;

	case 4:
		this->letter5.setString(letter);

		if (this->nickname.str().length() >= 5)
		{
			std::string popper;
			popper = this->nickname.str();
			popper.pop_back();
			this->nickname.str("");
			this->nickname << popper;
			this->nickname << letter;
		}
		else
		{
			this->nickname << letter;
		}
		break;

	default:
		this->letter1.setString(letter);
		this->currentLetter++;
		break;
	}
}

void GameOverEngine::initGameOver()
{
	this->initVariables();
	this->initFont();
	this->initText();
	this->initTextures();
	this->initSprites();
}

void GameOverEngine::updateGameOver()
{
	//QUESTION ABOUT SAVING SUBMENU
	if (this->inSave)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			if (this->cursorPointerPosition != 0)
			{
				--this->cursorPointerPosition;
			}

			this->setPointer(this->cursorPointerPosition);
			this->colorizeOption(this->cursorPointerPosition);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{
				if (this->cursorPointerPosition != 1)
				{
					++this->cursorPointerPosition;
				}

				this->setPointer(this->cursorPointerPosition);
				this->colorizeOption(this->cursorPointerPosition);
		}

		if (this->yesText.getGlobalBounds().contains(this->getMousePos()))
		{
			this->cursorPointerPosition = 0;

			this->setPointer(this->cursorPointerPosition);
			this->colorizeOption(this->cursorPointerPosition);
		}

		if (this->noText.getGlobalBounds().contains(this->getMousePos()))
		{
			this->cursorPointerPosition = 1;

			this->setPointer(this->cursorPointerPosition);
			this->colorizeOption(this->cursorPointerPosition);
		}
	}


	//ENTERING NICKNAME SUBMENU
	if (this->inNickname)
	{
		//Menu logic
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (this->cursorPointerPosition != 0)
			{
				--this->cursorPointerPosition;
			}

			this->setPointer(this->cursorPointerPosition);
			this->colorizeOption(this->cursorPointerPosition);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (this->cursorPointerPosition != 1)
			{
				++this->cursorPointerPosition;
			}

			this->setPointer(this->cursorPointerPosition);
			this->colorizeOption(this->cursorPointerPosition);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
		{
			if (!this->holdBack)
			{
				this->holdBack = true;
				if (this->nickname.str().length() != 0)
				{
					if (this->nickname.str().length() >= 5)
					{
						//this->currentLetter--;

						this->setCurrentLetter("");
					}

					else
					{
						std::string popper;
						popper = this->nickname.str();
						popper.pop_back();
						this->nickname.str("");
						this->nickname << popper;

						this->currentLetter--;

						this->setCurrentLetter("");
						this->currentLetter--;
					}
				}
			}
		}
		else
		{
			this->holdBack = false;
		}


		if (this->confirmText.getGlobalBounds().contains(this->getMousePos()))
		{
			this->cursorPointerPosition = 0;

			this->setPointer(this->cursorPointerPosition);
			this->colorizeOption(this->cursorPointerPosition);
		}

		if (this->cancelText.getGlobalBounds().contains(this->getMousePos()))
		{
			this->cursorPointerPosition = 1;

			this->setPointer(this->cursorPointerPosition);
			this->colorizeOption(this->cursorPointerPosition);
		}

		//Entering Nickname

		//Numbers
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
		{
			if (!this->holdTable[0])
			{
				this->holdTable[0] = true;
				this->setCurrentLetter("1");
			}
		}
		else
		{
			this->holdTable[0] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
		{
			if (!this->holdTable[1])
			{
				this->holdTable[1] = true;
				this->setCurrentLetter("2");
			}
		}
		else
		{
			this->holdTable[1] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
		{
			if (!this->holdTable[2])
			{
				this->holdTable[2] = true;
				this->setCurrentLetter("3");
			}
		}
		else
		{
			this->holdTable[2] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
		{
			if (!this->holdTable[3])
			{
				this->holdTable[3] = true;
				this->setCurrentLetter("4");
			}
		}
		else
		{
			this->holdTable[3] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
		{
			if (!this->holdTable[4])
			{
				this->holdTable[4] = true;
				this->setCurrentLetter("5");
			}
		}
		else
		{
			this->holdTable[4] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
		{
			if (!this->holdTable[5])
			{
				this->holdTable[5] = true;
				this->setCurrentLetter("6");
			}
		}
		else
		{
			this->holdTable[5] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
		{
			if (!this->holdTable[6])
			{
				this->holdTable[6] = true;
				this->setCurrentLetter("7");
			}
		}
		else
		{
			this->holdTable[6] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
		{
			if (!this->holdTable[7])
			{
				this->holdTable[7] = true;
				this->setCurrentLetter("8");
			}
		}
		else
		{
			this->holdTable[7] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
		{
			if (!this->holdTable[8])
			{
				this->holdTable[8] = true;
				this->setCurrentLetter("9");
			}
		}
		else
		{
			this->holdTable[8] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
		{
			if (!this->holdTable[9])
			{
				this->holdTable[9] = true;
				setCurrentLetter("0");
			}
		}
		else
		{
			this->holdTable[9] = false;
		}

		//First letters bar

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			if (!this->holdTable[10])
			{
				this->holdTable[10] = true;
				setCurrentLetter("Q");
			}
		}
		else
		{
			this->holdTable[10] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (!this->holdTable[11])
			{
				this->holdTable[11] = true;
				setCurrentLetter("W");
			}
		}
		else
		{
			this->holdTable[11] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if (!this->holdTable[12])
			{
				this->holdTable[12] = true;
				setCurrentLetter("E");
			}
		}
		else
		{
			this->holdTable[12] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			if (!this->holdTable[13])
			{
				this->holdTable[13] = true;
				setCurrentLetter("R");
			}
		}
		else
		{
			this->holdTable[13] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			if (!this->holdTable[14])
			{
				this->holdTable[14] = true;
				setCurrentLetter("T");
			}
		}
		else
		{
			this->holdTable[14] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			if (!this->holdTable[15])
			{
				this->holdTable[15] = true;
				setCurrentLetter("Y");
			}
		}
		else
		{
			this->holdTable[15] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			if (!this->holdTable[16])
			{
				this->holdTable[16] = true;
				setCurrentLetter("U");
			}
		}
		else
		{
			this->holdTable[16] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			if (!this->holdTable[17])
			{
				this->holdTable[17] = true;
				setCurrentLetter("I");
			}
		}
		else
		{
			this->holdTable[17] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			if (!this->holdTable[18])
			{
				this->holdTable[18] = true;
				setCurrentLetter("O");
			}
		}
		else
		{
			this->holdTable[18] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			if (!this->holdTable[19])
			{
				this->holdTable[19] = true;
				setCurrentLetter("P");
			}
		}
		else
		{
			this->holdTable[19] = false;
		}

		//Second letters bar
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (!this->holdTable[20])
			{
				this->holdTable[20] = true;
				setCurrentLetter("A");
			}
		}
		else
		{
			this->holdTable[20] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (!this->holdTable[21])
			{
				this->holdTable[21] = true;
				setCurrentLetter("S");
			}
		}
		else
		{
			this->holdTable[21] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (!this->holdTable[22])
			{
				this->holdTable[22] = true;
				setCurrentLetter("D");
			}
		}
		else
		{
			this->holdTable[22] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			if (!this->holdTable[23])
			{
				this->holdTable[23] = true;
				setCurrentLetter("F");
			}
		}
		else
		{
			this->holdTable[23] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			if (!this->holdTable[24])
			{
				this->holdTable[24] = true;
				setCurrentLetter("G");
			}
		}
		else
		{
			this->holdTable[24] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			if (!this->holdTable[25])
			{
				this->holdTable[25] = true;
				setCurrentLetter("H");
			}
		}
		else
		{
			this->holdTable[25] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		{
			if (!this->holdTable[26])
			{
				this->holdTable[26] = true;
				setCurrentLetter("J");
			}
		}
		else
		{
			this->holdTable[26] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			if (!this->holdTable[27])
			{
				this->holdTable[27] = true;
				setCurrentLetter("K");
			}
		}
		else
		{
			this->holdTable[27] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			if (!this->holdTable[28])
			{
				this->holdTable[28] = true;
				setCurrentLetter("L");
			}
		}
		else
		{
			this->holdTable[28] = false;
		}

		//Third letters bar
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			if (!this->holdTable[29])
			{
				this->holdTable[29] = true;
				setCurrentLetter("Z");
			}
		}
		else
		{
			this->holdTable[29] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			if (!this->holdTable[30])
			{
				this->holdTable[30] = true;
				setCurrentLetter("X");
			}
		}
		else
		{
			this->holdTable[30] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			if (!this->holdTable[31])
			{
				this->holdTable[31] = true;
				setCurrentLetter("C");
			}
		}
		else
		{
			this->holdTable[31] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			if (!this->holdTable[32])
			{
				this->holdTable[32] = true;
				setCurrentLetter("V");
			}
		}
		else
		{
			this->holdTable[32] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			if (!this->holdTable[33])
			{
				this->holdTable[33] = true;
				setCurrentLetter("B");
			}
		}
		else
		{
			this->holdTable[33] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		{
			if (!this->holdTable[34])
			{
				this->holdTable[34] = true;
				setCurrentLetter("N");
			}
		}
		else
		{
			this->holdTable[34] = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			if (!this->holdTable[35])
			{
				this->holdTable[35] = true;
				setCurrentLetter("M");
			}
		}
		else
		{
			this->holdTable[35] = false;
		}
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

void GameOverEngine::renderGameOver(sf::RenderTarget* target)
{
	if (this->inSave)
	{
		target->draw(this->backgroundSave);
		target->draw(this->yesText);
		target->draw(this->noText);
	}

	if (this->inNickname)
	{
		target->draw(this->backgroundName);
		target->draw(this->confirmText);
		target->draw(this->cancelText);

		target->draw(this->letter1);
		target->draw(this->letter2);
		target->draw(this->letter3);
		target->draw(this->letter4);
		target->draw(this->letter5);
	}

	target->draw(this->pointer);
	target->draw(this->scoreText);
}

const bool GameOverEngine::getDecision(int decision) const
{
	switch (decision)
	{
	case 0:
		return this->quitDecision;
		break;

	case 1:
		return this->saveDecision;
		break;
	}
}

const std::string GameOverEngine::getNickName() const
{
	return this->nickname.str();
}

const sf::Vector2f GameOverEngine::getMousePos() const
{
	sf::Vector2i pos = sf::Mouse::getPosition(*this->window);
	return this->window->mapPixelToCoords(pos);
}

GameOverEngine::GameOverEngine(unsigned*& points, sf::Vector2f windowSize, sf::RenderWindow* window) : points(points)
{
	this->initVariables();
	this->windowSize = windowSize;
	this->window = window;
}

GameOverEngine::~GameOverEngine()
{
}
