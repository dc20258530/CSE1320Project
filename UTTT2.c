#include <stdio.h>
#include <stdlib.h>

#define SIZE 9 // Size for the 3x3 grid of 3x3 grids
#define SUBGRID_SIZE 3 // Size for each subgrid

// Function to print the tic tac toe board
void printBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (i % SUBGRID_SIZE == 0 && i != 0) {
            printf("-----------\n");
        }
        for (int j = 0; j < SIZE; j++) {
            if (j % SUBGRID_SIZE == 0 && j != 0) {
                printf("|");
            }
            printf(" %c ", board[i][j]);
        }
        printf("\n");
    }
}

// Function to initialize the tic tac toe board
void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '-';
        }
    }
}

// Function to make a move
int makeMove(char board[SIZE][SIZE], int row, int col, char player) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != '-') {
        return 0; // Invalid move
    }
    board[row][col] = player;
    return 1; // Valid move
}

// Function to check for a win in a subgrid
char checkWinSubgrid(char board[SIZE][SIZE], int startRow, int startCol) {
    // Check rows, columns, and diagonals in the subgrid for a win
    // Return 'X' or 'O' if a player has won, otherwise return '-'
}

// Function to check for a win in the entire board
char checkWin(char board[SIZE][SIZE]) {
    // Check all subgrids for a win
    // Return 'X' or 'O' if a player has won the entire game, otherwise return '-'
}

// Main function to run the game
int main() {
    char board[SIZE][SIZE];
    char currentPlayer = 'X';
    int row, col;
    char winner = '-';

    initializeBoard(board);
    printBoard(board);

    // Game loop
    while (winner == '-') {
        printf("Player %c, enter row and column to make a move: ", currentPlayer);
        scanf("%d %d", &row, &col);
        if (makeMove(board, row, col, currentPlayer)) {
            printBoard(board);
            winner = checkWin(board);
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        } else {
            printf("Invalid move. Try again.\n");
        }
    }

    if (winner != '-') 
    {
        printf("Player %c wins!\n", winner);
    } 
    else 
    {
        printf("It's a draw!\n");
    }

    return 0;
}
