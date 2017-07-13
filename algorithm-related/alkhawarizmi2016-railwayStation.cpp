#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>

int main() {

    int N, each;

    while(cin >> N && N > 0) {

        vi input;

        for(int i = 0; ;i++) {
            cin >> each;
            if(i == 0 && each == 0) break;

            input.push_back(each);

            if(input.size() == N) {

                stack<int> s;
                int inc = 0;

                for(auto e : input) {

                    if(inc < e) {
                        for(inc++; inc <= e; inc++)
                            s.push(inc);
                        inc--;
                    }

                    if(s.top() == e) s.pop(); // if current number is on the direction B
                    else break; // invalid movement, then break from loop
                }

                cout << (s.empty() ? "Yes" : "No") << endl;

                // prepare for next input
                i = -1;
                input.clear();
            }
        }
    }
}

