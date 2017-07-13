/* References :
   http://www.geeksforgeeks.org/dynamic-programming-set-3-longest-increasing-subsequence/
   https://www.youtube.com/watch?v=4fQJGoeW5VE */
   

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int lis(vector<int> &A)
{
    vector<vector<int> > L{A.size()};

    int max = 1;

    L[0].push_back(A[0]);

    for(int i = 1; i < A.size(); i++)
    {
        for(int j = 0; j < i; j++)
            if(A[j] < A[i] && L[j].size() > L[i].size())
                L[i] = L[j];

        L[i].push_back(A[i]);
    }

    for(auto x: L)
    {
        max = std::max(max, (int)x.size());

        for(auto b: x)
            cout << b << " ";

        cout << endl;
    }

    return max;
}

int main()
{
    vector<int> A = {1, -3, -2, 5, -6, 7, 10, -16};
    cout << "\n lis -> " << lis(A) << endl;
}
