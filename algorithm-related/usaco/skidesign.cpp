/*
 ID: mohd_sh2
 LANG: C++11
 TASK: skidesign
 */

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
const int BUF = 1000;

int N, input[BUF + 1];

int square(int a) { return a * a; }

int main() {

#ifndef STDIN
    ofstream cout("skidesign.out");
    ifstream cin("skidesign.in");
#endif

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> input[i];

    // sort hills by ascending order
    sort(input, input + N);

    int min_total = 1e9, ctotal;

    for (int low = input[N-1]-17; low > 0; low--) {
        ctotal = 0;
        for (int i = 0; i < N; i++) {

            // checks if outside range

            if (input[i] > low+17)
                ctotal += square(input[i]-(low+17));
            if (input[i] < low)
                ctotal += square(low-input[i]);
        }

        min_total = min(min_total, ctotal); // get minimum cost
    }

    cout << min_total << endl;

    return 0;
}