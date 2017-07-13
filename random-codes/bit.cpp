#include <bits/stdc++.h>
using namespace std;

class BIT {
	
	private:
		
		vector<int> bit;
		int n;
		
	public:
		
		BIT(int arr[], int n) {
			this->bit.reserve(n*2);
			this->bit.assign(n*2, 0);
			this->n = n;
			
			for(int i = 0; i < n; i++) {
				updateBIT(i, arr[i]);
			}
		}
		
		void updateBIT(int i, int val) {
			
			i++; // index starts from 1
			
			while(i <= n) {
				bit[i] += val;
				i += i & -i;
			}
		}
		
		int getSum(int i, int j) {
			
			i++, j++; // index starts from 1
			
			if(i == 1) {
				int sum = 0;
				while(j > 0) {
					sum += bit[j];
					j -= j & -j;
				}
				return sum;
			}
			
			return getSum(0, j-1) - getSum(0, i-2); // parameter used zero-based indexing
		}
		
		int getSum(int i) {
			return getSum(0, i);
		}
		
};

int main() {
	
	int arr[] = {1,1,1,2,1};
	int size = sizeof arr / sizeof arr[0];
	
	BIT bit(arr, size);
	cout << bit.getSum(2,3) << endl;
	
}