#pragma once
#include "HiScore.h"
#include "HiScoreDbElement.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <regex>

class HiScoreDB
{
	//Private variables
	std::vector<HiScoreDbElement> dbElements;

	std::fstream file;
	std::string path, line;

	//Private functions
	void saveDB();
	void readDB();
	void sort();
	void checkSavePath();

public:

	//Public functions
	void reloadDB();
	void addScore(HiScoreDbElement);

	//Accesors
	const std::vector<HiScoreDbElement> getVector() const;

	//Constructor
	HiScoreDB(std::string = ".\\Saves\\save.txt");
	
	//Destructor
	virtual ~HiScoreDB();
};

