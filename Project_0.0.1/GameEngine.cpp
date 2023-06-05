#include "GameEngine.h"

//Private functions
void GameEngine::initVariables()
{
	this->width = 960;
	this->height = 540;
	this->paused = false;
	this->pauseHold = false;
}

void GameEngine::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->width, this->height), "Title", sf::Style::Close);

	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void GameEngine::initPlayer()
{
	this->playerEngine = new PlayerEngine(this->player, this->window->getSize());
	this->playerEngine->initPlayer();
}

void GameEngine::initEnemy()
{
	this->enemiesEngine = new EnemiesEngine(this->window->getSize(), this->enemies);
	this->enemiesEngine->initEnemies();
}

void GameEngine::initCombat()
{
	this->combatEngine = new CombatEngine(this->window->getSize(), this->bullets, this->enemies, this->player);
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

	if (!this->paused)
	{
		this->updatePlayer();
		this->updateEnemy();
		this->updateCombat();
	}
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
	//Pause
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		if (!this->pauseHold)
		{
			if (!this->paused)
			{
				this->paused = true;
			}

			else
			{
				this->paused = false;
			}

			this->pauseHold = true;
		}
	}

	else
	{
		this->pauseHold = false;
	}

	//Run engines functions for input
	if (!this->paused)
	{
		this->playerEngine->Player_Input();
		this->combatEngine->BulletsInput();
	}
}

void GameEngine::updatePlayer()
{
	this->playerEngine->update();
}

void GameEngine::updateCombat()
{
	this->combatEngine->BulletsEnemyHit();
	this->combatEngine->BulletsCulling();
	this->combatEngine->BulletsPlayerHit();
	this->combatEngine->enemyIntersectPlayer();
	this->combatEngine->enemyShoot();
}

void GameEngine::updateEnemy()
{
	this->enemiesEngine->updateEnemies();
}

//Render
void GameEngine::render()
{
	this->window->clear();

	this->player->render(this->window);

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	this->window->display();
}

//Constructors
GameEngine::GameEngine()
{
	this->initVariables();
	this->initWindow();

	this->initPlayer();
	this->initEnemy();
	this->initCombat();
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

	for (auto* i : this->enemies)
	{
		delete i;
	}

	delete this->playerEngine;
	delete this->combatEngine;
	delete this->enemiesEngine;
}
