#pragma once

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <iostream>

#define TMap std::map

using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
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
	FString GetHiddenWord() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	
	
	void Reset(bool);
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 CurrentTry;
	FString HiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	void GetHiddenWordsFromFile();
	FString GetRandomHiddenWord() const;

	std::vector<FString> HiddenWords;
};