/*
 ID: mohd_sh2
 LANG: C++11
 TASK: concom
 */

#include <bits/stdc++.h> // gcc only
using namespace std;
#define TRACE(x) cerr<<__FUNCTION__<<":"<<__LINE__<<": "#x" = "<<x<<endl;
typedef set<int> si;
typedef pair<int, int> ii;
typedef map<int, multiset<ii> > adj_list;

int main() {

#ifndef STDIN
    freopen("concom.out", "w", stdout);
    freopen("concom.in", "r", stdin);
#endif

    int n, i, j, p;
    cin >> n;

    adj_list adlist;
    si vertices;

    while(n--) {
        cin >> i >> j >> p;
        adlist[i].insert(make_pair(j,p));
        vertices.insert(i); vertices.insert(j);
    }

    for(int u : vertices) {

        /*
         * algorithm explanation :
         *
         * my algorithm is little bit same as Djikstra's shortest path,
         * except we're not looking at the shortest path, but nodes that has
         * stocks > 50 from source nodes
         *
         * so if you can't understand my solution below, try to understand
         * Djikstra's shortest path algorithm from web, you'll surely understand my solution
         * next, plus you can also learn one of famous shortest path algorithm, which is
         * killing two birds with a one stone!!
         *
         * I tried to understand another peoples brute-force algorithm, but
         * honestly can't wrap it into my head
         */

        queue<int> q;
        bool visited[105];
        int stock[105];

        memset(visited, 0, sizeof(visited));
        memset(stock, 0, sizeof(stock));

        // start first at 'node'
        visited[u]=true;
        stock[u] = 100; // set selfnode as maximum stock
        q.push(u);

        while(!q.empty()) {

            // cnode = current node
            int cnode = q.front(); q.pop();

            // loop vertices adjacent to cnode
            for(ii adj_node : adlist[cnode]) {

                int v, w;
                tie(v, w) = adj_node;

                // only add to next v node if cnode is owned by source `u`
                if(stock[cnode] > 50)
                    stock[v] += w;

                // we'll only process next `v` node if it's owned by source `u`
                if(stock[v] > 50) {
                    if(!visited[v]) {
                        q.push(v);
                        visited[v]=true;
                    }
                }
            }
        }

        // print answers after finished processing
        for(int j : vertices) {
            if(j != u && stock[j] > 50) { // only print answer if j owned by source `u`
                cout << u << ' ' << j << endl;
            }
        }
    }

    return 0;
}