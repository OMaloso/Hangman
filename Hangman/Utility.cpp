#include "Utility.h"

std::string Utility::DifficultyEnumToString(eDifficulty _difficulty)
{
	switch (_difficulty)
	{
		case Easy:
		{
			return "Easy";
			break;
		}
		case Medium:
		{
			return "Medium";
			break;
		}
		case Hard:
		{
			return "Hard";
			break;
		}
		default:
		{
			return "Error returning difficulty string. Switch case returned default case.";
			break;
		}
	}
   
}
