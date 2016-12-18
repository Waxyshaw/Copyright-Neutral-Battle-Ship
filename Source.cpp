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

void ShipGen(const int, string, Status grid[ARRAYMAX][ARRAYMAX]); // Function used to generate the ships in-game.
void ShotsFired(int, Status grid[ARRAYMAX][ARRAYMAX]); // Function used to loop through program until shots are depleted.
void CheckSquare(int, int, Status grid[ARRAYMAX][ARRAYMAX]); // Checks and changes values on chosen square
void GridPrint(Status grid[ARRAYMAX][ARRAYMAX]); // Function used to print the Battle Ship grid.
void LetterPrint(int&, int&); // Consolidates the column of letters delineating each row.
void Insanity(int); // Look up the definition of insanity.

void main(){

	char play; // For the start of the game
	char exitChar; // Used to exit program
	Status grid[ARRAYMAX][ARRAYMAX]; // The grid containing all of the values for the program.

	int shots; // Used for the ShotsFired function.

	// Greetings, human.
	cout << "Hello and welcome to Wacyshaw's copyright-neutral Battle Ship!";
	cout << "\nWould you like to play?\n\nType \"y\" to begin. Type \"n\" to quit.\n";
	
	do{
		cin >> play;
		switch(tolower(play)){
		case 'n':
			cout << "Why did you even bother booting up this program? Jerk.\n";
			break;
		case 'y':
			cout << "Excellent. Let's begin.\n";

			// Generate ships.
			ShipGen(FRIGATE, "Frigate", grid);
			ShipGen(TENDER, "Tender", grid);
			ShipGen(DESTROYER, "Destroyer", grid);
			ShipGen(CRUISER, "Cruiser", grid);
			ShipGen(CARRIER, "Carrier", grid);

			// Input the number of shots you want to use
			cout << "Input the number of shots you want to use:";
			cin >> shots;
			ShotsFired(shots, grid);
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

	// Coordinates where the ship is initially generated 
	srand(100);
	int x = rand() % 15;
	int y = rand() % 15;
	int direction = rand() % 4;

	do{ // while(!success) so we don't get ships outside of the borders.

		grid[x][y].shipClass = shipClass; // Labelling the square's ship as a specific ship class.
		grid[x][y].ship = true; // Labelling the square as containing a ship

		// Cases for each direction
		for(int n = 0; n < SHIP; n++){
			switch(direction){
			case 0:
				x++;
				if((x < 15) && (x >= 0) && (grid[x][y].ship == false)) break; // Used to make sure ships don't extend past the borders
					grid[x][y].shipClass = shipClass;
					grid[x][y].ship = true;
					success = true;
				break;
			case 1:
				x--;
				if((x < 15) && (x >= 0) && (grid[x][y].ship == false)) break;
					grid[x][y].shipClass = shipClass;
					grid[x][y].ship = true;
					success = true;
				break;
			case 2:
				if((y < 15) && (y >= 0) && (grid[x][y].ship == false)) break;
					y++;
					grid[x][y].shipClass = shipClass;
					grid[x][y].ship = true;
					success = true;
				break;
			case 3:
				if((y < 15) && (y >= 0) && (grid[x][y].ship == false)) break;
					y--;
					grid[x][y].shipClass = shipClass;
					grid[x][y].ship = true;
					success = true;
				break;
			default:
				cout << "Error: var \"direction\" invalid.\n\n";
			}
		}
	} while(!success);
}

void ShotsFired(int s, Status grid[ARRAYMAX][ARRAYMAX]){

	char rowInput; // Letter input for row
	int columnInput; // Column input
	int row; // Converts rowInput to correct array position
	int column; // Converts columnInput to correct array position

	for(int n = 0; n < s; n++){
		cout << "Where do you want to fire?" 
			<< "Enter a letter between \"A\" and \"O\" followed by a number between 1 and 15 (e.g. A1): \n";
		cin >> rowInput >> columnInput;
		row = int(tolower(rowInput)) - 97; // Converts the letter to an integer
		column = columnInput - 1;

		// For failing to choose a new square
		for(int counter = 0; grid[row][column].hit == true; counter++){
			Insanity(counter);
			cout << "Where do you want to fire?" 
				<< "Enter a letter between \"A\" and \"O\" followed by a number between 1 and 15 (e.g. A1): \n";
			cin >> rowInput >> columnInput;
			row = int(tolower(rowInput)) - 97;
			column = columnInput - 1;
		}

		CheckSquare(row, column, grid);
		GridPrint(grid);
	}
}

void CheckSquare(int row, int column, Status grid[ARRAYMAX][ARRAYMAX]){
	switch(grid[row][column].ship){
	case true: // Hit
		grid[row][column].display = 'x';
		grid[row][column].hit = true;
		break;
	case false: // Miss
		grid[row][column].display = 'o';
		grid[row][column].hit = true;
		break;
	}
}

void GridPrint(Status grid[ARRAYMAX][ARRAYMAX]){

	cout << "     1    2    3    4    5    6    7    8    9    10    11    12    13    14    15" << endl;
	cout << "A";

	for(int m = 0; m <= ARRAYMAX; m++){
		for(int n = 0; n <= ARRAYMAX; n++){
			cout << "    ";
			if((n >= 10) && (n <= ARRAYMAX)) cout << " "; // Formatting for double-digit numbers
			cout << grid[m][n].display;
			if(n == ARRAYMAX){
				cout << "\n";
				LetterPrint(m, n);
			}
		}
	}
}

void LetterPrint(int& m, int& n){
	switch(m){
	case 0:
		cout << "B";
		n = 0;
		m++;
		break;
	case 1:
		cout << "C";
		n = 0;
		m++;
		break;
	case 2:
		cout << "D";
		n = 0;
		m++;
		break;
	case 3:
		cout << "E";
		n = 0;
		m++;
		break;
	case 4:
		cout << "F";
		n = 0;
		m++;
		break;
	case 5:
		cout << "G";
		n = 0;
		m++;
		break;
	case 6:
		cout << "H";
		n = 0;
		m++;
		break;
	case 7:
		cout << "I";
		n = 0;
		m++;
		break;
	case 8:
		cout << "J";
		n = 0;
		m++;
		break;
	case 9:
		cout << "K";
		n = 0;
		m++;
		break;
	case 10:
		cout << "L";
		n = 0;
		m++;
		break;
	case 11:
		cout << "M";
		n = 0;
		m++;
		break;
	case 12:
		cout << "N";
		n = 0;
		m++;
		break;
	case 13:
		cout << "O";
		n = 0;
		m++;
		break;
	case 14:
		break;
	default:
		cout << "Error with \"LetterPrint\" function.";
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