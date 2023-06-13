#pragma once
#include <string>
#include <sstream>

class HiScoreDbElement
{
	//Private variables
	unsigned int score;
	std::string name;

	//Friends
	friend class HiScoreEngine;

public:

	//Public functions

	//Overload
	friend std::ostream& operator << (std::ostream& output, const HiScoreDbElement& hiScore);

	bool operator < (const HiScoreDbElement& object) const
	{
		return (this->score < object.score);
	}

	bool operator > (const HiScoreDbElement& object) const
	{
		return (this->score > object.score);
	}

	//Constructor
	HiScoreDbElement(unsigned int, std::string);
};

