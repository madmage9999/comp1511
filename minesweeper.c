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

void rowCount(int minefield[SIZE][SIZE], int aCounter);
void colCount(int minefield[SIZE][SIZE], int aCounter);
int squareCheck(int minefield[SIZE][SIZE], int aCounter,
     int bCounter, int cCounter);
int squareReveal(int minefield[SIZE][SIZE], int aCounter,
     int bCounter, int win, int mineCounter);
void printGameField(int minefield[SIZE][SIZE], int win);
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
    int aCounter = 0;
    int bCounter = 0;
    int cCounter = 0;
    int win = 1;
    int hintCounter = 0;
    int gameCounter = 0;
    printf("Game Started\n");
    print_debug_minefield(minefield);
    //printf("Entering second loop\n");
    while(win == 1 && 0 < scanf("%d", &detector)) {
    //printf("in loop\n");
        win = fieldCheck((minefield), win);
        if (hintCounter == HINTS && detector <=DETECT_SQUARE) {
            scanf("%d %d %d", &aCounter, &bCounter, &cCounter);
            printf("Help already used\n");
            printf("%d\n", hintCounter);
        }

        else if (detector == DETECT_ROW && hintCounter < 3) {
            //printf("detecting row\n");
            scanf("%d", &aCounter);
            rowCount((minefield), aCounter);
            if (gameCounter == 0) {
                print_debug_minefield(minefield);
            }
            else {
                printGameField(minefield, win);
            }
            hintCounter ++;

        }

        else if (detector == DETECT_COL && hintCounter < 3) {
            //printf("detecting column\n");
            scanf("%d", &aCounter);
            colCount((minefield), aCounter);
            if (gameCounter == 0) {
                print_debug_minefield(minefield);
            }
            else {
                printGameField(minefield, win);
            }
            hintCounter ++;
        }

        else if (detector == DETECT_SQUARE && hintCounter < 3) {
            //printf("detecting square\n");
            scanf("%d %d %d", &aCounter, &bCounter, &cCounter);
            mineCounter = squareCheck((minefield), aCounter, bCounter, cCounter);
            printf("There are %d mine(s) in the square centered at row %d,\
column %d of size %d\n", mineCounter, aCounter, bCounter, cCounter);
            //printf("%d", mineCounter);
            if (gameCounter == 0) {
                print_debug_minefield(minefield);
            }
            else {
                printGameField(minefield, win);
            }
            hintCounter ++;
        }

        else if (detector == REVEAL_SQUARE) {
            scanf("%d %d", &aCounter, &bCounter);
            mineCounter = squareCheck((minefield), aCounter, bCounter, cCounter);
            win = squareReveal((minefield), aCounter, bCounter, win, mineCounter);
            if (gameCounter == 0) {
                print_debug_minefield(minefield);
            }
            else {
                printGameField(minefield, win);
            }

        }

        else if (detector == GAMEPLAY_MODE) {
            printf("Gameplay mode activated\n");
            printGameField(minefield, win);
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
void rowCount(int minefield[SIZE][SIZE], int aCounter) {
    int x = 0;
    int rowCounter = 0;
    while (x < SIZE) {
        if ((minefield[aCounter][x]) == 2) {
            rowCounter ++;

        }
        x ++;
    }
    printf("There are %d mine(s) in row %d\n", rowCounter, aCounter);
}

//counts how many mines in colCount
void colCount(int minefield[SIZE][SIZE], int aCounter) {
    int x = 0;
    int colCounter = 0;
    while (x < SIZE) {
        if ((minefield[x][aCounter]) == 2) {
            colCounter ++;

        }
        x ++;
    }
    printf("There are %d mine(s) in column %d\n", colCounter, aCounter);
}

//checks how many mines in a square
int squareCheck(int minefield[SIZE][SIZE], int aCounter,
     int bCounter, int cCounter) {
    int mineCounter = 0;
    int x = aCounter;
    int y = bCounter;
    int z = 0;
    int a = 0;
    if (cCounter == 3 || cCounter == 0) {
        aCounter --;
        bCounter --;
        cCounter = 3;
    }
    if (cCounter == 5) {
        aCounter = aCounter - 2;
        bCounter = bCounter - 2;
    }
    while (z < cCounter * cCounter && aCounter >= 0 && bCounter >= 0 &&
        aCounter <SIZE && bCounter < SIZE) {
        if ((minefield[aCounter][bCounter]) == 2){
            mineCounter ++;
        }
        z ++;
        bCounter ++;
        if (z == 3) {
            z = 0;
            aCounter ++;
            bCounter = y;
            a++;
        }
        if (a == 3) {
            break;
        }
    }
    aCounter = x;
    bCounter = y;    
    return mineCounter;
}


//Reveals mines in square
int squareReveal(int minefield[SIZE][SIZE], int aCounter, int bCounter, int win, int mineCounter) {
    //int x = 0;
    int z = 0;
    //printf("%d\n", aCounter);
    //printf("%d\n", bCounter);
    //printf("%d\n", mineCounter);
    int a = aCounter;
    int b = bCounter;
    aCounter --;
    bCounter --;

    if (mineCounter > 0 && minefield[a][b] != HIDDEN_MINE) {
        minefield[a][b] = VISIBLE_SAFE;
    } else {
        while (z < 9 && win == 1) {

            if (aCounter >= 0 && bCounter >= 0 &&
            aCounter < SIZE && bCounter < SIZE && 
            minefield[aCounter][bCounter] == HIDDEN_SAFE) {
                minefield[aCounter][bCounter] = VISIBLE_SAFE;
            }
            else if ((aCounter >= 0 && bCounter >= 0 &&
            aCounter < SIZE && bCounter < SIZE && 
            (minefield[aCounter][bCounter]) == HIDDEN_MINE)) {
                win = 0;
                printf("Game over\n");
                break;
            }
            z++;
            bCounter ++;
            if (z % 3 == 0) {
                aCounter ++;
                bCounter = b - 1;
            }
        }
    }
    return win;
}
//Prints gameplay field
void printGameField(int minefield[SIZE][SIZE], int win) {
    if (win == 0) {
        printf("xx\n");
        printf("/\\\n");
    }
    else {
        printf("..\n");
        printf("\\/\n");
    }
    printf("    00 01 02 03 04 05 06 07\n");
    printf("   -------------------------\n");
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        printf("0%d |", i);
        while (j < SIZE){
            if (minefield[i][j] == VISIBLE_SAFE){
                printf("   ");
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
    printf("   --------------------------\n");
}

//Checks if game is lost yet
int fieldCheck(int minefield[SIZE][SIZE], int win) {
    int i = 0;
    int x = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            if (minefield[i][j] == HIDDEN_SAFE || minefield[i][j] == VISIBLE_SAFE) {
                x ++;
            } 
            else if (x < 0) {
                win = 0;
                break;
            }
            j++;
        }
        i++;
    }
    return win;
} 

