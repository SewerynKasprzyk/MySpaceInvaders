#pragma once
#include "GameEngine.h"	
#include <time.h>

#include <Windows.h> 
#include <tchar.h>

int main()
{
	std::cout << "Hello from SFML!" << std::endl;

	GameEngine gameEngine;

	gameEngine.run();

	return 0;
}