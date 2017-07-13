#include <bits/stdc++.h>
using namespace std;

void first(string s) {

    cout << "..";
    
    for(int i=1; i<=s.size(); i++) {
        cout << ((i%3==0)?'*':'@');
        cout << ((i<s.size())?"...":"");
    }

    cout << ".." << endl;
}

void second(string s) {

    cout << '.';

    for(int i=1; i<=s.size(); i++)
        cout << ((i%3==0) ? "*.*." : "@.@.");

    cout << endl;
}


void third(string s) {

    cout << "@.";

    int index=0;
    bool star = false;

    for(int i=1; i<=s.size()*2-1; i++) {


        //cout << "DEBUG" << endl;
        //cout << "star = " << star << endl;
        //cout << "i = " << i << endl << endl;

        if(i%2 == 1)  cout << s[index++];
        else cout << (!star ? '@' : '*'); 

        if(i%3==0)
            star ^= 1;

        cout << '.';
    }

    cout << (s.size()%3==0 ? '*' : '@') << endl;

}

int main() {

    string in;

    while(cin >> in) {
        
        first(in);
        second(in);
        third(in);
        second(in); 
        first(in);

    }
}
