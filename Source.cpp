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

// Lengths for each ship
const int FRIGATE = 2; 
const int TENDER = 2;
const int DESTROYER = 3;
const int CRUISER = 3;
const int CARRIER = 4;

// This struct gives all of the information for each square on the board.
struct Status{
	bool ship, // Does the square contain a ship or water?
		hit; // Has this square been hit before?
	string shipClass; // Label for each ship class.
	char display = '~'; // Used for display symbol.
};

void ShotsFired(); // Function used to loop through program until shots are depleted.
void ShipGen(); // Function used to generate the ships in-game.
void CheckSquare(); // Checks and changes values on chosen square
void GridPrint(); // Function used to print the Battle Ship grid.
void Insanity(); // Look up the definition of insanity.

void main(){

	char play; // For the start of the game
	char exitChar; // Used to exit program
	Status grid[ARRAYMAX][ARRAYMAX]; // The grid containing all of the values for the program.

	int shots; // Used for the ShotsFired function.

	// Greetings, human.
	cout << "Hello and welcome to Wacyshaw's copyright-neutral Battle Ship!\nWould you like to play?\n\nType \"y\" to begin. Type \"n\" to quit.\n";
	
	do{
		cin >> play;
		switch(tolower(play)){
		case 'n':
			cout << "Why did you even bother booting up this program? Jerk.\n";
			break;
		case 'y':
			cout << "Excellent. Let's begin.\n";
			ShipGen(FRIGATE, "frigate" grid[ARRAYMAX][ARRAYMAX]);
			cout << "Input the number of shots you want to use:";
			cin >> shots;
			ShotsFired(shots, grid[ARRAYMAX][ARRAYMAX]);
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

void ShipGen(const int SHIP, string shipClass, Status grid[ARRAYMAX][ARRAYMAX]){

	bool success = false; // Used to reset ship generation
	srand(100);

	do{ // while(success = false) so we don't get shipos outside of the borders.
		// Coordinates where the ship is initially generated 
		int x = rand() % 15;
		int y = rand() % 15;
		int direction = rand() % 4;

		grid[x][y].shipClass = shipClass; // Labelling the square's ship as a specific ship class.
		grid[x][y].ship = true; // Labelling the square as containing a ship

		// Cases for each direction
		for(int n = 0; n < SHIP; n++){
			switch(direction){
			case 0:
				x++;
				if(x > 15 || (grid[x][y].ship = true)) // Used to make sure ships don't extend past the borders
					break;
				grid[x][y].shipClass = shipClass;
				grid[x][y].ship = true;
				success = true;
				break;
			case 1:
				if(x > 15 || (grid[x][y].ship = true))
					break;
				x--;
				grid[x][y].shipClass = shipClass;
				grid[x][y].ship = true;
				success = true;
				break;
			case 2:
				if(y > 15 || (grid[x][y].ship = true))
					break;
				y++;
				grid[x][y].shipClass = shipClass;
				grid[x][y].ship = true;
				success = true;
				break;
			case 3:
				if(y > 15 || (grid[x][y].ship = true))
					break;
				y--;
				grid[x][y].shipClass = shipClass;
				grid[x][y].ship = true;
				success = true;
				break;
			default:
				cout << "Error: var \"direction\" invalid.\n\n";
			}
		}
	} while(success = false);
}

void ShotsFired(int s, Status grid[ARRAYMAX][ARRAYMAX){

	char rowInput; // Letter input for row
	int columnInput; // Column input
	int row; // Converts rowInput to correct array position
	int column; // Converts columnInput to correct array position

	for(int n = 0; n < s; n++){
		cout << "Where do you want to fire? Enter a letter between \"A\" and \"O\" followed by a number between 1 and 15 (e.g. A1): \n";
		cin >> rowInput >> columnInput;
		row = int(tolower(rowInput)) - 97; // Converts the letter to an integer
		column = columnInput - 1;
		for(int counter = 0; grid[row][column].hit == true; counter++){
			Insanity(counter);
			cout << "Where do you want to fire? Enter a letter between \"A\" and \"O\" followed by a number between 1 and 15 (e.g. A1): \n";
			cin >> rowInput >> columnInput;
			row = int(tolower(rowInput)) - 97;
			column = columnInput - 1;
		}
		CheckSquare(row, column, grid);
		GridPrint(grid[ARRAYMAX][ARRAYMAX]);
		if()

	}
}

void CheckSquare(int& row, int& column, Status grid[ARRAYMAX][ARRAYMAX]){
	switch(grid[row][column].ship){
	case true:
		grid[row][column].display = 'x';
		grid[row][column].hit = true;
		break;
	case false:
		grid[row][column].display = 'o';
		grid[row][column].hit = true;
		break;
	default:
		cout << "Error: Switch function did not result in a boolean.\n\n";
	}
}

void GridPrint(Status grid[ARRAYMAX][ARRAYMAX]){
	for(int m = 0; m < ARRAYMAX; m++){
		for (int n = 0; n < ARRAYMAX; n++){
			cout << "   " << grid[m][n].display;
			if((m % 15) == 0){
				cout << "\n";
			}
		}
	}
}

void Insanity(int counter){
	switch(counter){
	case 1:
		cout << "You already hit that square! Try again./n/n";
		break;
	case 2:
		cout << "Did you not hear me? You already hit that square. Try again.\n\n";
		break;
	case 3:
		cout << "This is the third time I've had to tell you. Do you really want to sit here shooting at the same square all day?\n\n";
		break;
	case 4:
		cout << "I am a computer program. I can do this all day. Is this really all you want to do with your time?\n\n";
		break;
	case 5: 
		cout << "Do you know what the definition of \"Insanity\" is? It's trying the same thing over and over expecting a different result.\n\n";
		break;
	case 6:
		cout << "Clearly your insane. For the sake of your poor computer, I will terminate this program after four more failed attempts.\n\n";
		break;
	case 7:
		cout << "You have three attempts remaining.\n\n";
		break;
	case 8:
		cout << "You have two attempts remaining.\n\n";
		break;
	case 9:
		cout << "Are you sure this is what you want? I promise I'll terminate the program. Don't test me.\n\n";
		break;
	case 10:
		exit(0);
		break;
	default:
		cout << "Error with \"Insanity\" function.\n\n";
	}
}