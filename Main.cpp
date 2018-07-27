#include <iostream>
#include <string>

#include "FBullCowGame.h"

using FString = std::string;
using int32 = int32;

void PrintIntro();
void PlayGame();
FString GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

int32 main() 
{
	bool PlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		PlayAgain = AskToPlayAgain();
	} while (PlayAgain);
	
	return 0;
}

void PlayGame() 
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();
	for (int32 i = 0; i < MaxTries; i++) {
		FString Guess = GetGuess();		// TODO 
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		std::cout << "Bulls= " << BullCowCount.Bulls << "\nCows= " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}

	// TODO summarize game 
}

// Introduce the game
void PrintIntro() 
{

	std::cout << "Welcome to Bulls and Cows\n"
		"Can you guess the " << BCGame.GetHiddenWordLength() <<
		" letter isogram I'm thinking of?" << std::endl;
	return;
}

// Get a guess from the player
FString GetGuess() 
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	std::cout << "Try " << CurrentTry << ". Enter your guess." << std::endl;
	FString Guess = "";
	std::getline(std::cin, Guess);
	return Guess;
}

bool AskToPlayAgain() 
{
	std::cout << "Do you want to play again? (y/n)" << std::endl;
	FString Response;
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}