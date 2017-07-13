/*
 * references
 * 1) http://www.geeksforgeeks.org/greedy-algorithms-set-2-kruskals-minimum-spanning-tree-mst/
 * 2) https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class QuickUnion {
private:

    int *array; // store our disjoint-set data structure here
    int *sz; // size of tree
    int N; // number of nodes

public:

    QuickUnion(int n) {
        N = n;
        array = new int[N];
        sz = new int[N];

        for(int i = 0; i < N; i++) {
            array[i] = i; // using itself to indicate root of each tree
            sz[i] = 1; // size of each node always one at beginning
        }
    }

    ~QuickUnion() {
        delete[] array;
        delete[] sz;
    }

    // p = src
    // q = dst
    void union_add(int p, int q) {
        if(!connected(p, q)) {
            int rp = root(p);
            int rq = root(q);

            if(sz[rp] <= sz[rq]) { // doesn't matter much
                array[rp] = rq;
                sz[rq] += sz[rp]; // add previous tree size into new one
            } else if (sz[rp] > sz[rq]) {
                array[rq] = rp;
                sz[rp] += sz[rq];
            }
        }
    }

    bool connected(int p, int q) {
        return root(p) == root(q);
    }

    int root(int p) {

        while(p != array[p]) {

            // halving path by pointing to grandparent
            // path compression technique 
            p = array[p] = array[array[p]];
        }

        return p;
    }
};

typedef struct edge {
    int u;
    int v;
    int weight;
} Edge;

bool cmp(Edge a, Edge b) {
    return a.weight < b.weight; 
}

int main() {
   
    vector<Edge> c;
    vector<Edge> spanning_tree;
   
    int v;  // number of vertices
    int e;  // num of edge(s)
    cin >> v >> e;

    QuickUnion qu(v);

    for(int i = 0; i < e; i++) {
        
        Edge edge;
        cin >> edge.u >> edge.v >> edge.weight;
        c.push_back(edge);        
    }

    sort(c.begin(), c.end(), cmp);

    // min spanning tree edges is v-1
    // f < v-1 : stop when we found all v-1 edges that connected all the vertices 
    for(int f = 0, i = 0; f < v-1; i++) {
        Edge edge = c[i];
      
        // check if there's a cycle
        if(qu.connected(edge.u, edge.v)) {
            continue;
        }
       
        spanning_tree.push_back(edge);
        qu.union_add(edge.u, edge.v); 
        f++; // found one, increment node
    }

    // print all spanning tree edge(s)
    for(int i = 0; i < spanning_tree.size(); i++) {

        Edge edge = spanning_tree[i];
        cout << edge.u << ' ' << edge.v << endl;
    }

    return 0;
}
