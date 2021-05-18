#pragma once

#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map 
using int32 = int; 

FBullCowGame::FBullCowGame () { Reset(); } // default constructor


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameisWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLenghtToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15} };

	return WordLenghtToMaxTries[MyHiddenWord.length()] ; 
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "dubli"; // this must be an isogram

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameisWon - false;
	return;
}




 EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	 if (!IsIsogram(Guess)) // if the guess isn't an isogram
	 {
		 return EGuessStatus::Not_Isogram; 
	 }
	 else if (!IsLowerCase(Guess)) // if the guess isn't all lowercase //TODO write function
	 {
		 return EGuessStatus::Not_Lowercase; 
	 }
	 else if (Guess.length() != GetHiddenWordLenght()) // if the guess length is wrong
	 {
		 return EGuessStatus::Wrong_Lenght;
	 }
	 else // otherwise
	 {
		 return EGuessStatus::OK;
	 }
}

// recieves a VALID guess, incriments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLenght = MyHiddenWord.length(); // assuming same lenght as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLenght; MHWChar++) 
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLenght; GChar++) 
		{
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				if (MHWChar == GChar) 
				{  //if they're the same place
					BullCowCount.Bulls++; // incriment bulls
				}
				else 
				{
					BullCowCount.Cows++; // increment cows if not
			
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLenght) {
		bGameisWon = true;
	}
	else {
		bGameisWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }


	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) {
			return false; //we do not have an isogram
		}
		else {
			LetterSeen[Letter] = true;
		}

	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) //
	{
		if (!islower(Letter))// if not a lower case letter
		{
			return false;
		}
	}
	return true;
}
