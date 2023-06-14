#include "HiScoreDB.h"

void HiScoreDB::saveDB()
{
	this->file.open(this->path, std::ios::out | std::ofstream::trunc);

	if (file.good() == false)
	{
		std::cout << "ERROR: CAN'T OPEN SAVE FILES";
	}

	for (auto &element : this->dbElements)
	{
		this->file << element;
	}

	file.close();
}

void HiScoreDB::readDB()
{	
	this->dbElements = {};
	this->file.open(this->path, std::ios::in);

	if (this->file.good() == false)
	{
		std::cout << "ERROR: CAN'T OPEN SAVE FILES!";
	}

	while (getline(this->file, this->line))
	{
		std::string string1;
		std::stringstream stream1;
		stream1 << this->line;

		while (getline(stream1, string1))
		{
			std::string name = {};
			unsigned int score = 0;

			std::stringstream stream2;
			stream2 << string1;

			std::string string2;

			// If true -> name | if false -> score
			bool nameOrScore = true;

			while (getline(stream2, string2, '|'))
			{
				std::regex rgx;
				std::smatch match;

				switch (nameOrScore)
				{
				case true:

					rgx = ("([a-zA-Z0-9]{3,5})");

					if (std::regex_search(string2, match, rgx)) 
					{
						name = match[0];
					}
					else
					{
						name = "?\\";
					}

					nameOrScore = false;
					break;

				case false:

					rgx = ("([0-9]{1,9})");

					if (std::regex_search(string2, match, rgx))
					{
						score = stoi(match[0]);
					}
					else
					{
						name = "?~";
						score = 0;
					}

					nameOrScore = true;
					break;
				}
			}
			
			HiScoreDbElement element(score, name);
			this->dbElements.push_back(element);
		}
	}

	file.close();

	this->sort();
}

void HiScoreDB::sort()
{
	std::sort(this->dbElements.begin(), this->dbElements.end(), std::greater<HiScoreDbElement>());
}

void HiScoreDB::checkSavePath()
{
	//Add save folders if there's not
	std::filesystem::path path = std::filesystem::path(this->path);

	if (!std::filesystem::exists(path))
	{
		std::cout << "ERROR: THERE'S NO SAVES AT SAVE PATH!" << std::endl << "TRYING TO CREATE NEW SAVE DIRECTORY AND FILE" << std::endl << "IF THIS ERROR CONSTANTLY POP UP CHECK READ/SAVE ACCESS IN GAME FILES PATH" << std::endl << "IF IT'S FIRST GAME RUN IGNORE THIS ERROR" << std::endl;

		std::filesystem::create_directories(path.parent_path());

		this->file.open(this->path, std::ios::out);

		if (file.good() == false)
		{
			std::cout << "ERROR: CAN'T OPEN SAVE FILES";
		}

		file.close();
	}

}

void HiScoreDB::reloadDB()
{
	//this->dbElements = {};
	this->saveDB();
}

void HiScoreDB::addScore(HiScoreDbElement element)
{
	//this->readDB();

	this->dbElements.push_back(element);
	this->sort();
	this->saveDB();
}

const std::vector<HiScoreDbElement> HiScoreDB::getVector() const
{
	return this->dbElements;
}

HiScoreDB::HiScoreDB(std::string path)
{
	this->path = path;
	this->checkSavePath();
	this->readDB();
}

HiScoreDB::~HiScoreDB()
{
	this->reloadDB();
}
