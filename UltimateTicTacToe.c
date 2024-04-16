#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define BOARD 9
#define ROW 3
#define COL 3
#define PLAYER1 'X'
#define PLAYER2 'O'

char board[9][3][3];

void resetBoard();
void printBoard();
char checkMiniWinner();

int main()
{
    int quit = 1;
    resetBoard();
    printf("Enter board #(1-9)");
    scanf("%d", &b);
    printMenu();
    do
    {
        
    }
    while(quit != 0);
    printBoard();
}

void resetBoard()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                board[i][j][k] = ' ';
            }
        }
    }
}

void printBoard()
{
    int i = 0;
    while (i < 9)
    {
        for (int j = 0; j < 3; j++)
        {
            printf ("  %c  |  %c  |  %c  /  %c  |  %c  |  %c  /  %c  |  %c  |  %c  \n", 
            board[i][j][0], board[i][j][1], board[i][j][2], board[i+1][j][0], 
            board[i+1][j][1], board[i+1][j][2], board[i+2][j][0], board[i+2][j][1], 
            board[i+2][j][2]);
            if (j != 2)
                printf ("-----|-----|-----/-----|-----|-----/-----|-----|-----\n");
        }
        if (i < 6)
            printf ("=====|=====|=====/=====|=====|=====/=====|=====|=====\n");
        i += 3;
    }
}

void player1Move(int b)
{
    int row;
    int col;

    do
    {
        /*Asks the user, row, and column to place their X or O
          If the spot is available it places, else its an invalid move and they try again*/
        printf("Enter row #(1-3): ");
        scanf("%d", &row);
        row--;
        printf("Enter column #(1-3): ");
        scanf("%d", &col);
        col--;
        if(board[b][row][col] != ' ')
        {
            printf("Invalid move!\n");
        }
        else
        {
            board[b][row][col] = PLAYER1;
            break;
        }
    } 
    while (board[b][row][col] != ' ');
}

void player2Move(int board)
{
    int row;
    int col;
    

    do
    {
        printf("Enter row #(1-3): ");
        scanf("%d", &row);
        row--;
        printf("Enter column #(1-3): ");
        scanf("%d", &col);
        col--;
        if(board[b][row][col] != ' ')
        {
            printf("Invalid move!\n");
        }
        else
        {
            board[b][row][col] = PLAYER2;
            break;
        }
    } 
    while (board[b][row][col] != ' ');
}

char checkMiniWinner()
{
    for (int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j][0] == board[i][j][1] && board[i][j][0] == board[i][j][2])
            {
                return board[i][j][0];
            }
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(board[i][0][j] == board[i][1][j] && board[i][0][j] == board[i][2][j])
            {
                return board[i][0][j];
            }
        }
    }
    for (int i = 0; i < 9; i++)
    {
        if(board[i][0][0] == board[i][1][1] && board[i][0][0] == board[i][2][2])
        {
            return board[i][0][0];
        }
    }
    for (int i = 0; i < 9; i++)
    {
        if(board[i][0][2] == board[i][1][1] && board[i][0][2] == board[i][2][0])
        {
            return board[i][0][2];
        }
    }
    return ' ';
}