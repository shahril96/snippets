#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

ull sum[1000000];

int main() {

    ull n, q;
    int rec;
    cin >> n >> q;

    for(int i=1; i<=n; i++) {
        scanf("%d", &rec);
        sum[i] = sum[i-1] + rec;
    }

    while(q--) {
        int i,j;
        cin >> i >> j;
        cout << sum[j]-sum[i-1] << endl;
    }

    return 0;
}
