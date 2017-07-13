/*
 ID: mohd_sh2
 LANG: C++11
 TASK: milk
 */

#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
using namespace std;

struct Farmer {
    int p; // price in cents that farmer i charges
    int a; // amount of milk that farmer i can sell to Merry Milk Makers per day
};

Farmer farmer[5000];

int main() {

#ifndef STDIN
    ofstream cout("milk.out");
    ifstream cin("milk.in");
#endif

    // n =  amount of milk that Merry Milk Makers wants per day
    // m = number of farmers that they may buy from
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; i++)
        cin >> farmer[i].p >> farmer[i].a;

    // sort ascending order based on `price in cents`
    sort(farmer, farmer+m, [](const Farmer &a, const Farmer &b) -> bool {
        return a.p < b.p;
    });

    int total=0, atb;
    for(int i = 0; i < m && n > 0; i++) {
        // amount to buy
        atb = n >= farmer[i].a ? farmer[i].a : n;
        total += atb * farmer[i].p;
        n -= atb;
    }

    cout << total << endl;

    return 0;
}