
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef map<int, multiset<ii> > adj_list;
typedef vector<ii> vii;
typedef map<int, int> mii;

/**

Input:
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

Output:
Src to Dst : 
0 -> 0 : 0
0 -> 1 : 4
0 -> 2 : 12
0 -> 3 : 19
0 -> 4 : 28
0 -> 5 : 16
0 -> 6 : 18
0 -> 7 : 8
0 -> 8 : 14
**/

#define INF 999999

/**
 * src = source node for shortest path to all other vertices
 * adj_list (typedef of) map<int, multiset<int> > list = adjacent list 
 * V, E = number of vertices and edges in connected components
 * &dst = reference vector<int> for shortest path from src to other vertices
 * &par = reference vector<int> of an ancestor
 *        this can be recursively call to find shortest path itself
 * 
 * - return boolean to indicate either -ve cycle is detected
 *   (negative cycle indicate there is no shortest path found)
 **/
bool bellman_ford(int src, adj_list &graph, int V, int E,
                  vi &dst, vi &par) {
    
    dst[src] = 0; // except for src->src which is 0
    par[src] = -1; // starting node parent is -1
    
    // first i < V-1 is to relax edges on the graph V-1 times
    // last V-1 loop is to detect -ve cycle in the graph
    for(int i = 0; i < V; i++) {
        bool relax = false;
        for(int u = 0; u < V; u++) {
            for(auto vp : graph[u]) {
                int v = vp.first, w = vp.second;
                if(dst[u]+w < dst[v]) {
                    relax = true;
                    dst[v] = dst[u]+w;
                    par[v] = u; } } }
        
        // if there's no changes in any iteration before V-1, then
        // there will be no future changes as well, then just break
        // out from the loop
        if(i < V-1 && relax == false) break;  

        // if after V-1 iteration there is a changes, then it's a
        // negative cycle break out from the loop
        if(i >= V-1 && relax == true) return false;
    } 
    
    return true; } // in case all went well (no -ve cycle)


int main() {
    // code here
    adj_list graph;
    int V, E, u, v, w;
    cin >> V >> E;

    for(int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        graph[u].insert(make_pair(v, w)); // directed graph
    }

    int src_node = 0; // as an example
    
    // declare and initialize to INF
    vi dst(V, INF), par(V, INF);

    if(bellman_ford(0, graph, V, E, dst, par) == false) {
        cout << "Negative cycle found in graph!" << endl;
    } else {
        cout << "Src to Dst : " << endl;
        for(int i = 0; i < V; i++) {
            cout << src_node << " -> " << i << " : " << dst[i] << endl; } }

    return 0;
}
