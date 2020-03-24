// Assignment 1 20T1 COMP1511: Minesweeper
//
// This program was written by Steve Li (z5310206)
// on INSERT-DATE-HERE
//
// Version 1.0.0 (2020-03-08): Assignment released.

#include <stdio.h>
#include <stdlib.h>

// Possible square states.
#define VISIBLE_SAFE    0
#define HIDDEN_SAFE     1
#define HIDDEN_MINE     2

// The size of the starting grid.
#define SIZE 8

// The possible command codes.
#define DETECT_ROW              1
#define DETECT_COL              2
#define DETECT_SQUARE           3
#define REVEAL_SQUARE           4
#define GAMEPLAY_MODE           5
#define DEBUG_MODE              6
#define REVEAL_RADIAL           7

// Add any extra #defines here.

#define MINEFIELD_SIZE          64
#define SQUARE_SIZE             9
#define HINTS                   3

void initialise_field(int minefield[SIZE][SIZE]);
void print_debug_minefield(int minefield[SIZE][SIZE]);

// Place your function prototyes here.

void rowCount(int minefield[SIZE][SIZE], int row);
void colCount(int minefield[SIZE][SIZE], int row);
int squareCheck(int minefield[SIZE][SIZE], int row,
     int column, int sqSize);
int squareReveal(int minefield[SIZE][SIZE], int row,
     int column, int win, int mineCounter);
void printGameField(int minefield[SIZE][SIZE], int win, int mineCounter);
int fieldCheck(int minefield[SIZE][SIZE], int win);

int main(void) {
    //initialise minefield
    int minefield[SIZE][SIZE];
    initialise_field(minefield);
    printf("Welcome to minesweeper!\n");
    printf("How many mines? ");

    //Scans how many mines
    int noMines = 0;
    scanf("%d", &noMines);
    /*while (noMines <= 0) {
       printf("How many mines? ");
       scanf("%d", &noMines);
    }*/
    int mineCounter = 0;
    printf("Enter pairs:\n");

    int minerow = 0;
    int minecolumn = 0;


    //printf("entering first loop\n");
    while (mineCounter < MINEFIELD_SIZE && noMines != 0 &&
           (scanf("%d %d", &minerow, &minecolumn) == 2 )) {
        // change condition into a function//
        //change if statement t o a function//
        mineCounter ++;
        if (minerow <= SIZE && minecolumn <= SIZE &&
             minerow >= 0 && minecolumn >= 0) {
            minefield[minerow][minecolumn] = HIDDEN_MINE;
        }
        noMines --;
        if (noMines == 0) {
            break;
        }
    }
    int detector = 0;
    int row = 0;
    int column = 0;
    int sqSize = 0;
    int win = 1;
    int hintCounter = 0;
    int gameCounter = 0;
    printf("Game Started\n");
    print_debug_minefield(minefield);
    //printf("Entering second loop\n");
    while(win == 1 && 0 < scanf("%d", &detector)) {
    //printf("in loop\n");
        win = fieldCheck((minefield), win);
        if (hintCounter == HINTS && detector <=DETECT_COL) {
           // scanf("%d %d %d", &row, &column, &sqSize);
            scanf("%d", &row);
            printf("Help already used\n");
            if (gameCounter == 0) {
                print_debug_minefield(minefield);
            }
            else {
                printGameField(minefield, win, mineCounter);
            }
            //printf("%d\n", hintCounter);
        }
        
        else if (hintCounter == HINTS && detector == DETECT_SQUARE) {
            scanf("%d %d %d", &row, &column, &sqSize);
            printf("Help already used\n");
            if (gameCounter == 0) {
                print_debug_minefield(minefield);
            }
            else {
                printGameField(minefield, win, mineCounter);
            }
            //printf("%d\n", hintCounter);
        }

        else if (detector == DETECT_ROW && hintCounter < 3) {
            //printf("detecting row\n");
            scanf("%d", &row);
            rowCount((minefield), row);
            if (gameCounter == 0) {
                print_debug_minefield(minefield);
            }
            else {
                printGameField(minefield, win, mineCounter);
            }
            hintCounter ++;

        }

        else if (detector == DETECT_COL && hintCounter < 3) {
            //printf("detecting column\n");
            scanf("%d", &row);
            colCount((minefield), row);
            if (gameCounter == 0) {
                print_debug_minefield(minefield);
            }
            else {
                printGameField(minefield, win, mineCounter);
            }
            hintCounter ++;
        }

        else if (detector == DETECT_SQUARE && hintCounter < 3) {
            //printf("detecting square\n");
            scanf("%d %d %d", &row, &column, &sqSize);
            mineCounter = squareCheck((minefield), row, column, sqSize);
            printf("There are %d mine(s) in the square centered at row %d,\
column %d of size %d\n", mineCounter, row, column, sqSize);
            //printf("%d", mineCounter);
            if (gameCounter == 0) {
                print_debug_minefield(minefield);
            }
            else {
                printGameField(minefield, win, mineCounter);
            }
            hintCounter ++;
        }

        else if (detector == REVEAL_SQUARE) {
            scanf("%d %d", &row, &column);
            mineCounter = squareCheck((minefield), row, column, sqSize);
            //printf("%d\n", mineCounter);
            win = squareReveal((minefield), row, column, win, mineCounter);
            win = fieldCheck((minefield), win);
            if (gameCounter == 0) {
                print_debug_minefield(minefield);
            }
            else {
                printGameField(minefield, win, mineCounter);
            }

        }

        else if (detector == GAMEPLAY_MODE) {
            printf("Gameplay mode activated\n");
            printGameField(minefield, win, mineCounter);
            gameCounter = 1;

        }

        else if (detector == DEBUG_MODE) {
            printf("Debug mode activated\n");
            print_debug_minefield(minefield);
            gameCounter = 0;

        }
    }
    //if (win == 0) {
        //printf("Game over\n");
    

    return 0;
}


