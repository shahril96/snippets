/*
 * references
 *
 * 1) http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
 * 2) http://home.cse.ust.hk/faculty/golin/COMP271Sp03/Notes/MyL09.pdf
 * 
 */

#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <utility>
#include <climits>
using namespace std;

struct Info {
    int weight;
    vector<int> vertices;
};

int main() {

    int V, E;
    int src, dst;
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

    map<int, Info> cost;

    for(auto v : vertices) {
        Info info;
        info.weight = INT_MAX;
        cost[v] = info;
    }

    S.insert(0);
    Q.erase(Q.find(0));
    cost[0].weight = 0;

    // process while remaining set isn't empty
    while(Q.size() > 0) {

        // find cost for all included vertices's adjacences
        for(auto s : S) {
            for(auto e : edges[s]) {

                // s = v
                // e.first = u
                // e.second = w

                // ignore if adjacent vertex is already
                // inside included set
                if(S.find(e.first) == S.end()) {

                    int total_cost = cost[s].weight + e.second;

                    if(total_cost < cost[e.first].weight) {
                        cost[e.first].weight = total_cost;

                        // copy vector of vertices to reach `u`
                        cost[e.first].vertices = cost[s].vertices;
                        cost[e.first].vertices.push_back(s);
                    }
                }
            }
        }

        int min_index = INT_MAX;
        int min_cost = INT_MAX;

        // find min cost for all adjacences
        for(auto c : cost) {

            // ignore vertex that already inside included set
            if(S.find(c.first) == S.end()) {
                if(c.second.weight < min_cost) {
                    min_index = c.first;
                    min_cost = c.second.weight;
                }
            }
        }

        // found vertex with minimum cost
        // insert into already included set
        // delete from remaining set
        S.insert(min_index);
        Q.erase(Q.find(min_index));
    }

    cout << "\n Node->Node\tPath\t\t\tWeight\n\n";

    for(int i = 0; i < V; i++) {
        cout << ' ' << 0 << " -> " << i << "\t\t";
        for(auto v : cost[i].vertices) {
            cout << v << ' ';
        }
        cout << i << "\t\t\t" << cost[i].weight << endl;
    }

    return 0;
}
