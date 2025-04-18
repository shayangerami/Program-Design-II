/*
 * Program: Connect Four
 * Description: A two-player game where players take turns dropping their pieces
 *             into a 6x7 grid. The first player to connect four of their pieces
 *             horizontally, vertically, or diagonally wins the game. If no winner is found and
 *             board is full game is tied. A player can choose to end the game by typing -1.
 * Author: Shayan Gerami
 * Date: 4/10/2025
 */

#include <iostream>
#include <string>

using namespace std;

// Function prototypes
void displayBoard(char board[6][7]); // Displays board
int makeMove(char board[6][7], int col, char player); // Makes a move by changing the board
bool checkWin(char board[6][7], int row, int col, char player); // Checks if there is a winner
bool checkTie(char board[6][7]); // Checks is board is full = tie

int main() {
    char board[6][7];

    // Initialize the board with '-'
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            board[i][j] = '-';
        }
    }

    char currPlayer = 'R'; // Game starts with red
    string player = "Red";
    int chosenCol;
    
    displayBoard(board); // Display original board

    while (true) { // Main game loop
    
        // Prompt user to choose column
        cout << "It is " << player << "'s turn." << endl;
        cout << "In which column would you like to move (-1 to exit)?" << endl;
        cin >> chosenCol;

        // Exit condition
        if (chosenCol == -1) {
            break;
        }
        
        // Validate input range
        if (chosenCol < 1 || chosenCol > 7) {
            cout << "Invalid move, try again." << endl;
            continue;
        }

        // Check if move is valid
        int rowPlayed = makeMove(board, chosenCol - 1, currPlayer);
        if (rowPlayed != -1) {
            // Check for winner
            if (checkWin(board, rowPlayed, chosenCol - 1, currPlayer)) {
                displayBoard(board);
                cout << "\n" << player << " Wins!" << endl;
                break; // End the game loop
            } else {
                if (!checkTie(board)) { // Check for tie
                    currPlayer = (currPlayer == 'R') ? 'Y' : 'R'; // Switch player turn
                    player = (player == "Red") ? "Yellow" : "Red";
                    displayBoard(board);
                } else {
                    displayBoard(board);
                    cout << "\nGame over. Tie game." << endl;
                    break; // End the game loop
                }
                
            }
        } else{
            cout << "Invalid move, try again." << endl;
        }

    }
    return 0;
}

/**
 * Displays the current state of the Connect Four board
 * @param board - The 6x7 game board array
 */
void displayBoard(char board[6][7]){
    int rows = 6;
    int cols = 7;

    // Print board
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++){
            cout << board[r][c] << " ";
        }
        cout << endl;
    }

    // Print the bottom border
    for (int i = 0; i < 13; ++i) {
        cout << "=";
    }
    cout << endl;

    // Print column numbers
    for (int col = 1; col <= cols; ++col) {
        cout << col << " ";
    }
    cout << endl;
}

/**
 * Attempts to make a move in the specified column for the given player
 * @param board - The 6x7 game board array
 * @param col - The column where the move is attempted (0-6)
 * @param player - The player making the move ('R' or 'Y')
 * @return The row where the piece was placed, or -1 if the move was invalid
 */
int makeMove(char board[6][7], int col, char player){
    int rows= 6;

    // Start from the bottom of board to find empty spots
    for (int r = rows - 1; r >= 0 ; r--){
        // Check if empty
        if (board[r][col] == '-') {
            board[r][col] = player;
            return r; // Move successful, return row (used for win check)
        }
    }
    return -1; // Column is full
}

/**
 * Checks if the current player has won the game
 * @param board - The 6x7 game board array
 * @param row - The row of the last move
 * @param col - The column of the last move
 * @param player - The player to check for a win ('R' or 'Y')
 * @return true if the player has won, false otherwise
 */
bool checkWin(char board[6][7], int row, int col, char player) {

    // -------- Horizontal Check --------
    // Check to the left of the current position
    // While within bounds and the piece matches the player, increment count
    int count = 1; // Initialize count to 1 (for the current piece)

    int currCol = col - 1;
    while (currCol >= 0 && board[row][currCol] == player) {
        currCol--;
        count++;
    }

    // Check to the right of the current position
    // While within bounds and the piece matches the player, increment count
    currCol = col + 1;
    while (currCol <= 6 && board[row][currCol] == player) {
        currCol++;
        count++;
    }

    if (count >= 4){
        return true; // There is a winner
    }

    // Reset count to 1 for next check
    count = 1;

    // -------- Vertical Check --------
    // Check downward (since we always place from top to bottom, no need to check upward)
    // While within bounds and the piece matches the player, increment count
    int currRow = row + 1;
    while (currRow <= 5 && board[currRow][col] == player) {
        currRow++;
        count++;
    }

    if (count >= 4){
        return true; // There is a winner
    }

    // Reset count to 1 for next check
    count = 1;

    // -------- Diagonal Check (Top-Left to Bottom-Right) --------
    // Check towards top-left
    // While within bounds and the piece matches the player, increment count
    currRow = row - 1;
    currCol = col - 1;
    while (currRow >= 0 && currCol >= 0 && board[currRow][currCol] == player) {
        count++;
        currRow--;
        currCol--;
    }

    // Check towards bottom-right
    // While within bounds and the piece matches the player, increment count
    currRow = row + 1;
    currCol = col + 1;
    while (currRow <= 5 && currCol <= 6 && board[currRow][currCol] == player) {
        count++;
        currRow++;
        currCol++;
    }

    if (count >= 4){
        return true; // There is a winner
    }

    // Reset count to 1 for next check
    count = 1;

    // -------- Diagonal Check (Bottom-Left to Top-Right) --------
    // Check towards bottom-left
    // While within bounds and the piece matches the player, increment count
    currRow = row + 1;
    currCol = col - 1;
    while (currRow < 6 && currCol >= 0 && board[currRow][currCol] == player) {
        count++;
        currRow++;
        currCol--;
    }

    // Check towards top-right
    // While within bounds and the piece matches the player, increment count
    currRow = row - 1;
    currCol = col + 1;
    while (currRow >= 0 && currCol < 7 && board[currRow][currCol] == player) {
        count++;
        currRow--;
        currCol++;
    }

    if (count >= 4){
        return true; // There is a winner
    }

    return false; // No win
}

/**
 * Checks if the game has ended in a tie
 * @param board - The 6x7 game board array
 * @return true if the board is full (tie game), false otherwise
 */
bool checkTie(char board[6][7]){
    int count = 0;
    for (int col = 0; col <= 6; col++){
        if (board[0][col] == '-') {
            return false; // Found an empty spot, board is not full
        }
    }
    return true; // No empty spot found, board is full
}