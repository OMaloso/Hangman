#include "Manager.h"

Manager::Manager()
{
}

void Manager::RunHangman()
{
	LoadWordsFromFile();

	while (currentLanguage == -1)
	{
		std::cout << "Hangman" << std::endl;
		std::cout << std::endl;
		std::cout << "Choose a language:" << std::endl;
		for (int i = 0; i < languageNames.size(); i++)
		{
			std::cout << i + 1 << ": " << languageNames[i] << std::endl;
		}

		std::cin >> userInput;
		std::cout << std::endl;

		if (userInput < 1 || userInput > languageNames.size() + 1)
		{
			std::cout << "Incorrect option. Please input value between 1 and " << languageNames.size() << std::endl;
		}
		else
		{
			currentLanguage = userInput - 1;
		}
	}

	while (isGameInPlay)
	{
		while (difficulty == None)
		{
			std::cout << "Do you want to play easy or hard?" << std::endl;
			std::cout << "1: Easy" << std::endl;
			std::cout << "2: Medium" << std::endl;
			std::cout << "3: Hard" << std::endl;

			std::cin >> userInput;
			std::cout << std::endl;

			if (userInput == 1)
			{
				difficulty = Easy;
			}
			else if (userInput == 2)
			{
				difficulty = Medium;
			}
			else if (userInput == 3)
			{
				difficulty = Hard;
			}
			else
			{
				std::cout << "Incorrect option. Please input value between 1 and 3." << std::endl;
			}
		}

		std::cout << currentLanguage << std::endl;
		std::cout << Utility::DifficultyEnumToString(difficulty) << std::endl;

		// Seed random number
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<> dis;
		int randomNumber{ 1 };

		// Specify values
		switch (difficulty)
		{
			case Easy:
			{
				int randomNumberSize = Languages[currentLanguage].GetEasyWords().size();

				if (randomNumberSize > 0)
				{
					std::uniform_int_distribution<> dis(0, randomNumberSize);

					// Generate a random number
					randomNumber = dis(gen);
					std::cout << "RNUM: " << randomNumber << std::endl;
				}
				else
				{
					std::cout << "Error: No words available in file" << std::endl;
					break;
				}

				currentWord = Languages[currentLanguage].GetEasyWords()[randomNumber];
				break;
			}
			case Medium:
			{
				int randomNumberSize = Languages[currentLanguage].GetMediumWords().size();

				if (randomNumberSize > 0)
				{
					std::uniform_int_distribution<> dis(0, randomNumberSize);

					// Generate a random number
					randomNumber = dis(gen);
					std::cout << "RNUM: " << randomNumber << std::endl;
				}
				else
				{
					std::cout << "Error: No words available in file" << std::endl;
					break;
				}

				currentWord = Languages[currentLanguage].GetMediumWords()[randomNumber];
				break;
			}
			case Hard:
			{
				int randomNumberSize = Languages[currentLanguage].GetHardWords().size();

				if (randomNumberSize > 0)
				{
					std::uniform_int_distribution<> dis(0, randomNumberSize);

					// Generate a random number
					randomNumber = dis(gen);
					std::cout << "RNUM: " << randomNumber << std::endl;
				}
				else
				{
					std::cout << "Error: No words available in file" << std::endl;
					break;
				}

				currentWord = Languages[currentLanguage].GetHardWords()[randomNumber];
				break;
			}
			default:
			{
				// Default
			}
		}

		std::vector<char> wordCharacters;


		while (!hasWonGame)
		{
			system("cls");
			std::cout << std::endl;
		}
	}
}

void Manager::LoadWordsFromFile()
{
	// Load languages file
	std::ifstream inputFile("Data/Languages.txt");
	std::string stringLine;

	if (!inputFile.is_open())
	{
		std::cout << "Failed to load file: Languages.txt" << std::endl;
	}

	while (getline(inputFile, stringLine))
	{
		languageNames.push_back(stringLine);
	}

	// Load words
	for (int i = 0; i < languageNames.size(); i++)
	{
		Language language(languageNames[i]);
		Languages.push_back(language);
	}
	std::cout << std::endl;


	//DisplayAllLanguageInfo();
}

void Manager::DisplayAllLanguageInfo()
{
	for (int i = 0; i < Languages.size(); i++)
	{
		Languages[i].DisplayLanguageInfo();
	}
}
