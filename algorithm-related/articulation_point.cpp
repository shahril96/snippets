#include <bits/stdc++.h>
using namespace std;

/**

Input :
7 8
0 1 1
1 2 1
2 0 1
1 3 1
1 4 1
1 6 1
3 5 1
4 5 1
Output :
List of all articulation points : 
1

Input : 
4 4
1 2 1
2 3 1
4 3 1
4 2 1
Output :
List of all articulation points : 
2

**/

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef map<int, multiset<ii> > adj_list;
typedef vector<ii> vii;
typedef map<int, int> mii;

map<int, set<ii > > graph;
mii dfs_low, dfs_num, parent;
map<int, bool> ap;
set<int> vertices, visited;

void articulation_p(int u) {
    static int time = 0;
    int child = 0; // count number of childs in DFS tree (not normal tree)

    visited.insert(u);
    dfs_low[u] = dfs_num[u] = ++time;

    for(ii vp : graph[u]) {
        int v = vp.first;

        // if forward-edge
        if(visited.find(v) == visited.end()) {
           
            child++; // count number of unvisited child with parent of `u`
            parent[v] = u;
            articulation_p(v);

            // check if subtree rooted with `v` (child of `u`)
            // have dfs_low lower than dfs_low of `u`
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);

            // find articulation for below 2 cases
            
            // 1) if `u` is root and has more than one childs in DFS tree
            if(parent[u] == -1 && child > 1)
                ap[u] = true;
           
            // 2) if `u` is not root, and dfs_low time of its child
            //    is more than or eq to the discovery time of itself
            if(parent[u] != -1 && dfs_low[v] >= dfs_num[u]) 
                ap[u] = true;
        
        // if back-edge
        // v != parent[u] is to ignore back-edge to the parent node (undirected node)
        } else if (v != parent[u]) 
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
    }
}

int main() { 

    int v, e;
    cin >> v >> e;

    while(e --> 0) {

        int u, v, w;
        cin >> u >> v >> w;

        vertices.insert(u); vertices.insert(v);

        graph[u].insert(make_pair(v, w));
        graph[v].insert(make_pair(u, w));
    }

   // find all articulation point on all connected components
    for(int i = 0; i < vertices.size(); i++) {
        if(visited.find(i) == visited.end()) {
            parent[i] = -1;
            articulation_p(i);
        }
    }

    cout << "List of all articulation points : \n";

    for(int i = 0; i < vertices.size(); i++) {
        if(ap[i] == true) {
            cout << i << endl;
        }
    }

}
