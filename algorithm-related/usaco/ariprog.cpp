/*
 ID: mohd_sh2
 LANG: C++11
 TASK: ariprog
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int, int> pii;
bool mark[1000000];

int main() {

#ifndef STDIN
    ofstream cout("ariprog.out");
    ifstream cin("ariprog.in");
#endif

    set<int> s;
    int n,m,calc;

    cin >> n >> m;

    // pre-calculate the bi-squares
    for(int p=0; p<=m; p++)
        for(int q=0; q<=m; q++) {
            calc=p*p+q*q;
            s.insert(calc);
            mark[calc] = 1;
        }


    vector<int> v(s.begin(), s.end());
    vector<pii> res;
    res.reserve(10001); // at most 10k answers (told by the question)

    int k, diff, prev;

    // brute-forcing to find all the answers
    for(int i=0; i<v.size(); i++)
        for(int j=i+1; j<v.size(); j++) {

            diff=v[j]-v[i];
            prev=v[j]+diff;

            for(k=2; k<n; k++, prev += diff)
                if(!mark[prev]) break;

            // found a answer, insert into vector for a while
            if(k == n)
                res.push_back(make_pair(v[i], diff));

        }

    // sort the answers
    sort(res.begin(), res.end(), [](pii &a, pii &b) -> bool {
        return a.second < b.second;
    });

    if(!res.size())
        cout << "NONE" << endl;
    else
        for(auto r : res)
            cout << r.first << ' ' << r.second << endl;

    return 0;
}