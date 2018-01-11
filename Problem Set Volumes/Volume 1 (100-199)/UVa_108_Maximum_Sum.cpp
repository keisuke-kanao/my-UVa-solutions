
/*
	UVa 108 - Maximum Sum

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_108_Maximum_Sum.cpp

	An accepted solution.

	See Maximum subarray problem.
		(http://en.wikipedia.org/wiki/Maximum_subarray_problem)
*/

#include <iostream>
#include <algorithm>
#include <limits>
#include <cstring>
using namespace std;

const int n_max = 100;
int array_[n_max][n_max];
int sum[n_max];

int maximum_sum(int N)
{
	int max_sum = numeric_limits<int>::min();
	for (int startx = 0; startx < N; startx++) {
		memset(sum, 0, N * sizeof(int));
		for (int x = startx; x < N; x++) {
			int max_ending_here = 0, max_so_far = numeric_limits<int>::min();
			for (int y = 0; y < N; y++) {
				sum[y] += array_[x][y];
				max_ending_here = max(0, max_ending_here + sum[y]);
				max_so_far = max(max_so_far, max_ending_here);
			}
			max_sum = max(max_sum, max_so_far);
		}
	}
	return max_sum;
}

int main()
{
    int N;
	while (cin >> N) {
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

