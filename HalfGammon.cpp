/******************************************************************************
 * Program: Backgammon Game Simulator
 *          HalfGammon
 * Description: A text-based implementation of the classic board game Backgammon.
 *              Two players (X and O) take turns rolling dice and moving their
 *              checkers around the board. The goal is to be the first to bear
 *              off all your checkers. The game includes rules for valid moves,
 *              hitting opponent's checkers, and bearing off.
 * Author: Shayan Gerami
 * Date: 3/5/2025
 ******************************************************************************/ 

#include <iostream>
#include <fstream>
#include <iomanip>
#include "mersenne-twister.h"

using namespace std;

// Function prototypes

// Displays the board
void displayBoard(int (&Xarray)[18], int (&Oarray)[18]);

// Checks if move is valid
bool validMoveX(int start, int dest, int (&Xarray)[18], int (&Oarray)[18]);
bool validMoveO(int start, int dest, int (&Xarray)[18], int (&Oarray)[18]);

// Moves the checker 
void moveX(int start, int dest, int (&Xarray)[18], int (&Oarray)[18]);
void moveO(int start, int dest, int (&Xarray)[18], int (&Oarray)[18]);

// Counts the number of checkers on the board
int countCheckers(int (&array)[18]);


int main() {
    // Initialize board
    int Xarray[18] = {0, 5, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int Oarray[18] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 5, 0};

    bool gameOver = false;
    bool Xturn = true; // X starts first
    int roll;
    int start;
    int dest;
    
    // Get the number to use as a random seed from the user
    int randSeed;
    cout << "Enter seed: ";
    cin >> randSeed;
    seed(randSeed);
    
    displayBoard(Xarray, Oarray);
    
    while (!gameOver) {
        if (Xturn) {
            cout << "\nIt's X's turn." << endl;
        }
        else {
            cout << "\nIt's O's turn." << endl;
        }
        
        roll = chooseRandomNumber(1, 6);
        cout << "Roll is " << roll << endl;
        
        // Determine if a bumped checker must be moved
        bool mustMove = false;
        if (Xturn && Xarray[0] != 0) {
            mustMove = true;
        }
        else if (!Xturn && Oarray[17] != 0) {
            mustMove = true;
        }
        if (mustMove) {
            cout << "Bumped checker must move." << endl;
        }
        
        // Check if any move is possible given the roll
        bool movePossible = false;
        if (mustMove) {
            if (Xturn) {
                movePossible = validMoveX(0, roll, Xarray, Oarray);
            }
            else {
                movePossible = validMoveO(17, 17 - roll, Xarray, Oarray);
            }
        }
        else {
            if (Xturn) {
                // Check positions 1 to 16 for X
                for (int pos = 1; pos <= 16; pos++) {
                    if (Xarray[pos] > 0 && validMoveX(pos, pos + roll, Xarray, Oarray)) {
                        movePossible = true;
                        break;
                    }
                }
            }
            else {
                // Check positions 1 to 16 for O
                for (int pos = 1; pos <= 16; pos++) {
                    if (Oarray[pos] > 0 && validMoveO(pos, pos - roll, Xarray, Oarray)) {
                        movePossible = true;
                        break;
                    }
                }
            }
        }
        
        if (!movePossible) {
            cout << "No move possible." << endl;
			// Display board
			displayBoard(Xarray, Oarray);
            // Change turn and continue the game loop
            Xturn = !Xturn;
            continue;
        }
        
        // If a move is possible, enter the move selection loop
        while (true) {
            if (mustMove) {
                if (Xturn) {
                    dest = roll;  // Forced move for X from position 0 to roll
                    if (validMoveX(0, dest, Xarray, Oarray)) {
                        moveX(0, dest, Xarray, Oarray);
                        int countX = countCheckers(Xarray);
                        int countO = countCheckers(Oarray);
                        if (countX == 0) {
                            cout << "Player X Wins!" << endl;
                            gameOver = true;
                            break;
                        }
                        else if (countO == 0) {
                            cout << "Player O Wins!" << endl;
                            gameOver = true;
                            break;
                        }
                        displayBoard(Xarray, Oarray);
                        mustMove = false;
                        break; // Exit move selection loop
                    }
                } 
                else {
                    dest = 17 - roll;  // Forced move for O from position 17 to (17 - roll)
                    if (validMoveO(17, dest, Xarray, Oarray)) {
                        moveO(17, dest, Xarray, Oarray);
                        int countX = countCheckers(Xarray);
                        int countO = countCheckers(Oarray);
                        if (countX == 0) {
                            cout << "Player X Wins!" << endl;
                            gameOver = true;
                            break;
                        }
                        else if (countO == 0) {
                            cout << "Player O Wins!" << endl;
                            gameOver = true;
                            break;
                        }
                        displayBoard(Xarray, Oarray);
                        mustMove = false;
                        break; // Exit move selection loop
                    }
                }
            }
            else {
                while (true){
                    cout << "What position would you like to move (-1 to quit)? ";
                    cin >> start;
                    // Check for out of range input
                    if (start == -1 || (start >= 1 && start <= 16)) {
                        break; // Exit loop if valid input
                    }
                    cout << "Invalid move. Try again." << endl;
                }   
                if (start == -1) {
                        return 0;
                }

                // Calculate destination based on start and roll
                if (Xturn) {
                    dest = start + roll;
                } 
                else {
                    dest = start - roll;
                }
                
                // Check valid move and then execute it
                if (Xturn && validMoveX(start, dest, Xarray, Oarray)) {
                    moveX(start, dest, Xarray, Oarray);
                    int countX = countCheckers(Xarray);
                    int countO = countCheckers(Oarray);
                    if (countX == 0) {
                        cout << "Player X Wins!" << endl;
                        gameOver = true;
                        break;
                    }
                    else if (countO == 0) {
                        cout << "Player O Wins!" << endl;
                        gameOver = true;
                        break;
                    }
                    displayBoard(Xarray, Oarray);
                    break; // Exit move selection loop
                } 
                else if (!Xturn && validMoveO(start, dest, Xarray, Oarray)) {
                    moveO(start, dest, Xarray, Oarray);
                    int countX = countCheckers(Xarray);
                    int countO = countCheckers(Oarray);
                    if (countX == 0) {
                        cout << "Player X Wins!" << endl;
                        gameOver = true;
                        break;
                    }
                    else if (countO == 0) {
                        cout << "Player O Wins!" << endl;
                        gameOver = true;
                        break;
                    }
                    displayBoard(Xarray, Oarray);
                    break; // Exit move selection loop
                }
                else {
                    cout << "Invalid move. Try again." << endl;
                }
            }
        }
        // Change turn if game is not over
        if (!gameOver) {
            Xturn = !Xturn;
        }
    }
    return 0;
}

