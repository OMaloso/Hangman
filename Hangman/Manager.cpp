#include "Manager.h"

Manager::Manager()
{
}

void Manager::RunHangman()
{
	LoadWordsFromFile();

	SelectLanguage();

	numberOfGuesses = maxNumberOfGuesses;

	while (isGameInPlay)
	{
		hasFinishedGame = false;
		while (difficulty == None)
		{
			system("cls");
			std::cout << "Hangman" << std::endl;
			std::cout << std::endl;

			std::cout << "Do you want to play easy or hard?" << std::endl;
			std::cout << "1: Easy" << std::endl;
			std::cout << "2: Medium" << std::endl;
			std::cout << "3: Hard" << std::endl;
			std::cout << std::endl;
			std::cout << "0: Quit" << std::endl;

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
			else if (userInput == 0)
			{
				exit(0);
			}
			else if (std::cin.fail())
			{
				std::cout << "Incorrect option. Please input value between 1 and 3." << std::endl;
				std::cin.clear(); // Clear error flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
				EnterToContinue(false);
			}
			else
			{
				std::cout << "Incorrect option. Please input value between 1 and 3." << std::endl;
				EnterToContinue(false);
			}
		}

		//std::cout << currentLanguage << std::endl;
		//std::cout << Utility::DifficultyEnumToString(difficulty) << std::endl;

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
					std::uniform_int_distribution<> dis(1, randomNumberSize - 1);

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
					std::uniform_int_distribution<> dis(1, randomNumberSize - 1);

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
					std::uniform_int_distribution<> dis(1, randomNumberSize - 1);

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

		// Get letters from string and add to a vector
		std::vector<char> wordCharacters;
		std::cout << "Word: " << currentWord << std::endl;

		for (int i = 0; i < currentWord.length(); ++i)
		{
			char character = currentWord[i];
			wordCharacters.push_back(character);
		}

		for (int i = 0; i < wordCharacters.size(); ++i)
		{
			std::cout << wordCharacters[i];
		}
		std::cout << std::endl;

		// Vector of guessed letters
		std::vector<char> guessedCharacters;

		while (!hasFinishedGame)
		{
			system("cls");
			std::cout << std::endl;

			DrawHangman7Guesses();

			// Check for a loss
			if (numberOfGuesses <= 0)
			{
				std::cout << "You have run out of guesses. Game Over" << std::endl;
				std::cout << std::endl;
				std::cout << "The correct answer was: " << currentWord << std::endl;
				Reset();
				hasFinishedGame = true;

				std::cout << std::endl;
				std::cout << "Press Enter to continue...";
				std::cin.get();

				continue;
			}

			// Show letters (or _ if unguessed)
			for (int i = 0; i < wordCharacters.size(); i++)
			{
				bool haveFoundLetter{ false };
				for (int j = 0; j < guessedCharacters.size(); j++)
				{
					if (guessedCharacters[j] == wordCharacters[i])
					{
						std::cout << wordCharacters[i] << " ";
						haveFoundLetter = true;
						break;
					}	
				}
				if (!haveFoundLetter)
					std::cout << "_ ";
			}

			// Check for a win
			int numberOfCharacters = 0;
			for (int i = 0; i < wordCharacters.size(); i++)
			{
				for (int j = 0; j < guessedCharacters.size(); j++)
				{
					if (guessedCharacters[j] == wordCharacters[i])
					{
						numberOfCharacters++;
						break;
					}
				}
			}
			if (numberOfCharacters >= wordCharacters.size())
			{
				std::cout << std::endl;
				std::cout << std::endl;
				std::cout << "You Win!" << std::endl;
				Reset();

				std::cout << std::endl;
				std::cout << "Press Enter to continue...";
				std::cin.get();

				continue;
			}

			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "Guessed letters: ";
			for (int i = 0; i < guessedCharacters.size(); i++)
			{
				std::cout << guessedCharacters[i] << ", ";
			}
			std::cout << std::endl;
			std::cout << "You have " << numberOfGuesses << " guesses left." << std::endl;
			std::cout << std::endl;

			std::string guessedLetter;
			std::cout << "Guess a letter: ";
			std::cin >> guessedLetter;

			if (guessedLetter.length() != 1)
			{
				std::cout << "Please guess one character at a time" << std::endl;
			}
			else
			{
				char guessedCharacter = guessedLetter.at(0);
				if (!std::isalpha(guessedCharacter))
				{
					std::cout << "Please use letters only. Try again." << std::endl;
				}
				else
				{
					// Check if letter is already in the guessed vector
					bool isLetterFound{ false };
					for (int i = 0; i < guessedCharacters.size(); i++)
					{
						if (guessedCharacter == guessedCharacters[i])
						{
							isLetterFound = true;
						}
					}

					if (isLetterFound)
					{
						std::cout << "Letter already guessed. Try another." << std::endl;
					}
					else
					{
						bool isLetterCorrect{ false };
						for (int i = 0; i < wordCharacters.size(); i++)
						{
							if (guessedCharacter == wordCharacters[i])
							{
								isLetterCorrect = true;
							}
						}
			
						if (isLetterCorrect)
						{
							std::cout << guessedCharacter << " was correct!" << std::endl;
						}
						else
						{
							std::cout << guessedCharacter << " was incorrect." << std::endl;
							numberOfGuesses--;
						}
						guessedCharacters.push_back(guessedCharacter);
					}
				}
			}

			EnterToContinue(true);
		}
	}
}

