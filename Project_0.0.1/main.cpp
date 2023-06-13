#pragma once
#include "GameEngine.h"	
#include <time.h>

int main()
{
	std::cout << "Hello from SFML!" << std::endl;

	GameEngine gameEngine;

	gameEngine.run();

	return 0;
}