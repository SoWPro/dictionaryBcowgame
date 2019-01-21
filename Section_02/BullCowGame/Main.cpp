/*This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame Class.
*/

//#include "stdafx.h"
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make unreal friendly
using FText = std::string;
using int32 = int;
int32 Userchoice = 0;

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetvalidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
int GetWordLength();

FBullCowGame BCGame; //instantiate a new game, which we re-use across plays



//initials or starts the application
int main()
{
	//I've put int32 Userchoice  near int32 Userchoice = 0; So that other resets can use it as well.
	Userchoice = GetWordLength();

	BCGame.Reset(Userchoice);

	bool PPlayagain = false;
	PrintIntro();

	do
	{
		PlayGame();
		PPlayagain = AskToPlayAgain();
	}
	while(PPlayagain);
	
	return 0;// exit application or stop playing the game
}

//Prints out the intro to the begining of the game
void PrintIntro() {
	//introduce the game

	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;	
	std::cout << "          )___(        ___" << std::endl;
	std::cout << "          (o o)      9(- o)9" << std::endl;
	std::cout << "  /-------\\ /          \\ /------\\" << std::endl;
	std::cout << " / | Bulls| 0           0| Cow  |\\" << std::endl;
	std::cout << "*  |------|              |------| *" << std::endl;
	std::cout << "   ^      ^              ^      ^" << std::endl;
/*	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << "letter isogram I'm thinking of? \n";*/
	std::cout << std::endl;
	return;
}
// plays a game to completion
void PlayGame()
{
	BCGame.Reset(Userchoice);
	int32 Userguess = GetWordLength();
	BCGame.ChoseHiddenWord(Userguess);
	int32 Turn_Limit = BCGame.GetMaxTries();


	//loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{

		FText Guess = GetvalidGuess();

		//submit valded guesses and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout <<"Bulls = "<< BullCowCount.Bulls <<" ";
		std::cout << "Cows = " << BullCowCount.Cows << "\n";	
	}
	PrintGameSummary();
	return;
}

int GetWordLength()
{
	int Length = 0;
	std::cout << "Please Enter a number between 3 - 7\n";
	std::cin >> Length;

	while (!(std::cin >> Length) || Length < 3 || Length > 7)
	{
		std::cout << "Please Enter a number between 3 - 7\n";
		std::cin.clear();
		std::cin.ignore();
	}
	std::cin.clear();
	std::cin.ignore();
	return Length;
}


//Gets the guess from a user. and loop conitnually until valid guess.
FText GetvalidGuess() {

	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		// get a guess from user
		std::cout << "\nTry " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << " Please Enter your guess: \n";
		
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
			std::cout << "Please turn your caps lock off or enter word in Lower case letters.\n\n";
			break;

		default:
			//assume the guess is valid
			break;
		}
		
	} while (Status != EGuessStatus::Ok);//keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'Y') || (Response[0] == 'y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon() == true)
	{
		std::cout << "Congrats you're a winner!" << std::endl;
	}
	else 
	{
		std::cout << "Sorry that unfortunate. You were unable to guess the word" << std::endl;
	}
	return;
}