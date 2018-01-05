
/*
	UVa 10363 - Tic Tac Toe

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10363_Tic_Tac_Toe.cpp
*/

#include <iostream>
using namespace std;

const int n = 3;
char grid[n][n];

int get_winner()
{
	// count the entirely occupied lines
	int winner = 0;
	int vw = 0;
	for (int i = 0, hw = 0; i < n; i++) { // horizontal lines
		char c = grid[i][0];
		if (c != '.' && c == grid[i][1] && c == grid[i][2])
			if (hw)
				return -1;
			else
				winner = hw = c;
	}
	for (int i = 0, vw = 0; i < n; i++) { // vertical lines
		char c = grid[0][i];
		if (c != '.' && c == grid[1][i] && c == grid[2][i])
			if (vw || winner && c != winner)
				return -1;
			else
				winner = vw = c;
	}
	// diagonal lines
	char c = grid[0][0];
	if (c != '.' && c == grid[1][1] && c == grid[2][2]) {
		if (winner && c != winner)
			return -1;
		else
			winner = c;
	}
	c = grid[0][2];
	if (c != '.' && c == grid[1][1] && c == grid[2][0]) {
		if (winner && c != winner)
			return -1;
		else
			winner = c;
	}
	return winner;
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int nX = 0, nO = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cin >> grid[i][j];
				if (grid[i][j] == 'X')
					nX++;
				else if (grid[i][j] == 'O')
					nO++;
			}
		bool valid = true;
		if (nO > nX || nO + 1 < nX)
			valid = false;
		else {
			int winner = get_winner();
			if (winner == -1)
				valid = false;
			else if (winner == 'X') {
				if (nX != nO + 1)
					valid = false;
			}
			else if (winner == 'O') {
				if (nX != nO)
					valid = false;
			}
		}
		cout << ((valid) ? "yes\n" : "no\n");
	}
	return 0;
}

