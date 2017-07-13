/*
 ID: mohd_sh2
 LANG: C++11
 TASK: barn1
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
using namespace std;
#define BUF 200

int occu[BUF];

int main() {

#ifndef STDIN
    ofstream cout("barn1.out");
    ifstream cin("barn1.in");
#endif

    int m; // maximum number of boards that can be purchased
    int s; // total number of stalls
    int c; // number of stalls that has cow

    cin >> m >> s >> c;
    for(int i = 0; i < c; i++)
        cin >> occu[i];
    sort(occu, occu+c); // sort ascending

    multiset<int> deltas; // to store deltas
    int total_delta = 0, delta;

    for(int i = 1; i < c; i++) {
        if(occu[i]-occu[i-1] > 1) {
            total_delta += (delta = occu[i]-occu[i-1]-1);
            deltas.insert(delta); // store delta
        }
    }

    int total = c; // stalls that has cows
    int cows_block=deltas.size()+1;

    for(auto it = deltas.begin(); it != deltas.end() && cows_block > m; it++) {
        total += *it; // add stalls that don't have cows
        cows_block--; // decrement block
    }

    cout << total << endl;

    return 0;
}