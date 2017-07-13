/*
 ID: mohd_sh2
 LANG: C++11
 TASK: holstein
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <climits>
using namespace std;
typedef vector<int> vi;

int V, G;

struct Feed {

    int val[30];

    bool is_met_req() {
        for(int i=0; i<V; i++) if(val[i]>0) return false;
        return true;
    }

    bool operator>(Feed &b) {
        for(int i=0; i<V; i++) if(val[i]<=b.val[i]) return false;
        return true;
    }

    Feed operator-(Feed &b) {
        Feed newf;
        for(int i=0; i<V; i++) newf.val[i] = val[i] - b.val[i];
        return newf;
    }
};

Feed req, each[20];

// find minimum feeding
Feed min_feed;
vi iproc_min;

// store solved list
set<vi> computed;

// iproc = processed index
void solve(Feed leftover, vi iproc) {

    if(leftover.is_met_req()) { // if below or eq zero

        // 1) little feed number
        if(iproc.size() < iproc_min.size()) {
            min_feed = leftover;
            iproc_min = iproc;
        }

        // 2) minimum feed
        if(leftover > min_feed) {
            min_feed = leftover;
            iproc_min = iproc;
        }

        return;
    }

    // brute-force all subsets
    for(int i=0; i<G; i++) {
        if(find(iproc.begin(), iproc.end(), i) == iproc.end()) {

            vi niproc(iproc);
            niproc.push_back(i);
            sort(niproc.begin(), niproc.end());

            // if we have not yet to solve
            // essence of dynamic programming =)
            if(computed.find(niproc) == computed.end()) {
                computed.insert(niproc); // mark that we already solved this subset
                solve(leftover - each[i], niproc);
            }
        }
    }
}

int main() {

#ifndef STDIN
    freopen("holstein.out", "w", stdout);
    freopen("holstein.in", "r", stdin);
#endif

    cin >> V;
    for(int i=0; i<V; i++)
        cin >> req.val[i];

    cin >> G;
    for(int i=0; i<G; i++)
        for(int j=0; j<V; j++)
            cin >> each[i].val[j];

    // initialize min_feed
    for(int i=0; i<V; i++) min_feed.val[i] = INT_MIN;

    // recursively solve the problem
    vi leftover;
    solve(req, leftover);

    // print out answers
    cout << iproc_min.size() << ' ';
    for(int i=0; i<iproc_min.size(); i++) {
        if(i>0) cout << ' ';
        cout << iproc_min[i]+1;
    }

    cout << endl;

    return 0;
}