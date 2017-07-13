/*
 ID: mohd_sh2
 LANG: C++11
 TASK: subset
 */

#include <iostream>
#include <fstream>
#include <cstdint>
using namespace std;

uint64_t N;
uint64_t dp[40][400]; // [1..39][1..390]

int main() {

#ifndef STDIN
    freopen("subset.out", "w", stdout);
    freopen("subset.in", "r", stdin);
#endif

    cin >> N;
    uint64_t total = N*(N+1)/2;

    if(total%2 == 1) {
        cout << 0 << endl;
    } else {
        for(int n=0; n<=N; n++) {
            for(int sum=0; sum <= total/2; sum++) {
                if(sum==0)
                    dp[n][sum] = 1;
                else if(n == 0)
                    dp[n][sum] = 0;
                else
                    dp[n][sum] = dp[n-1][sum-n] + dp[n-1][sum];
            }
        }

        cout << (dp[N][total/2]) / 2 << endl;
    }

    return 0;

}
