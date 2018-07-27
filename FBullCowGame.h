#pragma once

#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus {
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
};

enum class EResetStatus {
	No_Hidden_Word,
	OK,
};

class FBullCowGame 
{
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EWordStatus CheckGuessValidity(FString) const;
	
	void Reset();
	FBullCowCount SubmitGuess(FString);

private:
	int32 CurrentTry;
	int32 MaxTries;
	FString HiddenWord;
};