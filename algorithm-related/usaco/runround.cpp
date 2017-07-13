/*
 ID: mohd_sh2
 LANG: C++11
 TASK: runround
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
#define trace(x) cerr<<__FUNCTION__<<":"<<__LINE__<<": "#x" = "<<x<<endl;

bool runround(uint32_t num) {

    string numstr = to_string(num);

    int i=0, c=1;
    int mark[255] = {0};
    mark[numstr[0]] = true;

    while(true) {

        i = (i + numstr[i]-'0') % numstr.length(); // wrap round in-case over limit

        if(mark[numstr[i]] == true)
            return i == 0 && c == numstr.length();
        else
            mark[numstr[i]] = true; c++;
    }
}

int main() {

#ifndef STDIN
    freopen("runround.out", "w", stdout);
    freopen("runround.in", "r", stdin);
#endif

    uint32_t N;
    cin >> N;
    N++;
    while(!runround(N)) N++;
    cout << N << endl;
    return 0;
}
