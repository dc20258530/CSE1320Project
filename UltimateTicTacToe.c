#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define BOARD 9
#define ROW 3
#define COL 3
#define PLAYER1 'X'
#define PLAYER2 'O'

char board[BOARD][ROW][COL]; // creating the board for the game
int b1; // variable used to pass i value from function checkMiniWinner to fillSubBoard

void resetBoard();
void printBoard();
void printReferenceBoard();
void menu(FILE* file);
void printGameRecords(FILE* file);
void updateGameRecords(FILE* file, char winner);
int player1Move(int b);
int player2Move(int b);
void printMenu();
void printInstructions();
void fillSubBoard();
void winLossCount(char player);
int checkSubBoard(int x, int y);
int checkFreeSpaces();
char checkMiniWinner();

int main()
{
    FILE *file;
    int b;
    char winner = ' ';
    resetBoard();

    file = fopen("gameRecords.txt", "r+");
    if(file == NULL)
    {
        printf("File not found. Creating new file.\n");
        file = fopen("gameRecords.txt", "w+");
        fprintf(file, "0 0");
        rewind(file);
    }

    menu(file);
    start:
    printReferenceBoard(file);
    printf ("Player 1 enter the board # desired: ");
    scanf ("%d", &b);
    b--;
    while(winner == ' ' && checkFreeSpaces() != 0)
    {
        printBoard();

        b = player1Move(b);
        fillSubBoard();
        printBoard();

        b = player2Move(b);
        fillSubBoard();
    }
    updateGameRecords(file, winner);
    menu(file);
    winner = ' ';
    goto start;
}

void menu(FILE* file){
    int quit = 1;
    do
    {
        printMenu();
        int choice;
        scanf("%d", &choice);

        switch(choice)
        {
            case 1 :
                quit = 0;
                break;
            case 2 :
                printInstructions();
                break;
            case 3 :
                printGameRecords(file);
            case 4 :
                printf("\nExiting... \n");
                fclose(file);
                exit(0);
            default : 
                printf("\nInvalid choice. Please enter a valid option.\n");
        }
    }
    while(quit != 0);

}

void printGameRecords(FILE* file)
{
    int p1wins, p2wins; 
    fscanf(file, "%d %d", &p1wins, &p2wins);
    printf("Player 1 Wins: %d\n Player 2 Wins: %d\n", p1wins, p2wins);
}

void updateGameRecords(FILE* file, char winner)
{
    int p1wins, p2wins;
    fscanf(file, "%d %d", &p1wins, &p2wins);

    if(winner=='X')
    {
        p1wins++;
    }
    else{
        p2wins++;
    }

    fseek(file, 0, SEEK_SET);
    fprintf(file, "%d %d", p1wins, p2wins);

}

void resetBoard()
{
    for(int i = 0; i < BOARD; i++)
    {
        for(int j = 0; j < ROW; j++)
        {
            for(int k = 0; k < COL; k++)
            {
                board[i][j][k] = ' ';
            }
        }
    }
}

