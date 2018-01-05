
/*
	UVa 10913 - Walking on a Grid

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10913_Walking_on_a_Grid.cpp
*/

#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

const int infinite = numeric_limits<int>::min();
const int N_max = 75, k_max = 5;
int grid[N_max][N_max];
int paths[N_max][N_max][k_max + 1];
	// paths[i][j][k] is the max. sum of integers to square (i, j) with k negative integers, 
	// or infinite if it is impossible to reach the square
int paths_from_left[N_max][k_max + 1], paths_from_right[N_max][k_max + 1];

#ifdef DEBUG

void print_paths(int N, int k, int r)
{
	for (int c = 0; c < N; c++) {
		cout << '[';
		for (int i = 0; i <= k; i++)
			cout << paths[r][c][i] << ((i < k) ? " " : "] ");
	}
	cout << endl;
}

void print_paths(int N, int k, int p[N_max][k_max + 1])
{
	for (int c = 0; c < N; c++) {
		cout << '[';
		for (int i = 0; i <= k; i++)
			cout << p[c][i] << ((i < k) ? " " : "] ");
	}
	cout << endl;
}

#endif

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int N, k;
		cin >> N >> k;
		if (!N && !k)
			break;
		for (int r = 0; r < N; r++)
			for (int c = 0; c < N; c++) {
				cin >> grid[r][c];
				for (int i = 0; i <= k; i++)
					paths[r][c][i] = infinite;
			}

		for (int i = 0, j = (grid[0][0] < 0) ? 1 : 0; i + j <= k; i++)
			paths[0][0][i + j] = grid[0][0];
		for (int c = 1; c < N; c++) // the first row
			for (int i = 0, j = (grid[0][c] < 0) ? 1 : 0; i + j <= k; i++)
				if (paths[0][c - 1][i] != infinite)
					paths[0][c][i + j] = paths[0][c - 1][i] + grid[0][c];
#ifdef DEBUG
		print_paths(N, k, 0);
#endif
		for (int r = 1; r < N; r++) { // between the second and the next to last row
			for (int c = 0; c < N; c++)
				for (int i = 0; i <= k; i++)
					paths_from_left[c][i] = paths_from_right[c][i] = infinite;
			for (int c = 0; c < N; c++)
				for (int i = 0, j = (grid[r][c] < 0) ? 1 : 0; i + j <= k; i++) {
					int p = infinite;
					if (r)
						p = max(p, paths[r - 1][c][i]);
					if (c)
						p = max(p, paths_from_left[c - 1][i]);
					if (p != infinite)
						paths_from_left[c][i + j] = p + grid[r][c];
				}
			for (int c = N - 1; c >= 0; c--)
				for (int i = 0, j = (grid[r][c] < 0) ? 1 : 0; i + j <= k; i++) {
					int p = infinite;
					if (r)
						p = max(p, paths[r - 1][c][i]);
					if (c < N - 1)
						p = max(p, paths_from_right[c + 1][i]);
					if (p != infinite)
						paths_from_right[c][i + j] = p + grid[r][c];
				}
#ifdef DEBUG
				print_paths(N, k, paths_from_left);
				print_paths(N, k, paths_from_right);
#endif
			for (int c = 0; c < N; c++)
				for (int i = 0; i <= k; i++)
					paths[r][c][i] = max(paths_from_left[c][i], paths_from_right[c][i]);
#ifdef DEBUG
			print_paths(N, k, r);
#endif
		}
		int max_path = infinite;
		for (int i = 0; i <= k; i++)
			max_path = max(max_path, paths[N - 1][N - 1][i]);
		cout << "Case " << case_nr << ": ";
		if (max_path != infinite)
			cout << max_path << endl;
		else
			cout << "impossible\n";
	}
	return 0;
}