void Manager::LoadWordsFromFile()
{
	// Load file
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

void Manager::SelectLanguage()
{
	while (currentLanguage == -1)
	{
		std::cout << "Choose a language:" << std::endl;
		for (int i = 0; i < languageNames.size(); i++)
		{
			std::cout << i + 1 << ": " << languageNames[i] << std::endl;
		}
		std::cout << std::endl;
		std::cout << "0: Quit" << std::endl;

		std::cin >> userInput;
		std::cout << std::endl;

		if (userInput == 0)
		{
			exit(0);
		}
		else if (userInput < 1 || userInput > languageNames.size() + 1 || std::cin.fail())
		{
			std::cout << "Incorrect option. Please input value between 1 and " << languageNames.size() << std::endl;
			std::cin.clear(); // Clear error flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
		}
		else
		{
			currentLanguage = userInput - 1;
		}
	}
}

void Manager::DisplayAllLanguageInfo()
{
	for (int i = 0; i < Languages.size(); i++)
	{
		Languages[i].DisplayLanguageInfo();
	}
}

void Manager::Reset()
{
	difficulty = None;
	userInput = 0;
	hasFinishedGame = true;
	currentWord = "";
	numberOfGuesses = maxNumberOfGuesses;
}

void Manager::DrawHangman7Guesses()
{
	if (maxNumberOfGuesses != 7)
		return;

	// Draw hangman
	std::cout << "|";
	if (numberOfGuesses <= 6)
		std::cout << "-----" << std::endl;
	else
		std::cout << std::endl;

	std::cout << "|";
	if (numberOfGuesses <= 5)
		std::cout << "    o" << std::endl;
	else
		std::cout << std::endl;

	std::cout << "|";
	if (numberOfGuesses == 4)
		std::cout << "    |" << std::endl;
	else if (numberOfGuesses == 3)
		std::cout << "   /|" << std::endl;
	else if (numberOfGuesses <= 2)
		std::cout << "   /|\\" << std::endl;
	else
		std::cout << std::endl; 
	
	std::cout << "|";
	if (numberOfGuesses <= 4)
		std::cout << "    |" << std::endl; 
	else
		std::cout << std::endl;
	
	std::cout << "|";
	if (numberOfGuesses == 1)
		std::cout << "   /" << std::endl;
	else if (numberOfGuesses <= 0)
		std::cout << "   / \\" << std::endl;
	else
		std::cout << std::endl;

	std::cout << "|" << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
}

void Manager::EnterToContinue(bool _clearInput)
{
	std::cout << std::endl;
	std::cout << "Press Enter to continue...";
	if (_clearInput)
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
		std::cin.get();
	}
}
