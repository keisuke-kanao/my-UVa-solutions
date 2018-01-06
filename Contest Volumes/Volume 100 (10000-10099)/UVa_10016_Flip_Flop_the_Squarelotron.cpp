
/*
	UVa 10016 - Flip-Flop the Squarelotron

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10016_Flip_Flop_the_Squarelotron.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 100;
int matrix[n_max][n_max];

/*
For the rgi-th ring (rgi >= 0), the corresponding elements of matrix are:
	matrix[rgi][rgi] - matrix[rgi][n - 1 - rgi] // top row
	matrix[n - 1 - rgi][rgi] - matrix[n - 1 - rgi][n - 1 - rgi] // bottom row

	matrix[rgi][rgi] - matrix[n - 1 - rgi][rgi] // left column
	matrix[rgi][n - 1 - rgi] - matrix[n - 1 - rgi][n - 1 - rgi] // right column
*/

enum {upside_down = 1, left_right, main_diagonal, main_inverse_diagonal};

void upside_down_flip(int n, int rgi)
{
	for (int c = rgi; c < n - rgi; c++)
		swap(matrix[rgi][c], matrix[n - 1 - rgi][c]);
	for (int r = rgi + 1; r < n / 2; r++) {
		swap(matrix[r][rgi], matrix[n - 1 - r][rgi]);
		swap(matrix[r][n - 1 - rgi], matrix[n - 1 - r][n - 1 - rgi]);
	}
}

void left_right_flip(int n, int rgi)
{
	for (int r = rgi; r < n - rgi; r++)
		swap(matrix[r][rgi], matrix[r][n - 1 - rgi]);
	for (int c = rgi + 1; c < n / 2; c++) {
		swap(matrix[rgi][c], matrix[rgi][n - 1 - c]);
		swap(matrix[n - 1 - rgi][c], matrix[n - 1 - rgi][n - 1 - c]);
	}
}

void main_diagonal_flip(int n, int rgi)
{
	for (int c = rgi + 1; c < n - rgi; c++)
		swap(matrix[rgi][c], matrix[c][rgi]);
	for (int c = rgi + 1; c < n - rgi - 1; c++)
		swap(matrix[n - 1 - rgi][c], matrix[c][n - 1 - rgi]);
}

void main_inverse_diagonal_flip(int n, int rgi)
{
	for (int c = rgi; c < n - rgi - 1; c++)
		swap(matrix[rgi][c], matrix[n - 1 - c][n - 1 - rgi]);
	for (int c = rgi + 1; c < n - rgi - 1; c++)
		swap(matrix[n - 1 - rgi][c], matrix[n - 1 - c][rgi]);
}

int main()
{
	int m;
	scanf("%d", &m);
	while (m--) {
		int n;
		scanf("%d", &n);
		for (int r = 0; r < n; r++)
			for (int c = 0; c < n; c++)
				scanf("%d", &matrix[r][c]);
		for (int rgi = 0, nr_rings = (n + 1) / 2; rgi < nr_rings; rgi++) {
			int t;
			scanf("%d", &t);
			while (t--) {
				int c;
				scanf("%d", &c);
				switch (c) {
				case upside_down:
					upside_down_flip(n, rgi);
					break;
				case left_right:
					left_right_flip(n, rgi);
					break;
				case main_diagonal:
					main_diagonal_flip(n, rgi);
					break;
				case main_inverse_diagonal:
					main_inverse_diagonal_flip(n, rgi);
					break;
				}
#ifdef DEBUG
				for (int r = 0; r < n; r++)
					for (int c = 0; c < n; c++)
						fprintf(stderr, "%d%c", matrix[r][c], ((c == n - 1) ? '\n' : ' '));
#endif
			}
		}
		for (int r = 0; r < n; r++)
			for (int c = 0; c < n; c++)
				printf("%d%c", matrix[r][c], ((c == n - 1) ? '\n' : ' '));
	}
	return 0;
}

