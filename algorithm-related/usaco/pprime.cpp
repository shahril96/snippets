/*
 ID: mohd_sh2
 LANG: C++11
 TASK: pprime
 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

bool primetest(int num) {
    if (num < 2) return false;
    if (num <= 3) return true;
    if (num%2 == 0 || num%3 ==0) return false;
    for (int i = 5; i*i <= num; i++)
        if (num %i ==0) return false;
    return true;
}

set<int> pprime; // stores answers

void generate(int size) {

    bool isodd = size % 2;
    int half = isodd ? (size - 1) / 2 : size / 2;
    int low = pow(10, half - 1), high = pow(10, half) - 1;
    int num;

    for (int n = low; n <= high; n++) {

        string a = to_string(n);
        string b(a);
        reverse(b.begin(), b.end());

        if (!isodd) {
            a += b;
            num = stoi(a);
            if (primetest(num))
                pprime.insert(num);
        } else {
            for (int i = 0; i < 10; i++) {
                string astr = a + to_string(i) + b;
                num = stoi(astr);
                if (primetest(num))
                    pprime.insert(num);
            }
        }
    }
}

int main() {

#ifndef STDIN
    ofstream cout("pprime.out");
    ifstream cin("pprime.in");
#endif

    int a, b;
    cin >> a >> b;

    // predefined answers
    pprime.insert(5); pprime.insert(7);

    for (int i = 1; i < 9; i++)
        generate(i); // generate prime for i digits

    for (auto n : pprime) {
        if (n > b)
            break;
        if (n >= a)
            cout << n << endl;
    }

    return 0;
}