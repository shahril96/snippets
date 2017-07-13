
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
  
class segmentTree {

    private:

        vector<int> st, arr;
        int size;

        int nextLeft(int i) { return i*2; }
        int nextRight(int i) { return i*2 +1; }

        void build(int s, int e, int i) {
            
            if(s == e) {
                st[i] = e;
                return;
            }

            int m = (s+e)/2;
            int l = nextLeft(i), r = nextRight(i);
            build(s, m, l);
            build(m+1, e, r);

            // build min segment tree
            st[i] = arr[st[l]] <= arr[st[r]] ? st[l] : st[r];
        }

        int rmq(int i, int j, int index, int s, int e) {
            
            if(i > e || j < s) return -1;
            if(s >= i && e <= j) return st[index];

            int m = (s+e)/2;
            int left = rmq(i, j, nextLeft(index), s, m);
            int right = rmq(i, j, nextRight(index), m+1, e);
           
            if(left == -1) return right;
            if(right == -1) return left;

            return arr[left] <= arr[right] ? left : right;
            
        }

    public:

        segmentTree(int array[], int n) {

            size = n;
            st.assign(n*4, 0);

            arr.reserve(n+1);
            for(int i = 0; i < n; i++) {
                arr[i] = array[i];
            }

            build(0, n-1, 1);
        }

        int rmq(int i, int j) {
            return rmq(i, j, 1, 0, size-1);
        }

};

int main() {

    int arr[] = {3, 1, -1, 4, 10, 3, 15};
    segmentTree st(arr, sizeof arr / sizeof arr[0]);
    cout << st.rmq(1, 2) << endl;
    return 0;

}

