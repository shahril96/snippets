#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8
int base[SIZE][SIZE];

void shuffle(int arrayNum[]) {

    for(int i = 0; i < SIZE; i++) {
        int a = rand() % SIZE;
        int b = rand() % SIZE;

        int tmp = arrayNum[a];
        arrayNum[a] = arrayNum[b];
        arrayNum[b] = tmp;
    }
}

bool isSafe(int row, int col) {

    // check if queen is safe to put at (row, col)
    for(int i = 0; i <= row; i++) {

        // check upper row for current queen
        if(base[i][col])
            return false;

        // check lower diagonal for current queen
        else if(base[i][col - row - i])
            return false;

        // check upper diagonal for current queen
        else if(base[i][col + row - i])
            return false;
    }

    return true;
}

bool solve(int row) {

    // check if we already solve all queen problem
    if(row == SIZE) {
        return true;
    }

    int arrayNum[SIZE];

    for(int col = 0; col < SIZE; col++) {
        arrayNum[col] = col;
    }

    shuffle(arrayNum);

    for(int i = 0; i < SIZE; i++) {

        // take random col
        int col = arrayNum[i];

        // if queen can be placed here
        if(isSafe(row, col) == true) {

            // set queen at this position
            base[row][col] = 1;

            // check if can be solvable for next row
            if(solve(row + 1) == true)
                return true;

             else  // if can't solve next row, then backtrack to previous row
                base[row][col] = 0; // clear queen
        }
    }

    return false;
}

void draw() {

    char linelen[] = "-----------------------------------\n";

    for(int row = 0; row < SIZE; row++, printf(linelen)) {
        if(row == 0) printf(linelen);
        for(int col = 0; col < SIZE; col++) {
            if(col == 0) printf(" |");
            printf(" %s |%s", base[row][col] == 1 ? "1" : " ",
                              (col == SIZE-1) ? "\n" : "\0");
        }
    }
}

int main() {

    srand (time(NULL));

    if(solve(0) == true) {
        draw();
    } else {
        printf("Can't solve the problem!");
    }

}
