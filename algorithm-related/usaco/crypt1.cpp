/*
 ID: mohd_sh2
 LANG: C++11
 TASK: crypt1
 */

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <set>
using namespace std;

// set that allows redundancy
multiset<int> nzero;

bool is_in_set(int num, int checklen) {

    int mark=0, len=0, n;
    while(num > 0) {
        n = num%10;
        num/=10;
        len++;
        if(nzero.find(n) != nzero.end())
            mark++; // if found
    }

    return len == checklen && mark == len;
}

// to store all numbers
char buf[10];

int recurse_num(int i, int level) {

    if(level == 0) {

        int upnum, lownum;
        sscanf(buf, "%3d%2d", &upnum, &lownum);

        // if number in the set
        return is_in_set(upnum*lownum, 4) && is_in_set(upnum*(buf[4]-'0'), 3)
                && is_in_set(upnum*(buf[3]-'0'), 3);
    }

    int t=0;
    for(int n : nzero) {
        buf[i] = '0' + n;
        t += recurse_num(i+1, level-1);
    }
    return t;
}

int main() {

#ifndef STDIN
    ofstream cout("crypt1.out");
    ifstream cin("crypt1.in");
#endif

    int in, n;

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> in;
        nzero.insert(in);
    }

    cout << recurse_num(0, 5) << endl;

    return 0;
}