#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[9][3][3];

void resetBoard();
void printBoard();

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
    /*int R = 0, C = 3;
    for (int i = 0; i < 3; i++)
    {
        for(int j = R; j < C; j++)
        {
            printf("  %c  |  %c  |  %c  /  %c  |  %c  |  %c  /  %c  |  %c  |  %c  \n",
                board[j][0], board[j][1], board[j][2], board[j][3],
                board[j][4], board[j][5], board[j][6], board[j][7], board[j][8]);
            if(j == 2 || j == 5)
            {
                printf("=====|=====|=====/=====|=====|=====/=====|=====|=====\n");
            }
            else if(j == 8)
            {
                break;
            }
            else
            {
                printf("-----|-----|-----/-----|-----|-----/-----|-----|-----\n");
            }
        }
        C += 3;
        R += 3;
    }*/
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