void printBoard()
{
    int i = 0;
    while (i < BOARD)
    {
        for (int j = 0; j < ROW; j++)
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


void printReferenceBoard()
{
    int i = 0;
    printf ("  1     2     3     1     2     3     1     2     3\n");
    while (i < 9)
    {
        for (int j = 0; j < 3; j++)
        {
            printf ("%d", j+1);
            if (j != 1)
                printf ("      |     |     /     |     |     /     |     |     \n");
            else 
                printf ("      |  %d  |     /     |  %d  |     /     |  %d  |     \n",
                    i+1, i+2, i+3);
            if (j != 2)
                printf ("  -----|-----|-----/-----|-----|-----/-----|-----|-----\n");
        }
        if (i < 6)
            printf ("  =====|=====|=====/=====|=====|=====/=====|=====|=====\n");
        i += 3;
    }
}

int player1Move(int b)
{
    int row, col, check;

    do
    {
        check = 0;
        /*Asks the user, row, and column to place their X or O
          If the spot is available it places, else its an invalid move and they try again*/
        printf("Enter row #(1-3) in the correct board: ");
        scanf("%d", &row);
        row--;
        printf("Enter column #(1-3) in the correct board: ");
        scanf("%d", &col);
        col--;
        if (board[b][row][col] != ' ')
        {
            printf("Invalid move!\n");
            for (int j = 0; j < ROW; j++)
            {
                for (int k = 0; k < COL; k++)
                {
                    if (board[b][j][k] == PLAYER1 || board[b][j][k] == PLAYER2)
                        check++;
                }
            }
            if (check == 9)
            {
                printf ("Board is full, enter any open board #(1-9): ");
                scanf ("%d", &b);
                //continue;
            }
        }
        else
        {
            board[b][row][col] = PLAYER1;
            return moveSubBoard(col, row);
        }
    } 
    while (board[b][row][col] != ' ');
}

void printMenu()
{
    printf("\n\n       Ultimate TicTacToe\n");
    printf("************* Menu *************\n");
    printf("[1] PLAY\n");
    printf("[2] Instructions\n");
    printf("[3]See Game Records\n");
    printf("[4] Exit\n");
    printf("Select an option\n");
    printf("********************************\n:: ");
}

void printInstructions() 
{
    printf("\nInstructions for Ultimate Tic Tac Toe:\n");
    printf("----------------------------------------\n");
    printf("Objective:\n");
    printf("The objective of Ultimate Tic Tac Toe is to win three traditional Tic Tac Toe games\n");
    printf("in a row, column, or diagonal on the global board.\n\n");
    
    printf("Rules:\n");
    printf("1. Ultimate Tic Tac Toe is played on a 3x3 grid of 3x3 grids (total 9 boards).\n");
    printf("2. Players take turns to place their symbol (X or O) in an empty cell.\n");
    printf("3. The cell chosen determines the board the opponent must play on next.\n");
    printf("4. To win a local board, a player must win three traditional Tic Tac Toe games.\n");
    printf("5. Once a local board is won or drawn, it can't be played on again.\n");
    printf("6. If a move sends the opponent to a finished board, the player can choose\n");
    printf("   any unfinished board to play on.\n\n");

    printf("Gameplay:\n");
    printf("1. Player 1 (X) starts the game.\n");
    printf("2. Each player takes turns making moves until one player wins or the game draws.\n");
    printf("3. If a player wins a local board, they mark the corresponding cell on the global board.\n");
    printf("4. The first player to win three local boards in a row, column, or diagonal on the\n");
    printf("   global board wins the game.\n\n");

    printf("Legend:\n");
    printf(" - Local Board: A 3x3 grid where players make their moves.\n");
    printf(" - Global Board: A 3x3 grid where the results of the local boards are shown.\n");
    printf("   A cell in the global board is marked when a player wins a local board.\n");
    printf(" - X: Player 1's symbol.\n");
    printf(" - O: Player 2's symbol.\n\n");

    printf("Enjoy playing Ultimate Tic Tac Toe!\n");
}

int player2Move(int b)
{
    int row, col, check;

    do
    {
        check = 0;
        printf("Enter row #(1-3): ");
        scanf("%d", &row);
        row--;
        printf("Enter column #(1-3): ");
        scanf("%d", &col);
        col--;
        if(board[b][row][col] != ' ')
        {
            printf("Invalid move!\n");
            for (int j = 0; j < ROW; j++)
            {
                for (int k = 0; k < COL; k++)
                {
                    if (board[b][j][k] == PLAYER1 || board[b][j][k] == PLAYER2)
                        check++;
                }
            }
            if (check == 9)
            {
                printf ("Board is full, enter any open board #(1-9): ");
                scanf ("%d", &b);
                continue;
            }
        }
        else
        {
            board[b][row][col] = PLAYER2;
            return moveSubBoard(col, row);
        }
    } 
    while (board[b][row][col] != ' ');
}

void fillSubBoard()
{
    char miniWinner = checkMiniWinner();
    if (miniWinner == 'X' || miniWinner == 'O') 
    {
        for (int a = 0; a < 3; a++) 
        {
            for (int b = 0; b < 3; b++) 
            {
                board[b1][a][b] = miniWinner;
            }
        }
    }
}

int moveSubBoard(int x, int y)
{
    if (y == 0)
    {
        if (x == 0)
            return 0;
        if (x == 1)
            return 1;
        if (x == 2)
            return 2;
    }
    if (y == 1)
    {
        if (x == 0)
            return 3;
        if (x == 1)
            return 4;
        if (x == 2)
            return 5;
    }
    if (y == 2)
    {
        if (x == 0)
            return 6;
        if (x == 1)
            return 7;
        if (x == 2)
            return 8;
    }
}

int checkFreeSpaces()
{
    int freeSpaces = 81;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if(board[i][j][k] != ' ')
                {
                    freeSpaces--;
                }
            }
        }
    }

    return freeSpaces;
}

char checkMiniWinner()
{
    int i;
    for (i = 0; i < 9; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j][0] != ' ' && board[i][j][0] == board[i][j][1] && 
                board[i][j][0] == board[i][j][2])
            {
                b1 = i;
                return board[i][j][0];
            }
        }
    }
    for (i = 0; i < 9; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(board[i][0][j] != ' ' && board[i][0][j] == board[i][1][j] && 
                board[i][0][j] == board[i][2][j])
            {
                b1 = i;
                return board[i][0][j];
            }
        }
    }
    for (i = 0; i < 9; i++)
    {
        if(board[i][0][0] != ' ' && board[i][0][0] == board[i][1][1] && 
            board[i][0][0] == board[i][2][2])
        {
            b1 = i;
            return board[i][0][0];
        }
    }
    for (i = 0; i < 9; i++)
    {
        if(board[i][0][2] != ' ' && board[i][0][2] == board[i][1][1] && 
            board[i][0][2] == board[i][2][0])
        {
            b1 = i;
            return board[i][0][2];
        }
    }
}