#pragma once

#include <random>
#include <cstdlib>

#include "Language.h"

class Manager
{
public:
	Manager();
	void RunHangman();
	

private:
	std::vector<std::string> languageNames;
	eDifficulty difficulty{ None };
	bool isGameInPlay{ true };
	std::vector<Language> Languages;
	int currentLanguage{ -1 };

	int userInput{ 0 };
	bool hasWonGame{ false };
	std::string currentWord{ "" };

	void LoadWordsFromFile();
	void DisplayAllLanguageInfo();

};

