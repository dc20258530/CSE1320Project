#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ROWS 9
#define COLS 9

typedef char Board[ROWS][COLS];
typedef char MetaBoard[ROWS / 3][COLS / 3];
typedef enum {VALID, NOT_A_DIGIT, NOT_IN_BOARD, SPACE_OCCUPIED, OUT_OF_BOUNDS} MoveStatus;

void fillSubBoard(Board board, int x, int y, char c)
{
    for (; (x % 3) != 0; x--); // quickly set x to left bound of sub-board
    for (; (y % 3) != 0; y--); // quickly set y to upper bound of sub-board
    for (int rowMax = x + 2, row = x; row <= rowMax; row++)
    {
        for (int columnMax = y + 2, column = y; column <= columnMax; column++)
        {
            board[row][column] = c;
        }
    }
}

int getRowBound(int row)
{
    switch (row)
    {
        case 0 ... 2:
            return 0;
        case 3 ... 5:
            return 1;
        case 6 ... 8:
            return 2;
        default:
            return -1;
    }
}

int getColumnBound(int column)
{
    switch (column)
    {
        case 0 ... 2:
            return 0;
        case 3 ... 5:
            return 1;
        case 6 ... 8:
            return 2;
        default:
            return -1;
    }
}

void printBoard(Board board)
{
    printf("\n=============||===========||=============\n");
    for (int row = 0; row < ROWS; row++)
    {
        printf("||");
        for (int column = 0; column < COLS; column++)
        {
            if (board[row][column] == '-') printf("%d,%d|", row, column);
            else printf(" %c |", board[row][column]);
            if (0 == (column+1) % 3) printf("|");
        }
        if ((row+1) % 3 == 0) printf("\n=============||===========||=============\n");
        else printf("\n-----|---|---||---|---|---||---|---|-----\n");
    }
}

static int checkMeta(MetaBoard meta)
{
    const int xStart[ROWS - 1] = {0,  0,  0,  0,  1,  2,  0,  0};
    const int yStart[COLS - 1] = {0,  1,  2,  0,  0,  0,  0,  2};
    const int xDelta[ROWS - 1] = {1,  1,  1,  0,  0,  0,  1,  1};
    const int yDelta[COLS - 1] = {0,  0,  0,  1,  1,  1,  1,  1};
    static int startx, starty, deltax, deltay;
    for (int trip = 0; trip < ROWS - 1; trip++)
    {
        startx = xStart[trip];
        starty = yStart[trip];
        deltax = xDelta[trip];
        deltay = yDelta[trip];
        // main logic to check if a subboard has a winner
        if (meta[startx][starty] != '-' &&
            meta[startx][starty] == meta[startx + deltax][starty + deltay] &&
            meta[startx][starty] == meta[startx + deltax + deltax][starty + deltay + deltay]) return 1;
    }
    return 0;
}

static int checkBoard(Board board, MetaBoard meta, int player, int row, int column)
{
    const int xStart[ROWS - 1] = {0,  0,  0,  0,  1,  2,  0,  0};
    const int yStart[COLS - 1] = {0,  1,  2,  0,  0,  0,  0,  2};
    const int xDelta[ROWS - 1] = {1,  1,  1,  0,  0,  0,  1,  1};
    const int yDelta[COLS - 1] = {0,  0,  0,  1,  1,  1,  1,  1};
    static int startx, starty, deltax, deltay, status = 0;

    for (; (row % 3) != 0; row--); // quickly set row to left bound of sub-board
    for (; (column % 3) != 0; column--); // quickly set column to upper bound of sub-board

    for (int trip = 0; trip < ROWS - 1; trip++)
    {

        startx = row + xStart[trip];
        starty = column + yStart[trip];
        deltax = xDelta[trip];
        deltay = yDelta[trip];
        if (board[startx][starty] != '-' &&
            board[startx][starty] == board[startx + deltax][starty + deltay] &&
            board[startx][starty] == board[startx + deltax + deltax][starty + deltay + deltay])
        {
            fillSubBoard(board, row, column, (player == 1) ? 'X' : 'O');
            meta[getRowBound(row)][getColumnBound(column)] = (player == 1) ? 'X' : 'O';
            status = 1;
        }
    }
    return (status + checkMeta(meta)); // always check if the game has a winner
}

MoveStatus validCoords(Board board, int row, int column, int rowBound, int columnBound)
{
    if (!isdigit((char)(((int)'0') + row)) && !isdigit((char)(((int)'0') + column))) return NOT_A_DIGIT; // supplied coordinates aren't digits 1-9
    else if (row > ROWS - 1 || column > COLS - 1) return NOT_IN_BOARD; // supplied coordinates aren't within the bounds of the board
    else if (board[row][column] != '-') return SPACE_OCCUPIED; // supplied coordinates are occupied by another character
    else if (rowBound == -1 && columnBound == -1) return VALID; // supplied coordinates can move anywhere
    else if (((row > rowBound * 3 + 2 || column > columnBound * 3 + 2) ||
              (row < rowBound * 3 || column < columnBound * 3)) &&
             (rowBound > 0 && columnBound > 0)) return OUT_OF_BOUNDS; // coordinates aren't within the sub-board specified by the previous move
    else return VALID; // didn't fail anywhere else, so coords are valid
}

int main(void)
{
    int winner = 0, row = 0, column = 0, rowBound = -1, columnBound = -1, invalid = 0;
    char tempRow = '\0', tempColumn = '\0';
    Board board;
    MetaBoard meta;
    // initialize boards and fill with '-'
    memset(board, '-', ROWS * COLS * sizeof(char));
    memset(meta, '-', (ROWS / 3) * (COLS / 3) * sizeof(char));

    // game loop
    for (int turn = 0; turn < ROWS * COLS && !winner; turn++)
    {
        int player = (turn % 2) + 1;
        printBoard(board);
        printf("Player %d, enter the coordinates (x, y) to place %c: ", player, (player==1) ? 'X' : 'O');
        do
        {
            scanf("%c, %c", &tempRow, &tempColumn);
            for(; getchar() != '\n'; getchar()); // pick up superfluous input so we don't run into problems when we scan for input again
            row = abs((int) tempRow - '0');
            column = abs((int) tempColumn - '0');
            invalid = 0;
            switch (validCoords(board, row, column, rowBound, columnBound))
            {
                case NOT_A_DIGIT:
                    printf("Invalid input.  Re-enter: ");
                    invalid = 1;
                    break;
                case NOT_IN_BOARD:
                    printf("Out of board's bounds. Re-enter: ");
                    invalid = 2;
                    break;
                case SPACE_OCCUPIED:
                    printf("There is already an %c there.  Re-enter: ", board[row][column]);
                    invalid = 3;
                    break;
                case OUT_OF_BOUNDS:
                    printf("Your move was in the wrong sub-board.  Re-enter: ");
                    invalid = 4;
                    break;
                default:
                    break;
            }
        } while (invalid);

        board[row][column] = (player == 1) ? 'X' : 'O';
        switch(checkBoard(board, meta, player, row, column))
        {
            case 1:
                // next move can be anywhere
                rowBound = -1;
                columnBound = -1;
                break;
            case 2:
                winner = player;
                break;
            default:
                rowBound = row % 3;
                columnBound = column % 3;
                break;
        }
    }
    printBoard(board);

    if(!winner) printf("The game is a draw\n");
    else printf("Player %d has won\n", winner);

    return 0;
}