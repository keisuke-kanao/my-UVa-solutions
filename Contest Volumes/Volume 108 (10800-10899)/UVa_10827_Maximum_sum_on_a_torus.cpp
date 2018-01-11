
/*
	UVa 10827 - Maximum sum on a torus

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10827_Maximum_sum_on_a_torus.cpp
*/

#include <iostream>
#include <algorithm>
#include <limits>
#include <cstring>
using namespace std;

const int n_max = 75;
int array_[n_max][n_max];
int sum[n_max];

int maximum_sum(int N)
{
	int max_sum = numeric_limits<int>::min();
	for (int startx = 0; startx < N; startx++) {
		for (int starty = 0; starty < N; starty++) {
			memset(sum, 0, N * sizeof(int));
			for (int x = startx; x < N + startx; x++) {
				int max_ending_here = 0, max_so_far = numeric_limits<int>::min();
				for (int y = starty; y < N + starty; y++) {
					sum[y % N] += array_[x % N][y % N];
					max_ending_here = max(sum[y % N] /* 0 */, max_ending_here + sum[y % N]);
					max_so_far = max(max_so_far, max_ending_here);
				}
				max_sum = max(max_sum, max_so_far);
			}
		}
	}
	return max_sum;
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
	    int N;
		cin >> N;
		int min_i = numeric_limits<int>::min();
	 	for( int i = 0; i < N; i++)
			for(int j = 0; j < N; j++) {
				cin >> array_[i][j];
				min_i = max(min_i, array_[i][j]);
			}
		cout << ((min_i < 0) ? min_i : maximum_sum(N)) << endl;
	}
	return 0;
}

