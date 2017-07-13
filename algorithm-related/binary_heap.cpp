
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class heap {

    private:

        // dynamic array so we'll never
        // run out of elements :)
        vector<int> _arr;

        int parent(int i) { return i/2; }

        void heapify_up(int i) {

            // iterate until reached index 0
            while(i > 0) {
                if(_arr[parent(i)] > _arr[i]) {

                    // if parent key is higher than current key
                    // then fix it by swapping both of it
                    int tmp = _arr[parent(i)];
                    _arr[parent(i)] = _arr[i];
                    _arr[i] = tmp;
                }
                i = parent(i);
            }
        }

        void heapify_down(int i) {

            // fix bin heap structure after deletion
            while(i < _arr.size()-1) {

                int i_min = _arr[i*2] > _arr[i*2+1] ? i*2+1 : i*2;

                // continuously fix the heap tree by
                // swapping if node's childrens is lower than current node
                if(_arr[i] > _arr[i_min]) {
                    int tmp = _arr[i];
                    _arr[i] = _arr[i_min];
                    _arr[i_min] = tmp;
                }

                i = i_min;
            }

        }

    public:

        heap() {
            _arr.reserve(20);
            _arr.push_back(0);
        }


        void insert(int key) {
            _arr.push_back(key);
            heapify_up(_arr.size()-1);
        }

        int extractMin() {

            // move last key in array to root
            int tmp = _arr[1]; // store value before remove
            _arr[1] = _arr[_arr.size()-1];

            // after moved last to front, then remove that value
            _arr.pop_back();

            // fix tree heap property back
            heapify_down(1);

            return tmp;
        }

        void debug_print() {
            for(int i = 0; i <= _arr.size()-1; i++) {
                cout << _arr[i] << ' ';
            }
            cout << endl;
        }

};

int main() {

    heap h;
    h.insert(1);
    h.insert(5);
    h.insert(3);
    h.insert(10);
    h.insert(2);
    h.debug_print();
    h.extractMin();
    h.debug_print();

    return 0;
}
