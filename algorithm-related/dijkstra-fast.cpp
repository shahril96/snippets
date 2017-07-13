
/*
 
Input :

9 14
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 8 2
2 5 4
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7

Output : 

0 -> 0 : 0
0 -> 1 : 4
0 -> 2 : 12
0 -> 3 : 19
0 -> 4 : 21
0 -> 5 : 11
0 -> 6 : 9
0 -> 7 : 8
0 -> 8 : 14

*/

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef map<int, multiset<ii> > adj_list;
typedef vector<ii> vii;
typedef map<int, int> mii;

// adj_list (typedef of) map<int, multiset<int> > list = adjacent list
// set<int> V = list of connected vertices with src
// int src = node to start first
// return mii -> key = dst, value = shortest path from src to dst
// complexity = O(E log V)
mii dijkstra(adj_list &list, set<int> &V, int src) {

    mii dst; for(int v : V) dst[v] = 1e9;
    dst[src] = 0; // src to src distance is always zero

    priority_queue<ii, vii, greater<ii> > min_q;
    min_q.push(make_pair(0, src)); // (priority, vertex)

    while(!min_q.empty()) {
        int u = min_q.top().second; min_q.pop();

        for(auto x : list[u]) {
            int v = x.first, w = x.second;

            // check if there's any shortest path from U -> V
            if(dst[u]+w < dst[v]) {
                dst[v] = dst[u]+w;
                min_q.push(make_pair(dst[v], v)); }}}

    return dst;
}

int main() {

    // V = number of vertices, e = number of edges
    int V, E;
    cin >> V >> E;

    adj_list list;
    set<int> vertices;

    while(E --> 0) {
        int u, v, w;
        cin >> u >> v >> w;

        // get all vertices
        vertices.insert(u); vertices.insert(v);
        
        // if set hasn't been created yet
        if(!list.count(u)) { 
            multiset<ii> si;
            list[u] = si; }
        
        // undirected graph
        if(!list.count(v)) {
            multiset<ii> si;
            list[v] = si; }

        list[u].insert(make_pair(v, w));
        list[v].insert(make_pair(u, w)); }

    // get random src point
    int src = (*(list.begin())).first;

    mii ret = dijkstra(list, vertices, src);

    for(auto x : ret) {
        cout << src << " -> " << x.first << " : " << x.second << endl; }

    return 0; }
