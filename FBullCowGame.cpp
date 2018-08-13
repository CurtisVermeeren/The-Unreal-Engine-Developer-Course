#include "FBullCowGame.h"


FBullCowGame::FBullCowGame() 
{ 
	GetHiddenWordsFromFile();
	Reset(false); 
}

// Return the users current try
int32 FBullCowGame::GetCurrentTry() const { return CurrentTry; }

// Return the length of the hidden word
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length(); }

// Return the hidden word
FString FBullCowGame::GetHiddenWord() const
{
	return HiddenWord;
}

// Check if the game has been won
bool FBullCowGame::IsGameWon() const 
{ 
	return bGameIsWon;
}

// Return the maximum number of tries
// values scales based on the length of the hidden word
int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{
		{3,4}, {4,6}, {5,8}, {6,10}, {7,12}, {8,14}, {9, 16}
	};

	if (HiddenWord.length() < 3) {
		return 3;
	}
	else if (HiddenWord.length() > 9) {
		return 18;
	}
	return WordLengthToMaxTries[HiddenWord.length()];
}

// Checks that the guess is a valid isogram
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const 
{

	if (!IsIsogram(Guess)) 
	{
		return EGuessStatus::Not_Isogram;
	} 
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) 
	{
		return EGuessStatus::Wrong_Length;
	}
	else 
	{
		return EGuessStatus::OK;
	}
}

// Returns a random isogram for the dictionary of hidden words
FString FBullCowGame::GetRandomHiddenWord() const
{
	std::srand((int32)time(0));
	int32 index = (rand() % HiddenWords.size()) + 1;
	return HiddenWords[index];
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	CurrentTry++;

	FBullCowCount BullCowCount;

	int32 WordLength = HiddenWord.length();
	for (int32 HWChar = 0; HWChar < WordLength; HWChar++) {
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
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

	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

void FBullCowGame::GetHiddenWordsFromFile()
{
	std::ifstream IsogramFile("isograms.txt");
	std::string Line;

	while (std::getline(IsogramFile, Line))
	{
		HiddenWords.push_back(Line);
	}
}

void FBullCowGame::Reset(bool SameWord)
{
	if (!SameWord)
	{
		const FString HIDDEN_WORD = GetRandomHiddenWord();
		HiddenWord = HIDDEN_WORD;
	}

	CurrentTry = 1;

	bGameIsWon = false;
}
