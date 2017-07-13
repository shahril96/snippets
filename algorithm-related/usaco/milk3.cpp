/*
 ID: mohd_sh2
 LANG: C++11
 TASK: milk3
 */


#include <iostream>
#include <cstdio>
#include <fstream>
#include <tuple>
#include <utility>
using namespace std;
typedef pair<int, int> pii;

#define SIZE 25

bool solutions[SIZE];
bool mark[SIZE][SIZE][SIZE]; // mark visited

// length for each buckets
int al, bl, cl;

// temp vars
int at, bt, ct;

pii move_around(int src, int dst, int dstl) {
    while (src > 0 && dst < dstl) { src--, dst++; }
    return make_pair(src, dst);
}

void solve(int a, int b, int c) {

    // don't visit again
    if (mark[a][b][c] == true)
        return;

    mark[a][b][c] = true; // mark as visited

    // found solution, mark it
    if (a == 0)
        solutions[c] = true;

    // 6 possible choices for depth-first search
    tie(ct,at) = move_around(c, a, al); solve(at, b, ct); // c -> a
    tie(ct,bt) = move_around(c, b, bl); solve(a, bt, ct); // c -> b
    tie(at,bt) = move_around(a, b, bl); solve(at, bt, c); // a -> b
    tie(at,ct) = move_around(a, c, cl); solve(at, b, ct); // a -> c
    tie(bt,at) = move_around(b, a, al); solve(at, bt, c); // b -> a
    tie(bt,ct) = move_around(b, c, cl); solve(a, bt, ct); // b -> c
}

int main() {

#ifndef STDIN
    ofstream cout("milk3.out");
    ifstream cin("milk3.in");
#endif

    cin >> al >> bl >> cl;
    solve(0, 0, cl);

    // print out solutions
    for (int i = 0, c = 1; i < SIZE; i++)
        if (solutions[i] == 1) {
            if(c > 1) cout << ' ';
            cout << i;
            c++;
        }

    cout << endl;
}