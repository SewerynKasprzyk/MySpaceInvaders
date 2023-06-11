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

void GameEngine::initMenu()
{
	this->menuEngine = new MenuEngine(this->points, sf::Vector2f(this->window->getSize()));
}

void GameEngine::initPlayer()
{
	this->playerEngine = new PlayerEngine(this->player, this->window->getSize());
	this->playerEngine->initPlayer();
	this->playerEngine->initGUI();
}

void GameEngine::initEnemy()
{
	this->enemiesEngine = new EnemiesEngine(this->window->getSize(), this->enemies, this->ufo);
	this->enemiesEngine->initEnemies();
}

void GameEngine::initCombat()
{
	this->combatEngine = new CombatEngine(this->window->getSize(), this->bullets, this->enemies, this->player, this->ufo, this->explosions);
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
	//this->updateGame();
	this->updateMenu();
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
	//Do if game isn't paused and player is alive
	if (!this->paused && this->player->getState())
	{
		this->playerEngine->Player_Input();
		this->combatEngine->BulletsInput();
	}
}

void GameEngine::updatePlayer()
{
	this->playerEngine->updateGUI();
	this->playerEngine->update();
}

void GameEngine::updateCombat()
{
	//Do if game isn't paused and player is alive
	if ((!this->paused && this->player->getState()))
	{
		this->combatEngine->BulletsEnemyHit();
		this->combatEngine->BulletsCulling();
		this->combatEngine->BulletsPlayerHit();
		this->combatEngine->enemyIntersectPlayer();
		this->combatEngine->enemyShoot();
	}
	
	if(this->player->getState() == false)
	{
		this->combatEngine->playerDeathExplosionSequence();
	}

	this->combatEngine->explosionsRelease();
}

void GameEngine::updateGame()
{
	this->updateInput();

	if (!this->paused && this->player->getState())
	{
		this->updatePlayer();
		this->updateEnemy();
	}
	else
	{
		//When player die still need to adjuste hpBar to 0;
		this->playerEngine->updateGUI();
	}

	this->updateCombat();
}

void GameEngine::updateMenu()
{
	// TO DO ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void GameEngine::updateEnemy()
{
	this->enemiesEngine->updateEnemies();
}

//Render
void GameEngine::render()
{
	this->window->clear();
	
	//this->renderGame();
	this->renderMenu();

	this->window->display();
}

void GameEngine::renderGame()
{
	this->playerEngine->renderGUI(this->window);

	this->player->render(this->window);

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	if (this->ufo != nullptr)
	{
		this->ufo->render(this->window);
	}

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* explosion : this->explosions)
	{
		explosion->render(this->window);
	}
}

void GameEngine::renderMenu()
{
	this->menuEngine->menuRender(this->window);
}

//Constructors
GameEngine::GameEngine()
{
	this->initVariables();
	this->initWindow();

	this->initMenu();
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
	delete this->ufo;

	for (auto* i : this->enemies)
	{
		delete i;
	}

	for (auto* i : this->explosions)
	{
		delete i;
	}

	delete this->points;

	delete this->playerEngine;
	delete this->combatEngine;
	delete this->enemiesEngine;
}
