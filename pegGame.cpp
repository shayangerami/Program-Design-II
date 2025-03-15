/******************************************************************************
 * Program: Triangular Peg Solitaire
 * Author: Shayan Gerami
 * Date: 2/17/2025
 *
 * Description:
 * This program simulates the Triangular Peg Solitaire game. The board consists
 * of 15 pegs arranged in a triangular pattern with 5 rows. The goal of the game
 * is to remove pegs by jumping over them, similar to checkers, until only one
 * peg remains. The player wins if they achieve this.
 *
 * Rules:
 * 1. A move consists of jumping a peg over an adjacent peg into an empty hole.
 * 2. The jumped peg is removed from the board.
 * 3. Moves can be horizontal, vertical, or diagonal.
 * 4. The game ends when no valid moves remain.
 *
 * Board Layout:
 *     A
 *    B C
 *   D E F
 *  G H I J
 * K L M N O
 *
 * Input:
 * The player enters moves in the format "FROM OVER TO" (e.g., "FCA").
 * The program validates each move and updates the board accordingly.
 *
 * Output:
 * The program displays the current state of the board after each move and
 * notifies the player if they win or if a move is invalid.
 *
 * Functions:
 * - row(char peg): Returns the row of a given peg.
 * - col(char peg): Returns the column of a given peg.
 * - displayBoard(): Displays the current state of the board.
 * - isValid(char from, char over, char to): Validates a move.
 * - updateBoard(char from, char over, char to): Updates the board after a move.
 * - getPeg(char peg): Returns a reference to the specified peg.
 *
 * Example Moves:
 * - Valid: "FCA", "DEF", "JFC", "ACF"
 * - Invalid: "KHF" (not aligned diagonally)
 *
 * Notes:
 * - The program ensures that all moves are valid and aligned with the rules.
 * - Diagonal moves must follow the triangular board's staggered structure.
 *
 ******************************************************************************/

#include <iostream>
#include <string>

using namespace std;
 
int row(char peg);
int col(char peg);
void displayBoard();
bool isValid(char from, char over, char to);
void updateBoard(char from, char over, char to);
char& getPeg(char peg);

// Declare the board variables globally
char A, B, C, D, E, F, G, H, I, J, K, L, M, N, O;
int pegCount = 14;

int main() {
    string move;
    // Initialize the board variables
    A = '.', B = 'T', C = 'T', D = 'T', E = 'T', F = 'T', G = 'T', H = 'T', I = 'T', J = 'T', K = 'T', L = 'T', M = 'T', N = 'T', O = 'T';
	displayBoard();
	
    while (true) {
		
		if (pegCount == 1) { // Check if user wins
            cout << "You win! Congratulations!" << endl;
            break;
        }
 
        cout << "Enter move (for example FCA) or Q to quit: " << endl;
		cin >> move;

        if (move == "Q") { // Check if user exits
            break;
        }

		
        if (move.length() == 3) { // Split input to three parts, from, to, over
            char from = move[0];
            char over = move[1];
            char to = move[2];
			
            if (isValid(from, over, to)) {
                updateBoard(from, over, to);
				cout << '\n';
				if (pegCount != 1) {
					displayBoard(); // Display updated board
				}
            } else {
                cout << "Move is not valid. Try again." << endl;
				cout << '\n';
				displayBoard();
            }
        } 
    }

    return 0;
}


// row returns the row of the given peg location
// Parameter peg is a character, with the letter of the peg (A-O)
// Letter should be upper case, between A and O
// Returns the row (1 through 5). 
// Row 1 is the top row (with one peg), row 5 is the bottom (with 5 pegs)
int row(char peg) {
	if (peg >= 'K') {
		return 5;
	}
	else if (peg >= 'G') {
		return 4;
	}
	else if (peg >= 'D') {
		return 3;
	}
	else if (peg >= 'B') {
		return 2;
	}
	else if (peg == 'A') {
		return 1;
	}
	else {
		cout << "Error - row: Invalid peg: " << peg << endl;
		return -1;
	}
}

