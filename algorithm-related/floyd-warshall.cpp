#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef map<int, multiset<ii> > adj_list;
typedef vector<ii> vii;
typedef map<int, int> mii;
const int INF = 9999999;

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
0 -> 0 = 0
0 -> 1 = 4
0 -> 2 = 12
0 -> 3 = 19
0 -> 4 = 21
0 -> 5 = 11
0 -> 6 = 9
0 -> 7 = 8
0 -> 8 = 14

**/

const int n = 400; // 400 is the max vertices for floyd-warshall
                   // 400^3 = 6++ millions operations

/**
 * AdjMat = 2D array representing the u->v = w
 * par = 2D array representing parent of [i][j], can be recursively
 *       called until we meet the source i=j to print the path of
 *       src->dst
 * int V = number of vertices inside connected graph
 *
 * this function will modifies AdjMat that will contains shortest path from
 * all pair of u->v inside graph
 **/
void floyd_warshall(int AdjMat[][n], int par[][n], int V) {
    for(int k = 0; k < V; k++)
        for(int i = 0; i < V; i++) 
            for(int j = 0; j < V; j++) 
                if(AdjMat[i][k]+AdjMat[k][j] < AdjMat[i][j]) {
                    AdjMat[i][j] = AdjMat[i][k]+AdjMat[k][j];
                    par[i][j] = par[k][j]; // update parent
                } }

int main() {

    int AdjMat[n][n], par[n][n];
    int V,E,u,v,w;
    cin >> V >> E;

    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            AdjMat[i][j] = INF;
            par[i][j] = i; }
        AdjMat[i][i] = 0; }

    for(int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        AdjMat[u][v] = w; // directed graph
    }

    floyd_warshall(AdjMat, par, V);

    for(int j = 0; j < V; j++) {
        if(AdjMat[0][j] != INF) {
            cout << "0 -> " << j << " = " << AdjMat[0][j] << endl; } }
    
    return 0; }
