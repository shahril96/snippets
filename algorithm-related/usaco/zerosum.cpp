/*
 ID: mohd_sh2
 LANG: C++11
 TASK: zerosum
 */

#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;
#define trace(x) cerr<<__FUNCTION__<<":"<<__LINE__<<": "#x" = "<<x<<endl;

int solve(string expr) {

    string col = "";
    char op = '+';
    int res = 0;

    for(char c : expr) {

        if(isspace(c))
            continue;

        if(!isdigit(c)) {
           switch(op) {
               case '+': res += stol(col); break;
               case '-': res -= stol(col); break;
           }
           col = "";
           op = c;
        }
        else
            col += c;
    }

    if(!col.empty()) {
        switch(op) {
           case '+': res += stol(col); break;
           case '-': res -= stol(col); break;
       }
    }

    return res;
}

int N;
vector<string> ans;

void generate_comb(int num, string expr) {

    if(num > N) {
        if(solve(expr) == 0)
            ans.push_back(expr);
            //cout << expr << endl;
        return;
    }

    generate_comb(num+1, expr+string("+")+to_string(num));
    generate_comb(num+1, expr+string("-")+to_string(num));
    generate_comb(num+1, expr+string(" ")+to_string(num));
}

int main() {

#ifndef STDIN
    freopen("zerosum.out", "w", stdout);
    freopen("zerosum.in", "r", stdin);
#endif

    cin >> N;
    generate_comb(2, string("1"));

    sort(ans.begin(), ans.end());

    for(string each : ans) {
        cout << each << endl;
    }

    return 0;
}
