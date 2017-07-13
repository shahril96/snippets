/*
 ID: mohd_sh2
 LANG: C++11
 TASK: prefix
 */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <climits>
using namespace std;
#define trace(x) cerr<<__FUNCTION__<<":"<<__LINE__<<": "#x" = "<<x<<endl;

// primi = stores primitives
// psz = store len of number of primitives
// len_primi = stores len for each `primi`

// sequence = stores sequence string
// ssz = stores length of sequence string

// dp[] = stores processed str[start..n]

char primi[250][15], sequence[500000];
int len_primi[250], psz, ssz, dp[500000];


int solve(int start) {

    // if reached sequence limit
    if(start > ssz)
        return 0;

    if(dp[start] != 0) return dp[start];

    // store current maximum for this recursion depth
    int curr_prefix = 0;

    // get new string position
    char *ns = (char*)sequence + start;

    for(int i=0; i<psz; i++) {

        int new_start = start+len_primi[i];

        // if overflow then no proceed
        if(new_start > ssz) continue;

        // if comparison succeed, good to go
        if(!memcmp(primi[i], ns, len_primi[i])) {
            curr_prefix = max(curr_prefix, solve(new_start) + len_primi[i]);
        }
    }

    return dp[start] = curr_prefix;
}


int main() {

#ifndef STDIN
    freopen("prefix.out", "w", stdout);
    freopen("prefix.in", "r", stdin);
#endif

    // get primitive
    while(scanf("%s", primi[psz])) {
        if(primi[psz][0] == '.') break;
        len_primi[psz] = strlen(primi[psz]);
        psz++;
    }

    // get sequence
    while(scanf("%s", sequence+ssz) != EOF)
        ssz += strlen(sequence+ssz);

    printf("%d\n", solve(0));

    return 0;
}