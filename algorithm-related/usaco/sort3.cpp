/*
 ID: mohd_sh2
 LANG: C++11
 TASK: sort3
 */

#include <iostream>
#include <fstream>
using namespace std;

int N, arr[1050];
int freq[4];

int get_low(int i) {
    if(i>3) return N;
    int low=0;
    for(int j=0; j <= i-1; j++) low += freq[j];
    return low;
}

int swap(int i, int j) {
    int tmp=arr[i];
    arr[i]=arr[j];
    arr[j]=tmp;
}

int selection_sort() {

    int writes = 0;

    // find frequency
    for(int i=0; i<N; i++)
        freq[arr[i]]++;

    for(int i=1; i<=3; i++) {
        for(int j=i+1; j<=3; j++) {

            // do 1-2, 1-3, 2-3

            int jf = get_low(j);
            for(int l=get_low(i); l < get_low(i+1) && jf < get_low(j+1); l++) {

                // find j in `i` segment
                while(l < get_low(i+1) && arr[l] != j) l++;

                // find i in `j` segment
                while(jf < get_low(j+1) && arr[jf] != i) jf++;

                // if out of range
                if(l >= get_low(i+1) || jf >= get_low(j+1)) continue;

                swap(l, jf);
                writes++;
            }

        }

        // find the leftover and finish the job

        int jf = get_low(i+1);
        for(int l=get_low(i); l < get_low(i+1) && jf < N; l++) {

            // find first non `i` in `i` segment
            while(l < get_low(i+1) && arr[l] == i) l++;

            // find i in get_low(i+1) .. N segment
            while(jf < N && arr[jf] != i) jf++;

            // if out of range
            if(l >= get_low(i+1) || jf >= N) continue;

            swap(l, jf);
            writes++;
        }
    }

    return writes;
}

int main() {

#ifndef STDIN
    ofstream cout("sort3.out");
    ifstream cin("sort3.in");
#endif

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    cout << selection_sort() << endl;

}