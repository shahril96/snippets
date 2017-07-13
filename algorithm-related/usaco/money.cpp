/*
 ID: mohd_sh2
 LANG: C++11
 TASK: money
 */

#include <iostream>
#include <fstream>
using namespace std;
#define trace(x) cerr<<__FUNCTION__<<":"<<__LINE__<<": "#x" = "<<x<<endl;
typedef long long ll;

ll dp[30][10005];

int main() {

#ifndef STDIN
    freopen("money.out", "w", stdout);
    freopen("money.in", "r", stdin);
#endif

    int V, N;
    ll coins[30];

    cin >> V >> N;
    for(int i=1; i<=V; i++)
        cin >> coins[i];

    for(int i=1; i<=V; i++) {
        for(int j=0; j<=N; j++) {
            if(j==0) dp[i][j]=1;
            else if(j-coins[i] < 0) dp[i][j] = dp[i-1][j];
            else dp[i][j] = dp[i-1][j] + dp[i][j-coins[i]];
        }
    }

    cout << dp[V][N] << endl;

    return 0;
}