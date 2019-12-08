// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();
	SetUpGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	ClearScreen();
	PrintLine(Input);
	//If game is over, clear the screen and setup the game again.
	if (bGameOver == true) {
		ClearScreen();
		SetUpGame();
		return;
	}
	else {
		CheckGuess(Input);
	}
}

void UBullCowCartridge::SetUpGame() {
	//Initialize variables
	HiddenWord = "Cake";
	Lives = 4;
	bGameOver = false;

	//Welcome Player
	PrintLine(TEXT("Welcome to Bulls and Cows!\n"));
	PrintLine(TEXT("   This is a guessing game, and your goal\n   is to guess the isogram.\n"));

	//Prompt player for guess
	PrintLine(TEXT("   The hidden word is %i characters long."), HiddenWord.Len());
	PrintLine(TEXT("   Enter your guess: "));
}

void UBullCowCartridge::EndGame() {
	bGameOver = true;
	PrintLine(TEXT("   You are out of lives! GAME OVER."));
	PrintLine(TEXT("   The hidden word was %s."), *HiddenWord);
	PrintLine(TEXT("   Press enter to continue."));
}

bool UBullCowCartridge::ProcessGuess(const FString& Guess) {
	//Check if isogram
		//If no, guess again.
	for (int32 i = 0; i < Guess.Len(); i++) {
		for (int32 j = i + 1; j < Guess.Len(); j++) {
			if (Guess[i] == Guess[j]) {
				PrintLine(TEXT("   That isn't an isogram! Try again."));
				return false;
			}
		}
	}

	//Check if right number of characters	
		//If no, guess again.
	if (Guess.Len() != HiddenWord.Len()) {
		PrintLine(TEXT("   The hidden word is only %i\n   characters! Try again."), HiddenWord.Len());
		return false;
	}
	return true;
}

void UBullCowCartridge::CheckGuess(const FString& Guess) {
	//Test if guess is valid.
	if (!ProcessGuess(Guess))
		return;

	//Checking player guess.
		//If player guess is correct, next level and increase difficulty.
	if (Guess == HiddenWord) {
		PrintLine(TEXT("   CORRECT! Moving to next level.\n"));
		//Increase difficulty.
	}
	//If player guess is incorrect...
	else {
		PrintLine(TEXT("   INCORRECT."));
		Lives--;
		//Check if lives are out.
			//If yes, game over. 
			//Show player HiddenWord and prompt player to play again.
		if (Lives == 0)
			EndGame();
		//If no, guess again.
			//Show lives left
			//Show Bulls and Cows
		else {
			PrintLine(TEXT("   You have %i lives left."), Lives);
			CheckBullsAndCows(Guess);
		}
	}


}

void UBullCowCartridge::CheckBullsAndCows(const FString& Guess) {
	int32 Bulls = 0;
	int32 Cows = 0;

	for (int32 i = 0; i < Guess.Len(); i++) {
		if (Guess[i] == HiddenWord[i])
			++Bulls;
		else {
			for (int32 j = 0; j < HiddenWord.Len(); j++) {
				if (Guess[i] == HiddenWord[j])
					++Cows;
			}
		}
	}
	PrintLine(TEXT("   There were: %i Bulls"), Bulls);
	PrintLine(TEXT("               %i Cows"), Cows);
	return;
}