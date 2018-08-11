#include <iostream>
#include <string>

#include "FBullCowGame.h"

using FString = std::string;
using int32 = int32;

void PrintIntro();
void PrintGameSummary();
void PlayGame();
FString GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

int32 main() 
{
	bool PlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		PlayAgain = AskToPlayAgain();
	} while (PlayAgain);
	
	return 0;
}

void PlayGame() 
{
	int32 MaxTries = BCGame.GetMaxTries();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FString Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << ". Cows = " << BullCowCount.Cows << ".\n\n";
	}
	
}

// Introduce the game
void PrintIntro() 
{
	std::cout << "***********************************************\n";
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "***********************************************\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n" << std::endl;
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE YOU WIN!\n";
	}
	else {
		std::cout << "Better luck next time!\n";
	}
}

// Get a guess from the player
FString GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FString Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowecase letters.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain() 
{
	std::cout << "Do you want to play again? (y/n) ";
	FString Response;
	std::getline(std::cin, Response);

	if ((Response[0] == 'y' || Response[0] == 'Y')  && !BCGame.IsGameWon()) {
		std::cout << "\nPlay again with the same hidden word? (y/n) ";
		FString Response2;
		std::getline(std::cin, Response2);
		if (Response2[0] == 'y' || Response2[0] == 'Y') {
			BCGame.Reset(true);
		}
		else {
			std::cout << "\nThe hidden word was : " << BCGame.GetHiddenWord() << "\n\n";
			BCGame.Reset(false);
		}
	}
	else if (!(Response[0] == 'y' || Response[0] == 'Y') && !BCGame.IsGameWon()) {
		std::cout << "\nThe hidden word was : " << BCGame.GetHiddenWord() << "\n\n";
	}
	else {
		BCGame.Reset(false);
	}

	return (Response[0] == 'y' || Response[0] == 'Y');
}