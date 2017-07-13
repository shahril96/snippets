/*
 ID: mohd_sh2
 LANG: C++11
 TASK: frac1
 */

#include <iostream>
#include <fstream>
using namespace std;

// trade space for speed
int store[100001][2];

int main() {

#ifndef STDIN
    ofstream cout("frac1.out");
    ifstream cin("frac1.in");
#endif

    int N;
    cin >> N;

    for(int i=0; i<=N; i++)
        for(int j=0; j<=i; j++) {
            float calc = (float)j/i;
            if(!(calc != calc)) { // if not nan
                int indx = calc*1e5; // scale out fraction
                if(!store[indx][0] && !store[indx][1])
                    store[indx][0] = j, store[indx][1] = i;
            }
        }

    for(int i=0; i <= 1e5; i++)
        if(store[i][0] || store[i][1])
            cout << store[i][0] << '/' << store[i][1] << endl;

    return 0;
}