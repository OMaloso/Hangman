#pragma once

#include <iostream>
#include <fstream> 
#include <vector>
#include <string>

enum eDifficulty
{
	Easy,
	Medium,
	Hard,
	None
};

class Utility
{
public:
	static std::string DifficultyEnumToString(eDifficulty _difficulty);

};

