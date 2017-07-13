/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * Author: shahril
 *
 * Created on January 22, 2016, 5:21 PM
 */

#include <iostream>
#include <sstream>
#include <random>

class QuickUnion {
private:

    int *array;
    int *sz; // size of tree
    int N;

public:

    QuickUnion(int n, int row_size) {
        N = n;
        array = new int[N];
        sz = new int[N];

        for(int i = 0; i < N; i++) {
            array[i] = i;
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
            // flattening the tree way up
            p = array[p] = array[array[p]];
        }

        return p;
    }

    // prototype
    friend std::ostream &operator<< (std::ostream &out, QuickUnion &obj);
};

std::ostream &operator<< (std::ostream &out, QuickUnion &obj) {

    for(int i = 0; i < obj.N; i++) {
        out << "[" << i << "] " << obj.array[i] << std::endl;
    }

    return out;
}

void connect(QuickUnion &qu, int *exist,
             int loc, int pos, int row_size,
             int table_size) {

    // if loc is already bolded & have connection
    // then connect them
    if(exist[pos] != 0) {
        qu.union_add(loc, pos);

        // connect to virtual top
        if(pos <= row_size) {
            qu.union_add(pos, 0);
        }

        // connect to virtual bottom
        if(pos >= table_size-2 - row_size) {
            qu.union_add(pos, table_size-1);
        }
    }
}

int main() {

    // how many times to run simulation
    int simulation = 10;
    int row_size = 10000;
    int table_size = row_size * row_size + 2;

    // for generating high quality random num
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, table_size - 2);

    double avg = 0;

    for(int i = 0; i < simulation; i++)
    {
        // +2 because we create two virtual sites for top & bottom
        QuickUnion qu(table_size, row_size);

        // heap value always init all with zeroes
        // () tu guna nk call constructor, yakni init suma jadi zero
        int *exist = new int[table_size](); // with virtual location

        // counter any bolded site
        int count = 0;

        // check if virtual site is not connected
        while(!qu.connected(0, table_size-1)) {

            int loc;

            // generate random unique loc coordinate
            // code mainly bottleneck kt sini
            while(true) {
                loc = dis(gen);
                if(exist[loc] == 0) {
                    exist[loc] = 1; // mark as bolded down
                    break;
                }
            }

            // check upper
            if(loc-row_size > 0) {
                connect(qu, exist, loc, loc-row_size,
                        row_size, table_size);
            }

            // check lower
            if(loc+row_size < table_size-1) {
                connect(qu, exist, loc, loc+row_size,
                        row_size, table_size);
            }

            // check left
            if(loc-1 % row_size != 0) {
                connect(qu, exist, loc, loc-1,
                        row_size, table_size);
            }

            // check right
            if(loc % row_size != 0) {
                connect(qu, exist, loc, loc+1,
                        row_size, table_size);
            }

            count++;
        }

        std::cout << std::endl << " Threshold for " << i+1 << " : "
                  << (double)count / (table_size-2);

        avg += (double)count / (table_size-2);

        delete[] exist;
    }

    std::cout << std::endl << " Average overall percolate threshold : "
              << avg / simulation << std::endl << std::endl;
}
