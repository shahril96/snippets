#include <bits/stdc++.h>
using namespace std;

int main() {

    map<string, int> count;
    string s;

    while(cin >> s)
        count[s]++;

    map<int, vector<string> > result;

    for(auto it = count.rbegin(); it != count.rend(); it++) {
        string word;
        int count;
        tie(word, count) = *it;
        result[count].push_back(word);
    }

    int i=0;
    for(auto it = result.rbegin(); it != result.rend() && i < 5; it++) {

        vector<string> ll((*it).second.begin(), (*it).second.end());
        sort(ll.begin(), ll.end());

        for(string ss : ll) {
            if(i >= 5) break;
            cout << ss << ' ' << (*it).first << endl; 
            i++;
        }
    }
 
    
    return 0;
}
