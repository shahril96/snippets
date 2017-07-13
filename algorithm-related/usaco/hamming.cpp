/*
 ID: mohd_sh2
 LANG: C++11
 TASK: hamming
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;
typedef vector<int> vi;

int N, B, D;

int hamming_distance(int a, int b) {
    int t=0;
    a ^= b;
    for(int i=0; i<B; i++)
        if(a & (1 << i))
            t++;
    return t;
}

bool found = false;

void solve(vi &curr, int depth) {

    // base case
    if(depth==1) {
        found = true;
        return;
    }

    for(int i=curr.back()+1; i<=pow(2,B); i++) {

        // filter out non-hamming distance
        bool skip=false;
        for(auto n : curr) {
            if(hamming_distance(i, n) < D) {
                skip=true;
                break;
            }
        }

        if(skip) continue;

        curr.push_back(i);

        solve(curr, depth-1);
        if(found) return;

        curr.pop_back();
    }
}

int main() {

#ifndef STDIN
    freopen("hamming.out", "w", stdout);
    freopen("hamming.in", "r", stdin);
#endif

    cin >> N >> B >> D;
    vi start = {0}; // first answer always 0
    solve(start, N);

    for(int i=0; i<start.size(); i++) {
        if(i > 0 && i%10 == 0) cout << endl;
        else if(i>0) cout << ' ';
        cout << start[i];
    }

    cout << endl;

    return 0;
}