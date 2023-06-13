#include "HiScoreDbElement.h"

HiScoreDbElement::HiScoreDbElement(unsigned int score, std::string name)
{
	this->score = score;
	this->name = name;
}

std::ostream& operator<<(std::ostream& output, const HiScoreDbElement& hiScore)
{
	output << hiScore.name << "|" << hiScore.score << std::endl;
	return output;
}
