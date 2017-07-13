/*
 ID: mohd_sh2
 LANG: C++11
 TASK: preface
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int count[255];

string toRoman(int num) {

    static char oneth[][5] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    static char tenth[][5] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    static char hunth[][5] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};

    string cummulate;

    while(num >= 1000) {
        cummulate += "M";
        num -= 1000;
    }

    cummulate += hunth[num / 100]; num %= 100;
    cummulate += tenth[num / 10]; num %= 10;
    cummulate += oneth[num];

    return cummulate;
}

int main() {

#ifndef STDIN
    freopen("preface.out", "w", stdout);
    freopen("preface.in", "r", stdin);
#endif

    const char list[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

    int N;
    cin >> N;

    for(int i=1; i<=N; i++) {
        string ret = toRoman(i);
        for(char c : ret) {
            count[c]++;
        }
    }

    for(int i=0; i<7; i++) {
        if(count[list[i]] > 0) {
            cout << list[i] << ' ' << count[list[i]] << endl;
        }
    }

    return 0;
}