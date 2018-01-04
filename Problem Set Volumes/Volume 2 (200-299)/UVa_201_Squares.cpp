
/*
	UVa 201 - Squares

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_201_Squares.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

const int n_max = 9;
bool connections[n_max * n_max][n_max * n_max];
	// connections[i][j] is true if a line between row = i / n, column = i % n and  row = j / n, column = j % n
int horizontal_lines[n_max][n_max];
	// horizontal_lines[i][j] is the horizontal line length starting from row = i, column = j
int vertical_lines[n_max][n_max];
	// vertical_lines[i][j] is the vertical line length starting from row = i, column = j

int main()
{
	int pn = 0;
	int n, m;
	while (cin >> n >> m) {
		if (pn)
			cout << "\n**********************************\n\n";
		for (int i = 0; i < n * n; i++)
			for (int j = 0; j < n * n; j++)
				connections[i][j] = false;
		while (m--) {
			char d;
			int i, j;
			cin >> d >> i >> j;
			i--; j--;
			if (i < 0 || i >= n || j < 0 || j >= n)
				continue;
			if (d == 'H')
				connections[i * n + j][i * n + j + 1] = true;
			else
				connections[j * n + i][(j + 1) * n + i] = true;
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n - 1; j++) {
				horizontal_lines[i][j] = 0;
				for (int k = j; k < n - 1; k++) {
					if (connections[i * n + k][i * n + k + 1])
						horizontal_lines[i][j]++;
					else
						break;
				}
			}
		for (int j = 0; j < n; j++)
			for (int i = 0; i < n - 1; i++) {
				vertical_lines[i][j] = 0;
				for (int k = i; k < n - 1; k++) {
					if (connections[k * n + j][(k + 1) * n + j])
						vertical_lines[i][j]++;
					else
						break;
				}
			}
		cout << "Problem #" << pn + 1 << endl << endl;
		int nr_total_squares = 0;
		for (int s = 1; s < n; s++) {
			int nr_squares = 0;
			for (int i = 0; i < n - s; i++)
				for (int j = 0; j < n - s; j++)
					if (horizontal_lines[i][j] >= s && horizontal_lines[i + s][j] >= s &&
						vertical_lines[i][j] >= s && vertical_lines[i][j + s] >= s)
						nr_squares++;
			if (nr_squares) {
				nr_total_squares += nr_squares;
				cout << nr_squares << " square (s) of size " << s << endl;
			}
		}
		if (!nr_total_squares)
			cout << "No completed squares can be found.\n";
		pn++;
	}
	return 0;
}