bool validMoveX(int start, int dest, int (&Xarray)[18], int (&Oarray)[18]){
    // Returns true if move is valid

    // Check if starting position has a checker
    if (Xarray[start] == 0){
        return false; // Starting position has no X
    }

    // Check if move is within board range or is a bear off
    if (dest > 16) {
        // Bear off condition
        return true;
    }

    // Check if destination is within board range
    if (dest >= 1 && dest <= 16) {
        // A valid move can be made if destination is empty or has 1 O (hit)
        if (Oarray[dest] == 0 || Oarray[dest] == 1){
            return true;
        }
        else if (Oarray[dest] > 1) {
            return false; // Destination full
        }
        else if (Xarray[dest] < 5){ // Stacking condition (less than 5 checkers)
            return true; // Stack
        }
    }
    return false; // Invalid move
}

bool validMoveO(int start, int dest, int (&Xarray)[18], int (&Oarray)[18]){
    // Returns true if move is valid

    // Check if starting position has a checker
    if (Oarray[start] == 0){
        return false; // Starting position has no O
    }

    // Check if move is within board range or is a bear off
    if (dest < 1) {
        // Bear off condition
        return true;
    }

    // Check if destination is within board range
    if (dest >= 1 && dest <= 16) {
        // A valid move can be made if destination is empty or has 1 X (hit)
        if (Xarray[dest] == 0 || Xarray[dest] == 1){
            return true;
        }
        else if (Xarray[dest] > 1) {
            return false; // Destination full
        }
        else if (Oarray[dest] < 5){ // Stacking condition (less than 5 checkers)
            return true; // Stack
        }
    }
    return false; // Invalid move
}
void moveX(int start, int dest, int (&Xarray)[18], int (&Oarray)[18]){
    // Bear off (remove from the board)
    if (dest > 16){
        Xarray[start]--;
    }
	else{
        // Check if move is valid
        if (validMoveX(start, dest, Xarray, Oarray)){
            if (Oarray[dest] == 1){ 
                // Hit
                Oarray[dest]--;
				Xarray[dest]++;
				Xarray[start]--;
                // Move checker out of the board (index 17)
                Oarray[17]++;    
            }
			else{
				// Regular move
				Xarray[start]--;
				Xarray[dest]++;
			}
        }
    }
}

void moveO(int start, int dest, int (&Xarray)[18], int (&Oarray)[18]){
    // Bear off (remove from the board)
    if (dest < 1){
        Oarray[start]--;
    }
    else{
        // Check if move is valid
        if (validMoveO(start, dest, Xarray, Oarray)){
            if (Xarray[dest] == 1){ 
                // Hit
                Xarray[dest]--;
				Oarray[dest]++;
				Oarray[start]--;
                // Move checker out of the board (index 0)
                Xarray[0]++;    
            }
			else{
				// Regular move
				Oarray[start]--;
				Oarray[dest]++;
			}
        }
    }
}

int countCheckers(int (&array)[18]){
    int count = 0;
    for (int i = 0; i <= 17; i++){
        count += array[i];
    }
    return count;
}

void displayBoard(int (&Xarray)[18], int (&Oarray)[18]) {
    // Print the board row by row, starting from the top (row 7)
    for (int row = 7; row > 0; row--) {
        // Print position 0 (X's side)
        if (Xarray[0] == 1 && row == 1) {
            cout << 'X'; // Display bumped checker in the last row for position 0
        } else {
            cout << ' '; // Empty space for position 0
        }

        // Print columns (1 to 16)
        for (int col = 1; col <= 16; col++) {
            char c = ' ';
            
            if (Xarray[col] >= row) {
                c = 'X'; // Display X's checker
            } else if (Oarray[col] >= row) {
                c = 'O'; // Display O's checker
            }
            cout << setw(3) << c; // Use setw(3) for checkers to ensure consistent spacing
        }

        // Print position 17 (O's side)
        if (Oarray[17] == 1 && row == 1) {
            cout << setw(2) << 'O'; // Display bumped checker in the last row for position 17
        } else {
            cout << setw(2) << ' '; // Empty space for position 17
        }
        cout << endl;
    }

    // Print numbers below the board (1 to 16), without 0 and 17
    cout << ' '; // Align the numbers with the first column (position 0)
    for (int num = 1; num <= 16; num++) {
        cout << setw(3) << num; // Use setw(3) for numbers to align with checkers
    }
    cout << endl;
}
