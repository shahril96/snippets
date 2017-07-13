/*
 ID: mohd_sh2
 LANG: C++11
 TASK: namenum
 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;

const char touchkey[10][4] = {
    "", "", // index 0 & 1 (nothing)
    "ABC", // 2
    "DEF", // 3
    "GHI", // 4
    "JKL", // 5
    "MNO", // 6
    "PRS", // 7
    "TUV", // 8
    "WXY"  // 9
};

string digits;
set<string> dict;
char buf_store[100];

int recursive_name(const char *digitleft, int index, ostream &cout) {

    // base case when there's no character to recurse
    if (*digitleft == '\0') {

        // print out the answer
        if (dict.find(string(buf_store)) != dict.end()) {
            cout << buf_store << endl;
            return 1;
        }
        return 0;
    }

    // there are character(s) left, then recurse more deeply
    int digit_int = digitleft[0] - '0';
    int c=0; // how many answers node below found
    for (int i = 0; i < 3; i++) {
        buf_store[index] = touchkey[digit_int][i];
        c += recursive_name(digitleft + 1, index + 1, cout);
    }

    return c;
}

int main() {

    /**
     * below is a required file for this program
     * make sure it's on the same folder as the compiled program
     *
     * http://train.usaco.org/usaco/namenumdict.txt
     *
     * save it as "dict.txt"
     */

#ifndef STDIN
    ifstream cin("namenum.in");
    ofstream cout("namenum.out");
#endif

    // read all into RB tree
    ifstream dictif("dict.txt");
    string dict_line;
    while (dictif >> dict_line)
        dict.insert(dict_line);

    getline(cin, digits);

    if(recursive_name(digits.c_str(), 0, cout) == 0)
        cout << "NONE" << endl;

    return 0;
}