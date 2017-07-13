#include <stdio.h>
#include <stdbool.h>

#define N 6

// 0 = valid box to step
// x = invalid box to step (halangan)
char board[N][N] = {
    { 0 ,'x','x','x','x','x'},
    { 0 , 0 , 0 ,'x', 0 ,'x'},
    {'x','x', 0 ,'x', 0 ,'x'},
    { 0 , 0 , 0 , 0 , 0 ,'x'},
    {'x','x', 0 ,'x', 0 ,'x'},
    {'x','x', 0 , 0 , 0 , 0 }
};

void draw() {

    char linelen[] = "---------------------------";

    for(int row = 0; row < N; row++, puts(linelen)) {
        if(row == 0) puts(linelen);
        for(int col = 0; col < N; col++) {
            if(col == 0) printf(" |");
            printf(" %c |%c", board[row][col] == 0 ? ' ' : board[row][col],
                              (col == N-1) ? '\n' : '\0');
        }
    }
}

bool isSafe(int row, int col) {

    if(board[row][col] == 'x')
        return false;

    else if(row < 0 || row >= N)
        return false;

    else if(col < 0 || col >= N)
        return false;

    else if(board[row][col] == 1)
        return false;

    return true;

}

bool solve(int row, int col, // use for recursion
           int target_row, int target_col) // use for endpoint checking
    {

    if(row == target_row && col == target_col)
        return true;

    static int next_pos[4][2] = {
        {1, 0}, // go above
        {0, 1}, // go right
        {-1, 0}, // go below
        {0, -1} // go left
    };

    for(int i = 0; i < 4; i++) {

        int next_row = row + next_pos[i][0];
        int next_col = col + next_pos[i][1];

        if(isSafe(next_row, next_col) == true) {

            board[next_row][next_col] = '*';

            if(solve(next_row, next_col, target_row, target_col) == true)
                return true;
            else
                board[next_row][next_col] = 0;

        }
    }

    return false;
}

int main() {

    board[0][0] = '*';

    if(solve(0, 0, N-1, N-1) == true) {
        draw();
        puts("Origin : (0,0)");
        puts("Ending : (5,5)");
    } else {
        puts("Failed to find path for rat");
    }

    return 0;
}
