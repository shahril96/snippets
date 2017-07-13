#include <bits/stdc++.h>
using namespace std;

int main() {

    int a, b, c;
    cin >> a >> b >> c;

    for(int i=1; i<=a; i++) {

        if(i%b == 0 && i%c == 0) {
            cout << i << endl;
        }
        else if(i%b == 0) {
            cout << "Baa" << endl;
        }
        else if(i%c == 0) {
            cout << "Caa" << endl;
        }
        else 
            cout << i << endl;
    }


    return 0;
}
