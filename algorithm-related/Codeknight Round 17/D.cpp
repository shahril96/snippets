#include <bits/stdc++.h>
using namespace std;

int main() {

    int N, e;
    
    for(int i=1; cin >> N && N > 0; i++) {

        vector<int> books;
        int sum=0,avg;

        for(int i=0; i<N; i++) {
            cin >> e;
            sum += e;
            books.push_back(e);
        }

        avg = sum/N;

        int move=0;

        for(int i=0; i<N; i++) {
            if(books[i] > avg) {
                move += (books[i]-avg);
            }
        }

        cout << "Set " << i << " : " << move << endl;

    }

    return 0;
}

