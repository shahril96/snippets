/*
 ID: mohd_sh2
 LANG: C++11
 TASK: wormhole
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
using namespace std;

#define BUF 12

int N, solutions=0;
int X[BUF+1], Y[BUF+1];
int paired[BUF+1];

#define SIZE 15

// find any nearest point who is on the right (x+) of `index`
int find_right(int index) {

    int j=-1, j_val=1e9;
    int x = X[index], y = Y[index];

    for(int i=0; i<N; i++) {
        if(i == index) continue;

        if(Y[i]==y && X[i]>x && X[i]<j_val) {
            j=i, j_val=X[i];
        }
    }
    return j;
}

bool is_cycle() {

    int start;

    for(int i=0; i<N; i++) {

        // explore start from `i`
        start = i;

        // let's explore with minimum N steps
        // we can be sure that after N steps, it will restarts over again creating cycle
        for(int c=0; c<N; c++) {

            start = find_right(paired[start]);

            // -1 = that's mean the cow doesn't found any wormhole and stepping out of bound
            // return false as there's no cycle
            if(start == -1) break;
        }

        if(start != -1) return true;
    }

    return false;
}

void solve() {

    // find last point who's not paired yet
    int i;
    for(i=0; i<N; i++)
        if(paired[i] == -1)
            break;

    // if all point already paired
    if(i == N) {
        if(is_cycle() == true)
            solutions++;
        return;
    }

    for(int j=i+1; j<N; j++) {

        // if not paired yet, then pair it
        if(paired[i] == -1 && paired[j] == -1) {
            // pair the two points together
            paired[i]=j, paired[j]=i;
            // go down the tree and generate all left pairs
            solve();
            // reset for other pair with `i`
            paired[i]=paired[j]=-1;
        }
    }
}


int main() {

#ifndef STDIN
    ofstream cout("wormhole.out");
    ifstream cin("wormhole.in");
#endif

    cin >> N;
    for(int i=0; i<N; i++)
        cin >> X[i] >> Y[i];

    // set -1 as invalid value
    memset(paired, -1, sizeof(paired));

    solve();
    cout << solutions << endl;

    return 0;
}