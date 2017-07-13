/*
 ID: mohd_sh2
 LANG: C++11
 TASK: lamps
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;

typedef bitset<101> bit;

int N, C, t; // using 1-based index
bit final_on, final_off; // store final configuration

vector<string> store_bits;

void run_switch(bit &lamps, int option) {
    switch (option) {
    case 1:
        lamps.flip();
        break;
    case 2:
        for (int i = 1; i <= N; i += 2) lamps.flip(i);
        break;
    case 3:
        for (int i = 2; i <= N; i += 2) lamps.flip(i);
        break;
    case 4:
        for (int i = 1; i <= N; i += 3) lamps.flip(i);
        break;
    }
}

void combination(bit &lamps, int prev, int depth) {

    bit check_on  = lamps & final_on;
    bit check_off = lamps & final_off;

    if(check_on.count() == final_on.count()) // check if ON final condition mets
        if(check_off.count() == 0) { // check if OFF final condition mets

            // stores bit-set as string

            string tmp;
            for(int i=1; i<=N; i++) tmp += (lamps[i]+'0');

            if(find(store_bits.begin(), store_bits.end(), tmp) == store_bits.end())
                store_bits.push_back(tmp);
        }

    // base case
    if (depth <= 0)
        return;

    for (int i = prev + 1; i <= 4; i++) {
        run_switch(lamps, i); // do
        combination(lamps, i, depth-1); // run next combination
        run_switch(lamps, i); // undo
    }
}

int main() {

#ifndef STDIN
    freopen("lamps.out", "w", stdout);
    freopen("lamps.in", "r", stdin);
#endif

    cin >> N >> C;
    while (cin >> t, t >= 0) final_on.set(t, 1);
    while (cin >> t, t >= 0) final_off.set(t, 1);

    bit initial;
    for(int i=1; i<=N; i++) initial.set(i, 1); // set all lamps ON on initial

    // find all possible states
    C = C > 3 ? 4 : C; // there will be no solutions after 2^4
    combination(initial, 0, C);

    // store the bits
    sort(store_bits.begin(), store_bits.end(), [](const string a, const string b) -> bool {
        return a < b;
    });

    if(store_bits.empty()) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        // print all bits
        for(string each : store_bits) {
            cout << each << endl;
        }
    }

    return 0;
}