// col returns the column of the given peg location
// Parameter peg is a character, with the letter of the peg (A-O)
// Letter should be upper case, between A and O
// Returns the column (1 through 5). 
// At each level, the first letter is column 1, the second letter is column 2, etc.
int col(char peg) {
	if (peg >= 'K') {
		return peg - 'K' + 1;
	}
	else if (peg >= 'G') {
		return peg - 'G' + 1;
	}
	else if (peg >= 'D') {
		return peg - 'D' + 1;
	}
	else if (peg >= 'B') {
		return peg - 'B' + 1;
	}
	else if (peg == 'A') {
		return 1;
	}
	else {
		cout << "Error - col: Invalid peg: " << peg << endl;
		return -1;
	}
}

// Checks if a move is valid
bool isValid(char from, char over, char to) {
    char& fromPeg = getPeg(from);
    char& overPeg = getPeg(over);
    char& toPeg = getPeg(to);

    int fromRow = row(from);
    int fromCol = col(from);
    int overRow = row(over);
    int overCol = col(over);
    int toRow = row(to);
    int toCol = col(to);

    // Check for invalid pegs
    if (fromPeg == '?' || overPeg == '?' || toPeg == '?') {
        return false;
    }

    // Check if the move is valid (horizontal, vertical, or diagonal)
    bool isHorizontal = (fromRow == toRow && abs(fromCol - toCol) == 2); // Horizontal move
    bool isVertical = (fromCol == toCol && abs(fromRow - toRow) == 2); // Vertical move
    bool isDiagonal = (abs(fromRow - toRow) == 2 && abs(fromCol - toCol) == 2); // Diagonal move

    if (!(isHorizontal || isVertical || isDiagonal)) {
        return false; // Invalid move, not aligned in a valid way
    }

    // Ensure the middle peg (over) is directly between from and to
    if ((fromRow + toRow) / 2 != overRow || (fromCol + toCol) / 2 != overCol) {
        return false; // The middle peg is not between the 'from' and 'to'
    }

    // Diagonal alignment check
    if (isDiagonal) {
        int rowDiff = fromRow - toRow;
        int colDiff = fromCol - toCol;

        // Check if the signs of the row and column differences match
        if ((rowDiff > 0 && colDiff < 0) || (rowDiff < 0 && colDiff > 0)) {
            return false; // Invalid diagonal alignment
        }
    }

    // Check that the move involves jumping over a peg and landing on an empty spot
    if (fromPeg != 'T' || overPeg != 'T' || toPeg == 'T') {
        return false; // The from peg must be 'T', over peg must be 'T', and to peg must be empty
    }

    return true;
}

// Gets a character and return character value: peg or hole (T or .)
char& getPeg(char peg) {
	static char invalid='?';
	switch (peg) {
        case 'A': return A;
        case 'B': return B;
        case 'C': return C;
        case 'D': return D;
        case 'E': return E;
        case 'F': return F;
        case 'G': return G;
        case 'H': return H;
        case 'I': return I;
        case 'J': return J;
        case 'K': return K;
        case 'L': return L;
        case 'M': return M;
        case 'N': return N;
        case 'O': return O;
		default:
			return invalid;
	}
}

// Displays the board
void displayBoard() {
	
    cout << string(4, ' ') << A << string(12, ' ') << "A" << endl;
    cout << string(3, ' ') << B << " " << C << string(10, ' ') << "B" << " " << "C" << endl;
    cout << string(2, ' ') << D << " " << E << " " << F << string(8, ' ') << "D" << " " << "E" << " " << "F" << endl;
    cout << string(1, ' ') << G << " " << H << " " << I << " " << J << string(6, ' ') << "G" << " " << "H" << " " << "I" << " " << "J" << endl;
    cout << string(0, ' ') << K << " " << L << " " << M << " " << N << " " << O << string(4, ' ') << "K" << " " << "L" << " " << "M" << " " << "N" << " " << "O" << endl;

}

// Updates the board based on the move
void updateBoard(char from, char over, char to){
	
	char& fromPeg = getPeg(from);
    char& overPeg = getPeg(over);
    char& toPeg = getPeg(to);
 
    fromPeg = '.';
    overPeg = '.';
    toPeg = 'T';
	
	pegCount--;
}



