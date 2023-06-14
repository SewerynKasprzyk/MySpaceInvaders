#pragma once
#include "GameEngine.h"

//Private functions
void GameEngine::initVariables()
{
	this->width = 960;
	this->height = 540;
	this->paused = false;
	this->pauseHold = true;

	this->points = new unsigned;
	*this->points = 0;

	this->userInMenu = true;
	this->UserRunGame = false;
	this->UserInHiScore = false;
	this->UserInGameOver = false;

	this->deathExplosionEnded = false;

	this->enemies = {};
	this->bullets = {};
	this->explosions = {};
}

void GameEngine::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->width, this->height), "MySpaceInvaders", sf::Style::Close);

	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void GameEngine::initMenu()
{
	this->menuEngine = new MenuEngine(this->points, sf::Vector2f(this->window->getSize()), this->window);
}

void GameEngine::initHiScore()
{
	this->hiScoreEngine = new HiScoreEngine(sf::Vector2f(this->window->getSize()), this->window);
	this->hiScoreEngine->initHiScore();
}

void GameEngine::initPlayer()
{
	this->playerEngine = new PlayerEngine(this->player, this->window->getSize(), this->points);
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

void GameEngine::initGameOver()
{
	this->gameOverEngine = new GameOverEngine(this->points, sf::Vector2f(this->window->getSize()), this->window);
	this->gameOverEngine->initGameOver();
}

void GameEngine::restartInit()
{
	this->initMenu();
	this->initHiScore();
	this->initPlayer();
	this->initEnemy();
	this->initCombat();
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

	if (this->UserRunGame)
	{
		this->updateGame();
	}

	if (this->userInMenu)
	{
		this->updateMenu();
	}

	if (this->UserInHiScore)
	{
		this->updateHiScore();
	}

	if (this->UserInGameOver)
	{
		this->updateGameOver();
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
		if (this->combatEngine->playerDeathExplosionSequence())
		{
			this->UserInGameOver = true;
			this->UserInHiScore = false;
			this->UserRunGame = false;
			this->userInMenu = false;
		}
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
	this->menuEngine->updateMenu();

	//Play decision
	if (this->menuEngine->getDecision(0))
	{
		this->UserRunGame = true;
		this->UserInHiScore = false;
		this->userInMenu = false;
		this->UserInGameOver = false;

		this->initMenu();
	}

	//Hi-Score decision
	if(this->menuEngine->getDecision(1))
	{
		this->UserRunGame = false;
		this->UserInHiScore = true;
		this->userInMenu = false;
		this->UserInGameOver = false;

		this->initMenu();
	}

	//Quit decision
	if (this->menuEngine->getDecision(2))
	{
		this->window->close();
	}
}

void GameEngine::updateHiScore()
{
	this->hiScoreEngine->updateHiScore();

	//back decision
	if (this->hiScoreEngine->getDecision(2))
	{
		this->UserRunGame = false;
		this->UserInHiScore = false;
		this->userInMenu = true;
		this->UserInGameOver = false;

		this->initHiScore();
	}
}

void GameEngine::updateGameOver()
{
	this->gameOverEngine->updateGameOver();

	if (this->gameOverEngine->getDecision(0))
	{
		this->initVariables();

		//this->initMenu();
		this->initHiScore();
		this->initPlayer();
		this->initEnemy();
		this->initCombat();
		this->initGameOver();

		this->UserRunGame = false;
		this->UserInHiScore = true;
		this->userInMenu = false;
		this->UserInGameOver = false;
	}

	if (this->gameOverEngine->getDecision(1))
	{
		HiScoreDB db;

		db.addScore(HiScoreDbElement(this->player->getPoints(), this->gameOverEngine->getNickName()));

		this->initVariables();

		//this->initMenu();
		//this->initHiScore();
		this->initPlayer();
		this->initEnemy();
		this->initCombat();
		this->initGameOver();
		this->initHiScore();

		this->UserRunGame = false;
		this->UserInHiScore = true;
		this->userInMenu = false;
		this->UserInGameOver = false;
	}

}

void GameEngine::updateEnemy()
{
	this->enemiesEngine->updateEnemies();
}

//Render
void GameEngine::render()
{
	this->window->clear();
	
	if (this->UserRunGame)
	{
		this->renderGame();
	}

	if (this->userInMenu)
	{
		this->renderMenu();
	}

	if (this->UserInHiScore)
	{
		this->renderHiScore();
	}

	if (this->UserInGameOver)
	{
		this->renderGameOver();
	}

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

void GameEngine::renderHiScore()
{
	this->hiScoreEngine->hiScoreRender(this->window);
}

void GameEngine::renderGameOver()
{
	this->gameOverEngine->renderGameOver(this->window);
}

//Constructors
GameEngine::GameEngine()
{
	this->initVariables();
	this->initWindow();

	this->initMenu();
	this->initHiScore();
	this->initPlayer();
	this->initEnemy();
	this->initCombat();
	this->initGameOver();
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
	delete this->menuEngine;
	delete this->hiScoreEngine;
	delete this->gameOverEngine;
}