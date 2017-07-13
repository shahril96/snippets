/**
 *
 * references :
 *
 * 1) http://www.geeksforgeeks.org/dynamic-programming-set-8-matrix-chain-multiplication/ 
 * 2) https://home.cse.ust.hk/~dekai/271/notes/L12/L12.pdf
 * 3) http://www.bowdoin.edu/~ltoma/teaching/cs231/spring14/Lectures/12-dynamicAndGreedy/matrixchain.pdf
 *
 **/


#include <iostream>
#include <climits>
#include <algorithm>
#include <cstring>
using namespace std;

int table[1000][1000];

int m(int p[], int i, int j) {

    if(table[i][j] != -1) {
        return table[i][j];
    } else {

        int min_cost = INT_MAX;

        if(i == j) {
            return table[i][j] = 0;
        }

        for(int k = i; k < j; k++) {
            min_cost = min(
                    m(p,i,k) + p[i-1]*p[k]*p[j] + m(p,k+1,j),
                    min_cost);
        }

        return table[i][j] = min_cost;
    }

}

int main() {

    int p[] = {1,2,3,4};
    int n = sizeof(p)/ sizeof(int);

    memset(table, -1, sizeof(int) * 1000 * 1000);

    cout << "min_cost : " << m(p, 1, n-1) << '\n';
}
