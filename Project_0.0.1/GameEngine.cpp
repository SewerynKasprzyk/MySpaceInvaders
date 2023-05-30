#include "GameEngine.h"

//Private functions
void GameEngine::initVariables()
{
	this->width = 960;
	this->height = 540;
}

void GameEngine::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->width, this->height), "Title", sf::Style::Close);

	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void GameEngine::initPlayer()
{
	this->player = new Player(this->width, this->height);
}

void GameEngine::initEnemy()
{
	this->enemy = new Enemy(0.f, 0.f);
}

void GameEngine::initEngines()
{
	this->playerEngine = new PlayerEngine(this->player);
	this->bulletsEngine = new BulletsEngine(&this->bullets, this->player);
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
	this->playerEngine->Player_Input();

	this->bulletsEngine->BulletsInput();
}

void GameEngine::updateBullets()
{
	bulletsEngine->BulletsCulling();
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

	this->initPlayer();
	this->initEnemy();

	this->initEngines();
}

//Destructors
GameEngine::~GameEngine()
{
	delete this->window;
	delete this->player;

	for (auto* i : this->bullets)
	{
		delete i;
	}

	delete this->enemy;

	delete this->playerEngine;
	delete this->bulletsEngine;
}
