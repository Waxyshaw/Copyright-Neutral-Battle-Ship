// File: Battle_Ship.cpp
// Author: Waxyshaw
//
// We're making a working version of Battleship! It's only one player though, and there's no enemy AI

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>

using namespace std;

const int ARRAYMAX = 15; // Maximum spaces for each dimension in the array.

// This struct gives all of the information for each square on the board.
struct Status{
	bool ship, // Does the square contain a ship or water?
		hit; // Has this square been hit before?
	string shipClass; // Label for each ship class.
	char display = '~'; // Used for display symbol.
};

void ShotsFired(int s); // Function used to loop through program until shots are depleted.
void ShipGen(); // Function used to generate the ships in-game.
void CheckSquare(); // Checks and changes values on chosen square
void GridPrint(Status array[]); // Function used to print the Battle Ship grid.

void main(){

	char play; // For the start of the game
	char exitChar; // Used to exit program

	int shots; // Used for the ShotsFired function.

	// Greetings, human.
	cout << "Hello and welcome to Wacyshaw's copyright neutral Battle Ship!\nWould you like to play?\n\nType \"y\" to begin. Type \"n\" to quit.\n";
	
	do{
		cin >> play;
		switch(tolower(play)){
		case 'n':
			cout << "Why did you even bother booting up this program? Jerk.\n";
			break;
		case 'y':
			cout << "Excellent. Let's begin.\n";
			cout << "Input the number of shots you want to use:";
			cin >> shots;
			ShotsFired(shots);
			break;
		default:
			cout << "Invalid input. Try again.\n";
			cout << "Type \"y\" to begin. Type \"n\" to quit.\n";
		}
		break;
	} while(play != 'n');

	//Wait for key response before exiting.
	cout << "\n\nPress any key and <enter> to exit \n";
	cin >> exitChar;
}

void ShotsFired(int s){

	Status grid;
	char first; // Row
	int second; // Column
	int convert; // Converts char to int

	for(int n = 0; n < s; n++){
		cout << "Where do you want to fire? Enter a letter between \"A\" and \"O\" followed by a number between 1 and 15 (e.g. A1): \n";
		cin >> first >> second;
		convert = int(first) - 97;
		GridPrint(grid);

	}
}

void ShipGen(){

}

void CheckSquare(int a, int b){
	Status array[a][b];
	switch(array[].ship){
	case true:
		array[a][b].display = "x";
		array[a][b].hit = true;
	}
}

void GridPrint(Status array[]){
	for(int m = 0; m < (ARRAYMAX * ARRAYMAX); m++){
		cout << "   " << array[m].display;
		if((m % 15) == 0){
			cout << "\n";
		}
	}
	
}