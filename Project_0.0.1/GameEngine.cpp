#include "GameEngine.h"

//Private functions
void GameEngine::initVariables()
{
	this->width = 960;
	this->height = 540;
	this->hold = false;
	this->hold_aproved = false;
	this->bullet_type = false;
}

void GameEngine::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->width, this->height), "Title", sf::Style::Close);

	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void GameEngine::initTextures()
{
	this->textures["BULLET_01"] = new sf::Texture();
	this->textures["BULLET_01"]->loadFromFile(".\\Textures\\Laser_Sprites\\11.png");

	this->textures["BULLET_02"] = new sf::Texture();
	this->textures["BULLET_02"]->loadFromFile(".\\Textures\\Laser_Sprites\\12.png");
}

void GameEngine::initPlayer()
{
	this->player = new Player(this->width, this->height);
}

void GameEngine::initEnemy()
{
	this->enemy = new Enemy(0.f, 0.f);
}

void GameEngine::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void GameEngine::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->player->update();
	this->updateBullets();
}

void GameEngine::updatePollEvents()
{
	//Poll event
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed || (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape))
		{
			this->window->close();
		}
	}
}

void GameEngine::updateInput()
{

	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
	{
		this->player->move(-1.f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
	{
		this->player->move(1.f, 0.f);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
	{
		if (!this->hold && this->player->readyToShoot())
		{
			if (!hold_aproved)
			{
				this->hold = true;
			}

			if (bullet_type)
			{
				this->bullets.push_back(new Bullet(this->textures["BULLET_01"], this->player->getPos().x, this->player->getPos().y, 0.f, -1.f, 5.f));
				bullet_type = false;
			}
			else
			{
				this->bullets.push_back(new Bullet(this->textures["BULLET_02"], this->player->getPos().x, this->player->getPos().y, 0.f, -1.f, 5.f));
				bullet_type = true;
			}
		}
	}

	else
	{
		this->hold = false;
	}

}

void GameEngine::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete Bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;

			std::cout << "Bullets counter: " << this->bullets.size() << std::endl;
		}

		++counter;
	}
}

void GameEngine::updateEnemy()
{
}

void GameEngine::render()
{
	this->window->clear();

	//Draw all the stuffs

	this->player->render(this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	this->enemy->render(this->window);

	this->window->display();
}

//Constructors
GameEngine::GameEngine()
{
	this->initVariables();
	this->initWindow();
	this->initTextures();
	this->initPlayer();
	this->initEnemy();
}

//Destructors
GameEngine::~GameEngine()
{
	delete this->window;
	delete this->player;

	for (auto& i : this->textures)
	{
		delete i.second;
	}

	for (auto* i : this->bullets)
	{
		delete i;
	}
}
