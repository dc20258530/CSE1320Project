#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[9][9];

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
        for(int j = 0; j < 9; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void printBoard()
{
    int R = 0, C = 3;
    /*printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---");
    printf("\n %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---");
    printf("\n %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");*/
    for (int i = 0; i < 3; i++)
    {
        for(int j = R; j < C; j++)
        {
            //printf("%d", j);
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
    }
}