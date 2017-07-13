/*
 ID: mohd_sh2
 LANG: C++11
 TASK: castle
 */

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

struct Module {

    // inside what room?
    int room_num;

    int room_size;

    // wall boolean [N,E,S,W]
    bool w[4];

    // border with whom? [N,E,S,W]
    // if -1 = border with out of bound
    // if  0 = not assigned yet
    int b[4];
};

// [N,E,S,W][i=0,j=1]
int move_ij[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};

// [i][j], 1-based index
Module mod[55][55];

int M,N, wallNum;

void decodeNum(int i, int j, int wallNum) {

    while(wallNum > 0) {
        int curn = 1;

        if(wallNum >= 8) curn=8;
        else if(wallNum >= 4) curn=4;
        else if(wallNum >= 2) curn=2;

        switch (curn) {
            case 1: mod[i][j].w[3]=true; break;
            case 2: mod[i][j].w[0]=true; break;
            case 4: mod[i][j].w[1]=true; break;
            case 8: mod[i][j].w[2]=true; break;
        }
        wallNum -= curn;
    }
}

// i,j = location to start the flood
// num = what number to give for this room
int flood_fill(int i, int j, int num) {

    // already processed (base case)
    if(mod[i][j].room_num != 0) return 0;

    // mark this module belong to `num` room
    mod[i][j].room_num=num;

    int t=1, ii, jj;
    for(int l=0; l<4; l++) {

        ii = i + move_ij[l][0];
        jj = j + move_ij[l][1];

        if(ii >= 1 && ii <= N && jj >= 1 && jj <= M) { // check if out of bound

            bool has_obstacle = mod[i][j].w[l];

             //printf("i=%d, j=%d, ii=%d, jj=%d, obstacle=%d, num=%d\n",
             //          i, j, ii, jj, has_obstacle, num);

            if(has_obstacle == true) {
                if(mod[ii][jj].room_num > 0) {
                    mod[i][j].b[l] = mod[ii][jj].room_num; // take opposite and save to curr
                    mod[ii][jj].b[(l+2)%4] = mod[i][j].room_num; // take curr and save to opposite
                }
            } else {
                // if no obstacle than this must be in the same room
                mod[i][j].b[l]=num;
                mod[ii][jj].b[(l+2)%4]=num;

                // flood into another module
                t += flood_fill(ii, jj, num);
            }
        } else {
            mod[i][j].b[l] = -1; // -1 = out of bound
        }
    }

    return t;
}

int main() {

#ifndef STDIN
    ofstream cout("castle.out");
    ifstream cin("castle.in");
#endif

    cin >> M >> N;

    // using 1-based index
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            cin >> wallNum;
            decodeNum(i, j, wallNum);

            //printf("(%d,%d) -> n=%d, e=%d, s=%d, w=%d\n", i, j,
            //         mod[i][j].w[0], mod[i][j].w[1], mod[i][j].w[2], mod[i][j].w[3]);
        }
    }

    // begin flood fill
    int num_room=1, rtotal;
    int larg_room=-1e9;

    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            rtotal = flood_fill(i, j, num_room);

            // get max size of rooms
            larg_room = max(larg_room, rtotal);

            if(rtotal > 0) {

                // assign total to every module in the same room
                for(int ii=1; ii<=N; ii++) {
                    for(int jj=1; jj<=M; jj++) {
                        if(mod[ii][jj].room_num == num_room) {
                            mod[ii][jj].room_size = rtotal;
                        }
                    }
                }

                num_room++;
            }
        }
    }

    // get real number of room
    num_room--;

    // find the largest room & its border
    int it=N, jt=M; // first
    int iit=N, jjt=M; // second
    int ii=N, jj=M, val=0, cval; // tmp
    int total_ij=N*M, ij;

    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            for(int l=0; l<4; l++) { // loop every border

                if(mod[i][j].b[l] > 0 && mod[i][j].b[l] != mod[i][j].room_num) {

                    ii = i + move_ij[l][0];
                    jj = j + move_ij[l][1];

                    cval = mod[i][j].room_size + mod[ii][jj].room_size;
                    ij = (N-i)+j;

                    //printf("cval=%d, val=%d, i=%d, j=%d, ii=%d, jj=%d, it = %d, jt = %d\n",
                    //                                cval, val, i, j, ii, jj, it, jt);

                    if(cval > val || (cval == val && ij < total_ij)) {
                        it = i, jt = j;
                        iit = ii, jjt = jj;
                        val = cval;
                        total_ij = ij; // priority south & west
                    }
                }
            }
        }
    }

    // print the answers
    cout << num_room << endl;
    cout << larg_room << endl;
    cout << val << endl;

    if(it != iit && jt == jjt)
        cout << max(it, iit) << ' ' << jt << " N" << endl;
    else if (it == iit && jt != jjt)
        cout << it << ' ' << min(jt, jjt) << " E" << endl;

    return 0;
}
