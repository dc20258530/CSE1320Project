#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[9][3][3];

void resetBoard();
void printBoard();
char checkMiniWinner();

int main()
{
    resetBoard();
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