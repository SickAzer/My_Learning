
/* This is the console executeble, that make use of thó BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction. 
For game logic see the FBullCowGame class.

*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside of a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays 

// introduce the game

// the entry point for our application

int main()
{
    // std::cout << "Your current try is " << BCGame.GetCurrentTry() << "\n";
    bool bPlayAgain = false;
    do
    {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    } 
    while (bPlayAgain);


    return 0; // exit the application
}

// plays a single game to completion
void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();

    // loop  asking for guesses while the game is Not won
    // if there are still tries remaining


    do 
    {
        FText Guess = GetValidGuess(); 

        // submit valid guess to the game, and recieve counts
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls =  " << BullCowCount.Bulls;
        std::cout << ". Cows =  " << BullCowCount.Cows << "\n\n";
    } while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries);

    PrintGameSummary();
    return;
}

void PrintIntro() 
{
    std::cout << "MM                   MM                                     \n";
    std::cout << "MMM+                8MM                                     \n";
    std::cout << "MMMMMM            :MMM                        MM,     ZMM   \n";
    std::cout << "ZMMM+MMMM+       MMMM                         MMMO  MMMMM   \n";
    std::cout << "   MMM  MMMMMMMMMMMN                            MMMMMMMZ    \n";
    std::cout << "    MMMMM   MMMMMMMMM                        ZMMMZMZ, MMMMMM\n";
    std::cout << "      $MMD  MMM    MMMMMMM         MMMMMMMMMMMMM         MMM\n";
    std::cout << "777MMMMDI               I7MMM~  7MMMIIIIIII+                \n";
    std::cout << "MMM?                       MMM +MM                          \n";
    std::cout << "                           ZMM +M+                          \n";
    std::cout << "        B U L L S          MMM  MM            C O W S       \n";
    std::cout << "                     MMMMMMMO    MMMMMMM                    \n";
    std::cout << "               ZMMMMMMMM               MMMMM                \n";
    std::cout << "             MMMM                         MMMMM             \n";
    std::cout << "            MMM                               MMMMM         \n";
    std::cout << "           MMO                                   MM,        \n";
    std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght() << " letter isogram I`m thinking of?\n";
    std::cout << std::endl;
    return;
}

// loop continually until the user gives a valid guess

FText GetValidGuess() 
{
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::invalid_status;
    do {
        // get a guess from the player
        int CurrentTry = BCGame.GetCurrentTry();

        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
        std::cout << ". Enter your guess: ";
        std::getline(std::cin, Guess);
        Status = BCGame.CheckGuessValidity(Guess);

        switch (Status)
        {
        case EGuessStatus::Wrong_Lenght:
            std::cout << "Plaese enter a " << BCGame.GetHiddenWordLenght() << " letter word. \n\n";
            break;
        case EGuessStatus::Not_Isogram:
            std::cout << "Please enter a isogram (all letters should be unique)" << "\n\n";
            break;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Please enter a word with lowercase" << "\n\n";
            break;
        default:
            // assume the guess is valid
            break;
        }
    } while (Status != EGuessStatus::OK); // keep looping until we get no errors
    return Guess;

}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word (y/n)?";
    FText Response = "";
    std::getline(std::cin, Response);
    std::cout << "\n\n";
    return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "Congratulations! You have won!!!\n";
    }
    else
    {
        std::cout << "Sorry, but you lose... Better luck next time!\n";
    }
    return;
}
