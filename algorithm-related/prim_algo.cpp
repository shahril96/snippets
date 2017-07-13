/*
 * references
 * 
 * 1) http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
 * 2) https://www.cse.ust.hk/~dekai/271/notes/L07/L07.pdf
 * 
 */

#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <utility>
#include <climits>
using namespace std;

int main() {

    int V, E;
    cin >> V >> E;

    set<int> vertices;
    map<int, vector<pair<int,int> > > edges;

    for(int i = 0; i < E; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        edges[v].push_back(make_pair(u,w));
        edges[u].push_back(make_pair(v,w));
        vertices.insert(v);
        vertices.insert(u);
    }

    // all input
    // ready for an action!

    // S = included vertices
    set<int> S;

    // Q = not yet included vertices
    set<int> Q(vertices);

    // adjacent vertex -> pair(src vertex, weight)
    // to store min weight for edge with adj vertex's of included vertices
    map<int, pair<int,int> > cost;

    // adjacent vertex -> pair(src vertex, weight)
    // to store MST's edges
    map<int, pair<int,int> > mst;

    // init all initial cost to maximum value
    for(auto q : Q) {
        cost[q] = make_pair(NULL, INT_MAX);
    }

    // set vertex '0' as a starting node
    S.insert(0);
    Q.erase(Q.find(0));

    while(Q.size() > 0) {

        //
        // set minimum cost for all vertices adjacent to already-included vertices
        //
        
        for(auto i : S) {
            for(auto edge : edges[i]) {

                // i = v
                // edge.first = u
                // edge.second = w

                // no need to set cost to already included vertices
                if(S.find(edge.first) == S.end()) {  
                                                    
                    // find minimum edge's weight that connected to adjacent vertex
                    // then set it into cost's map
                    if(edge.second < cost[edge.first].second) {
                        cost[edge.first] = make_pair(i, edge.second);
                    }
                }
            }
        }

        //
        // find not-yet adjacent vertices that contains minimum weight
        //
        
        pair<int,int> mincost_vertex = make_pair(NULL, INT_MAX);
        int adj_vertex = -1; // store adjacent vertex that contains minimum weight

        for(auto each_cost : cost) {

            // no need find already included MST vertex
            if(S.find(each_cost.first) == S.end()) {

                // find adjacent vertex that contains minimum weight
                if(each_cost.second.second < mincost_vertex.second) {
                    mincost_vertex = each_cost.second; 
                    adj_vertex = each_cost.first;
                }
            }
        }

        // store new included MST's vertices for later print-out
        mst[adj_vertex] = mincost_vertex;

        // add choosen adjacent vertex into already included vertices list
        S.insert(adj_vertex);

        // remove choosen adjacent vertex from remaining vertices list
        Q.erase(Q.find(adj_vertex));
    }

    // print out MST
    
    cout << "Edge  Weight\n" << endl;

    for(auto result : mst) {

        int u = result.second.first;
        int v = result.first;
        int w = result.second.second;

        cout << u << '-' << v << '\t' << w << endl;
    }

    return 0;
}
