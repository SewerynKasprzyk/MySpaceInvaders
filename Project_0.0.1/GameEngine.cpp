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
	this->enemiesEngine->initEnemies();
}

void GameEngine::initEngines()
{
	this->playerEngine = new PlayerEngine(this->player);
	this->bulletsEngine = new BulletsEngine(&this->bullets, this->player);
	this->enemiesEngine = new EnemiesEngine(this->window->getSize(), &this->enemiesRow0, &this->enemiesRow1, &this->enemiesRow2, &this->enemiesRow3, &this->enemiesRow4);
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
		if ((ev.Event::type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) || (ev.type == sf::Event::Closed))
		{
			this->window->close();
		}
	}
}

void GameEngine::updateInput()
{
	//Run engines functions for input
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

	for (auto* enemy : this->enemiesRow0)
	{
		enemy->render(this->window);
	}

	for (auto* enemy : this->enemiesRow1)
	{
		enemy->render(this->window);
	}

	for (auto* enemy : this->enemiesRow2)
	{
		enemy->render(this->window);
	}

	for (auto* enemy : this->enemiesRow3)
	{
		enemy->render(this->window);
	}

	for (auto* enemy : this->enemiesRow4)
	{
		enemy->render(this->window);
	}

	//this->enemy->render(this->window);

	this->window->display();
}

//Constructors
GameEngine::GameEngine()
{
	this->initVariables();
	this->initWindow();

	this->initPlayer();

	this->initEngines();

	this->initEnemy();
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

	for (auto* i : this->enemiesRow0)
	{
		delete i;
	}

	for (auto* i : this->enemiesRow1)
	{
		delete i;
	}

	for (auto* i : this->enemiesRow2)
	{
		delete i;
	}

	for (auto* i : this->enemiesRow3)
	{
		delete i;
	}

	for (auto* i : this->enemiesRow4)
	{
		delete i;
	}

	delete this->playerEngine;
	delete this->bulletsEngine;
	delete this->enemiesEngine;
}
