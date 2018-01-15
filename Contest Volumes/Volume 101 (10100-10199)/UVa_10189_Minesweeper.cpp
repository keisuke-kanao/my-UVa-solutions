
/*
	1.6.2 Minesweeper
	PC/UVa IDs: 110102/10189, Popularity: A, Success rate: high Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10189_Minesweeper.cpp
*/

#include <iostream>
using namespace std;

const int n_max = 100 /* max. number of lines */, m_max = 100 /* max. number of columns */;

void increment_squares(int i, int j, int n, int m, int squares[n_max][m_max])
{
	int c_min = (j) ? j - 1 : 0;
	int c_max = (j + 2 > m) ? m : j + 2;
	// for squares in the line immediately before i
	if (i)
		for (int k = c_min; k < c_max; k++)
			if (squares[i - 1][k] != -1)
				squares[i - 1][k]++;
	// for squares in the same line 
	for (int k = c_min; k < c_max; k++)
		if (k != j && squares[i][k] != -1)
			squares[i][k]++;
	// for squares in the line immediately after i
	if (i < n - 1)
		for (int k = c_min; k < c_max; k++)
			if (squares[i + 1][k] != -1)
				squares[i + 1][k]++;
}

int main(int /* argc */, char** /* argv */)
{
	int squares[n_max][m_max]; // -1 for the squre where a mine is located, else the number of mines adjacent to the squre

	int field = 0; // field #
	int n, m;
	while (cin >> n >> m) {
		if (!n && !m) // end of input
			break;
		// initialize the squares
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				squares[i][j] = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				char c;
				cin >> c;
				if (c == '*')
					squares[i][j] = -1;
			}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (squares[i][j] == -1)
					increment_squares(i, j, n, m, squares); // increment the squares which are adjacent to this square
		if (field)
			cout << endl;
		cout << "Field #" << ++field << ":\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				if (squares[i][j] == -1)
					cout << '*';
				else
					cout << squares[i][j];
			cout << endl;
		}
	}
}