//Functions
// Set the entire minefield to HIDDEN_SAFE.
void initialise_field(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            minefield[i][j] = HIDDEN_SAFE;
            j++;
        }
        i++;
    }
}

// Print out the actual values of the minefield.
void print_debug_minefield(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            printf("%d ", minefield[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

//counts how many mines in rowCount
void rowCount(int minefield[SIZE][SIZE], int row) {
    int x = 0;
    int rowCounter = 0;
    while (x < SIZE) {
        if ((minefield[row][x]) == 2) {
            rowCounter ++;

        }
        x ++;
    }
    printf("There are %d mine(s) in row %d\n", rowCounter, row);
}

//counts how many mines in colCount
void colCount(int minefield[SIZE][SIZE], int row) {
    int x = 0;
    int colCounter = 0;
    while (x < SIZE) {
        if ((minefield[x][row]) == 2) {
            colCounter ++;

        }
        x ++;
    }
    printf("There are %d mine(s) in column %d\n", colCounter, row);
}

//checks how many mines in a square
//make for case 7

int squareCheck(int minefield[SIZE][SIZE], int row, int column, int sqSize) {
    int mineCounter = 0;
    int x = 0;
    int y = column;
    int z = 0;
    int a = 0;
    //int b = 0;
    if (sqSize == 3 || sqSize == 0) {
        row --;
        column --;
        sqSize = 3;
    }
    if (sqSize == 5) {
        row = row - 2;
        column = column - 2;
    }
    if (sqSize == 7) {
        row = row - 3;
        column = column - 3;
    }
    if (row < 0) {
        row = 0;
        if (sqSize == 3) {
            x = 1;
            //b = x;
        }
        else if (sqSize == 5) {
            x = 2;
           // b = x;
        }
        else if (sqSize == 7) {
            x = 3;
            //b = x;
        }
    }
    if (column < 0) {
        column = 0;
        if (sqSize == 3) {
            z = 1;
            a = z;
        }
        else if (sqSize == 5) {
            z = 2;
            a = z;
        }
        else if (sqSize == 7) {
            z = 3;
            a = z;
        }
    }
    /*printf("a: %d\n", row);
    printf("b: %d\n", column);
    printf("c: %d\n", sqSize);*/
    while (z < sqSize && row >= 0 && column >= 0 &&
        row <SIZE && column < SIZE) {
        //printf("a, b, x, z: %d %d %d %d\n", row, column, x, z);
        if ((minefield[row][column]) == HIDDEN_MINE){
            mineCounter ++;
        }
        z ++;
        column ++;
        if (z == sqSize || column == SIZE) {
            z = a;
            //x = b;
            row ++;
            if (y > 0) {
            column = y - 1;
            } else {
            column = y;
            }
            x ++;
        }
        if (x == sqSize || row == SIZE) {
            break;
        }
    }

    return mineCounter;
}


//Reveals mines in square
int squareReveal(int minefield[SIZE][SIZE], int row, int column, int win, int mineCounter) {
    //int x = 0;
    int z = 0;
    //printf("%d\n", row);
    //printf("%d\n", column);
    //printf("%d\n", mineCounter);
    int a = row;
    int b = column;

    row --;
    column --;

    if (mineCounter > 0 && minefield[a][b] != HIDDEN_MINE) {
        minefield[a][b] = VISIBLE_SAFE;
    } else {
        while (z < 9 && win == 1) {
            //printf("%d\n", row);
            //printf("%d\n", column);

            if (row >= 0 && column >= 0 &&
            row < SIZE && column < SIZE && 
            minefield[row][column] == HIDDEN_SAFE) {
                minefield[row][column] = VISIBLE_SAFE;
            }
            else if ((row >= 0 && column >= 0 &&
            row < SIZE && column < SIZE && 
            (minefield[row][column]) == HIDDEN_MINE)) {
                win = 0;
                printf("Game over\n");
                break;
            }
            z++;
            column ++;
            if (z % 3 == 0) {
                row ++;
                column = b - 1;
            }
        }
    }
    return win;
}
//Prints gameplay field
void printGameField(int minefield[SIZE][SIZE], int win, int mineCounter) {
    if (win == 0) {
        printf("xx\n");
        printf("/\\\n");
    }
    else {
        printf("..\n");
        printf("\\/\n");
    }
    printf("   00 01 02 03 04 05 06 07\n");
    printf("   -------------------------\n");
    int i = 0;    
    if (win == 1) {
        while (i < SIZE) {
            int j = 0;
            printf("0%d |", i);
            while (j < SIZE){
                if (minefield[i][j] == VISIBLE_SAFE && mineCounter == 0) {
                    mineCounter = squareCheck(minefield, i, j, 3);
                    if (mineCounter > 0) {
                    printf("0%d ", mineCounter);
                    mineCounter = 0;
                    } else {
                    printf("   ");
                    }
                } 
                else if (minefield[i][j] == VISIBLE_SAFE && mineCounter > 0) {
                printf("0%d ", mineCounter);
                mineCounter = 0;
                }
            
                if (minefield[i][j] == HIDDEN_MINE || minefield[i][j] == HIDDEN_SAFE) {
                    printf("## ");
                }
                j ++;
            }
            printf("|");
            printf("\n");
            i ++;
        }
    }
    else if (win == 0) {
        while (i < SIZE) {
            int j = 0;
            printf("0%d |", i);
            while (j < SIZE) {
                if (minefield[i][j] == HIDDEN_MINE) {
                    printf("() ");
                }
                if (minefield[i][j] == VISIBLE_SAFE){
                    printf("   ");
                }
                if (minefield[i][j] == HIDDEN_SAFE) {
                    printf("## ");
                }
                j ++;       
            }
            printf("|");
            printf("\n");
            i ++;
        }
    }
    printf("   -------------------------\n");
}

//Checks if game is won yet
int fieldCheck(int minefield[SIZE][SIZE], int win) {
    int i = 0;
    int x = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            if (minefield[i][j] == HIDDEN_SAFE) {
                x ++;
            } 

            j++;
        }
        i++;
    }
    if (x == 0) {
        win = 1;
        printf("Game won!\n");
    } 
    return win;
}

