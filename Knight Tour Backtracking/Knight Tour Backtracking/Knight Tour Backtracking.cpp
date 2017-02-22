// Knight Tour Backtracking.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>

#include <vector>

using namespace std;

// Moves that the knight can make 
int knightMoves[8][2] = {
	{ 1, -2 }, { 1, 2 }, { -1, 2 }, { -1, -2 },
	{ 2, -1 }, { 2, 1 }, { -2, 1 }, { -2, -1 },
};

//Board size
int BOARDSIZE;

int validBoardSize = false;

// Current position of the horse 
int currentPosX = -1;
int currentPosY = -1;


// Displays the solution (knight tour)
void ShowSolution(int** solution)
{
	cout << "Solution found!" << endl;
	for (int row = 0; row < BOARDSIZE; row++)
	{
		for (int col = 0; col < BOARDSIZE; col++)
		{
			cout << solution[col][row] << "\t";
		}
		cout << endl;
	}

}

//Checks if next position is within in the playboard and is not visited
bool isInBoard(int nextPosX, int nextPosY, int** solution){

	if ((nextPosX >= 0 && nextPosX < BOARDSIZE) && (nextPosY >= 0 && nextPosY < BOARDSIZE)){
		if (solution[nextPosX][nextPosY] == -1){
			return true;
		}
	}
	return false;
}


//Recursive function to move the knight across the board
bool isSolutionFound(int count, int knightMoves[][2], int** solution, int currentPosX, int currentPosY)
{
	// Check if knight tour is completed
	if (count == BOARDSIZE * BOARDSIZE - 1){
		return true;
	}
	// Loops through all possible moves 
	for (int i = 0; i < 8; i++){
		int nextPosX = currentPosX + knightMoves[i][0];
		int nextPosY = currentPosY + knightMoves[i][1];

		//If horse can move, increase the count and place it inside the solution array
		if (isInBoard(nextPosX, nextPosY, solution))
		{
			solution[nextPosX][nextPosY] = count + 1;

			if (isSolutionFound(count + 1, knightMoves, solution, nextPosX, nextPosY) == true){
				return true;
			}

			else{
				// If horse can't find move (current knight move used) , set count on current/chosen position to -1
				// So this position return false, and goes back to the forloop ( increasing i by 1, keeping current pos ) 
				solution[nextPosX][nextPosY] = -1;

			}
		}

	}
	return false;
}

void StartKnightTour(int BOARDSIZE){

	//Move count
	int count = 0;

	//Create board/solution and set the values to -1
	int** solution = new int*[BOARDSIZE];

	for (int i = 0; i < BOARDSIZE; i++){
		solution[i] = new int[BOARDSIZE];
	}

	//Init board to -1
	for (int row = 0; row < BOARDSIZE; row++)
	{
		for (int col = 0; col < BOARDSIZE; col++)
		{
			solution[col][row] = -1;
		}
	}


	// Sets the count on the first/starting position to 0
	solution[currentPosX][currentPosY] = 0;

	if (isSolutionFound(count, knightMoves, solution, currentPosX, currentPosY)){
		ShowSolution(solution);
	}
	else {
		cout << "No knight tour found :( " << endl;
	}

}

// Checks whether the input is an integer
void OnlyAcceptNumberInputs(int& target)
{
	cin >> target;

	if (cin.fail())
	{
		cout << "Input is not an integer." << endl;
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
	// Checks whether the board size is equal or higher than 5

	while (BOARDSIZE < 5)
	{
		cout << "Please enter a board size with a value of 5 or higher: ";

		OnlyAcceptNumberInputs(BOARDSIZE);
	}

	// Checks for the starting positiion if the entered value is zero and within the board
	while (currentPosX < 0 || currentPosX >(BOARDSIZE - 1))
	{

		cout << "Please enter in which column the knight should start: ";
		OnlyAcceptNumberInputs(currentPosX);
	}

	while (currentPosY < 0 || currentPosY>BOARDSIZE - 1)
	{

		cout << "Please enter in which row the knight should start: ";
		OnlyAcceptNumberInputs(currentPosY);
	}

	StartKnightTour(BOARDSIZE);
	return 0;
}

