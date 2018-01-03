
/*
	UVa 10913 - Walking on a Grid

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10913_Walking_on_a_Grid.cpp
*/

const int N_max = 75, k_max = 5;

int sums[N_max][N_max][k_max + 1];


for (int j = 0; j < N; j++)
	for (int l = 0; l <= k; l++)
		sums_from_left[j][l] = sums_from_right[j][l] = numeric_limits<int>::min();

if (grid[i][j] > = 0)
	sums_from_left[j][0] = (grid[i][j] >= 0



int sums_from_left[N_max][k_max], sums_from_right[N_max][k_max];

for (int j = 0; j < N; j++) // from left to right

	int g = grid[i][j];
	int s = g + max(sums[i - 1][j][l], sums[i][j - 1][l]);
	if (g >= 0)
		sums_from_left[i][j][l] = s;
	else if (l < k)
		sums_from_left[i][j][l + 1] = s;

for (int j = N - 1; j >= 0; j--) // from right to left
	int g = grid[i][j];
	int s = g + max(sums[i - 1][j][l], sums[i][j + 1][l]);
	if (g >= 0)
		sums_from_left[i][j][l] = s;
	else if (l < k)
		sums_from_left[i][j][l + 1] = s;

for (int j = 0; j < N; j++)
	for (int l = 0; l < k; i++)
		sums[i][j][l] = max(sums_from_left[i][j][l], sums_from_right[i][j][l]);



#include <iostream>
#include <queque>
using namespase std;

enum {dir_left, dir_right, dir_down};
const int N_max = 75, k_max = 5, nr_dirs = dir_down - dir_left + 1;;
const dirs[nr_dirs][2] = {{0, -1}, {0, 1}, {1, 0}};
int grid[N_max][N_max];
int sums[N_max][N_max][k_max][nr_dirs];
	// sums[i][j][k][d] is the sum at (i, j) with k negative integers and d direction
bool visited[N_max][N_max][k_max][nr_dirs];

struct state {
	int i_, j_, k_, s_;
	state(int i, int j, int k, int s) : i_(i), j_(j), k_(k), s_(s) {}
};

void bfs(int N, int k)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int l = 0; l < k; l++)
				for (int d = 0; d < nr_dirs; d++) {
					visited[i][j][l][d] = false;
					sums[i][j][l][d] = -1;
				}

	queue<state> sq;
	int g = grid[0][0];
	if (g >= 0 || k)
		sq.push(state(0, 0, ((g >= 0) ? 0 : 1), g));
	while (!sq.empty()) {
		state s = sq.top(); sq.pop();
		for (int d = 0; d < nr_dirs; d++) {
			int i = s.i_ + dirs[d][0], j = s.j_ + dirs[d][1];
			if (i < 0 || i >= N || j < 0 || j >= N)
				continue;
			g = grid[i][j];
			if (g >= 0) {
				if (!visited[i][j][s.k_][d]) {
					visited[i][j][s.k_][d] = true;
					sums[i][j][s.k_][d] = s.s_ + g;
					sq.push(state(i, j, s.k_, s.s_ + g));
				}
			}
			else {
				if (s.k_ < k && !visited[i][j][s.k_ + 1][d]) {
					visited[i][j][s.k_ + 1][d] = true;
					sums[i][j][s.k_ + 1][d] = s.s_ + g;
					sq.push(state(i, j, s.k_ + 1, s.s + g));
				}
			}
		}
	}
}

int main()
{
	while (true) {
		int N, k;
		cin >> N >> k;
		if (!N && !k)
			break;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> grid[i][j];
	}
	return 0;
}

