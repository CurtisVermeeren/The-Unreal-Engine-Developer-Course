#include "FBullCowGame.h"


FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MaxTries; }

int32 FBullCowGame::GetCurrentTry() const { return CurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return false; }

EWordStatus FBullCowGame::CheckGuessValidity(FString) const 
{

	return EWordStatus::OK;
}

FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	CurrentTry++;

	FBullCowCount BullCowCount;

	int32 HiddenWordLength = HiddenWord.length();
	for (int32 HWChar = 0; HWChar < HiddenWordLength; HWChar++) {
		for (int32 GChar = 0; GChar < ; GChar++) {
			// Characters Match
			if (Guess[GChar] == HiddenWord[HWChar]) {
				// Match in the same place
				if (HWChar == GChar) {
					BullCowCount.Bulls++;
				}
				// Match in a different place
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	return BullCowCount;
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	HiddenWord = HIDDEN_WORD;

	CurrentTry = 1;
}
