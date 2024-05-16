#pragma once

#include "Utility.h"

class Language
{
public:
	Language(std::string _languageName);
	void DisplayLanguageInfo();

	std::string GetLanguageName() { return languageName; }
	std::string GetFilename() { return fileName; }
	std::vector<std::string> GetEasyWords() { return easyWords; }
	std::vector<std::string> GetMediumWords() { return mediumWords; }
	std::vector<std::string> GetHardWords() { return hardWords; }

private:
	std::string languageName{ "" };
	std::string fileName{ "" };
	std::vector<std::string> easyWords;
	std::vector<std::string> mediumWords;
	std::vector<std::string> hardWords;

	void LoadWords();
};

