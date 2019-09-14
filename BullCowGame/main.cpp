/* This is the console exectuable that makes use of the BullCow class
This acts as the view in the MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game


// entry point for our application
int main() {

	std::cout << BCGame.GetCurrentTry();

	bool bPlayAgain = false;

	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain == true);

	return 0; // exit the application

}

// introduce the game
void PrintIntro() {
	constexpr int32 WORD_LENGTH = 5;
	std::cout << "Welcome to Bulls & Cows - a fun word game!\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	return;
}

void PlayGame() {

	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();
	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {

		FText Guess = GetValidGuess();

		// Submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	// TODO add game summary
}

// loop continually until user gives valid guess
FText GetValidGuess() { 
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {

		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " - Please enter your guess:\n";
	
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram (no repeating letters).\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please ensure all letters are lowercase.\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::Ok); // keep looping until we get no errors

	return Guess;
}

// ask player if they wish to play again
bool AskToPlayAgain() {
	std::cout << "Do you want to play again?\n\nEnter y/n\n\n";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}