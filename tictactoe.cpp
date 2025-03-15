// Lab3.cpp   
// for CS 141 lab 3	

#include <iostream>
using namespace std;


char p1,p2,p3,p4,p5,p6,p7,p8,p9;

// Running display board should print out the board and the characters denoting each square.
// (Which would display either the letter for the square, or the X or O that has moved there.)
// Running the code after displayBoard() function for the first time should be like:
//   -------
//   |a|b|c|     
//   -------
//   |d|e|f|   
//   -------
//   |g|h|i|   
//   -------
// (With no spaces before the board. The board is made of letters, vertical lines, and dashes: | and - )
void displayBoard(){
   // Enter code here
   cout << "-------" << endl;
   cout << "|" << p1 << "|" << p2 << "|" << p3 <<"|" << endl;
   cout << "-------" << endl;
   cout << "|" << p4 << "|" << p5 << "|" << p6 <<"|" << endl;
   cout << "-------" << endl;
   cout << "|" << p7 << "|" << p8 << "|" << p9 <<"|" << endl;;
   cout << "-------" << endl;

}

// This function allows a move to a specific square. For the initial move, if the square is 'b' and player is 'X'
// after this method is called, the board would look like this:
//   -------
//   |a|X|c|     
//   -------
//   |d|e|f|   
//   -------
//   |g|h|i|   
//   -------
void moveToSquare(char square, char player) {
    
    switch(square) {
        case 'a':
            p1 = player;
            break;
        case 'b':
            p2 = player;
            break;
        case 'c':
            p3 = player;
            break;
        case 'd':
            p4 = player;
            break;
        case 'e':
            p5 = player;
            break;
        case 'f':
            p6 = player;
            break;
        case 'g':
            p7 = player;
            break;
        case 'h':
            p8 = player;
            break;
        case 'i':
            p9 = player;
            break;
    }
    
}

// Outputs "Congratulations you won!" if one of the players wins
// (all three squares in one row are the same, 
// all three squares in a column are the same,
// or the three squares on a diagonal are the same)
bool checkForWin() {
    // Horizontal
    if (p1 == p2 && p2 == p3) {
        return true;
    }
    else if (p4 == p5 && p5 == p6) {
        return true;
    }
    else if (p7 == p8 && p8 == p9) {
        return true;
    }
    // Vertical
    else if (p1 == p4 && p4 == p7) {
        return true;
    }
    else if (p2 == p5 && p5 == p8) {
        return true;
    }
    else if (p3 == p6 && p6 == p9) {
        return true;
    }
    // Diagonal
    else if (p1 == p5 && p5 == p9) {
        return true;
    }
    else if (p3 == p5 && p5 == p7) {
		return true;
    }
	
	return false;

}

int main()
{
	// Initialize the board
	p1='a',p2='b',p3='c',p4='d',p5='e',p6='f',p7='g',p8='h',p9='i';
	char currentPlayer = 'X';
	char square = ' ';

    displayBoard();
	
	cout << "Player " << currentPlayer << ", enter the square you would like to play in (or q to quit): ";
	cin >> square;

    while (square != 'q') {
        moveToSquare(square, currentPlayer);

        // Switch the current player
        if (currentPlayer == 'X') {
            currentPlayer = 'O';
        } else {
            currentPlayer = 'X';
        }

        displayBoard();
        checkForWin();

        if(checkForWin()) {
			cout << "Congratulations you won!" << endl;
			break;
		}

        cout << "Player " << currentPlayer << ", enter the square you would like to play in (or q to quit): ";
        cin >> square;
    }
	
	cout << "Exiting program..." << endl;
	return 1;

}// end main()
