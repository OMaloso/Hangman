#include "Language.h"

Language::Language(std::string _languageName)
{
	languageName = _languageName;

	LoadWords();
}

void Language::DisplayLanguageInfo()
{
	std::cout << GetLanguageName() << std::endl;
	std::cout << GetFilename() << std::endl;

	for (int j = 0; j < GetEasyWords().size(); j++)
	{
		std::cout << GetEasyWords()[j] << std::endl;
	}
	for (int j = 0; j < GetMediumWords().size(); j++)
	{
		std::cout << GetMediumWords()[j] << std::endl;
	}
	for (int j = 0; j < GetHardWords().size(); j++)
	{
		std::cout << GetHardWords()[j] << std::endl;
	}
	std::cout << std::endl;
}

void Language::LoadWords()
{
	fileName = "Data/" + languageName + ".txt";

	std::ifstream inputFile(fileName);
	std::string stringLine;

	std::cout << "Loading " << languageName << " file..." << std::endl;

	if (!inputFile.is_open())
	{
		std::cout << "Failed to load " << fileName << " file." << std::endl;
	}
	
	eDifficulty difficulty{ Easy };

	while (getline(inputFile, stringLine))
	{
		if (stringLine == "===Easy===")
		{
			difficulty = Easy;
		}
		else if (stringLine == "===Medium===")
		{
			difficulty = Medium;
		}
		else if (stringLine == "===Hard===")
		{
			difficulty = Hard;
		}
	
		switch (difficulty)
		{
			case Easy:
			{
				easyWords.push_back(stringLine);
				break;
			}
			case Medium:
			{
				mediumWords.push_back(stringLine);
				break;
			}
			case Hard:
			{
				hardWords.push_back(stringLine);
				break;
			}
			default:
			{
				// Default
			}
		}
	}
}
