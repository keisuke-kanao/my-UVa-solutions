
/*
	UVa 10279 - Mine Sweeper

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10279_Mine_Sweeper.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const int nr_dirs = 8;
	const int dirs[nr_dirs][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
	const int n_max = 10;
	char mines[n_max][n_max], game[n_max][n_max];
	int g;
	cin >> g;
	while (g--) {
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cin >> mines[i][j];
				if (mines[i][j] != '*')
					mines[i][j] = '0';
			}
		// mark the grids that are adjacent to the mines with '1' - '8'
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (mines[i][j] == '*') {
					for (int k = 0; k < nr_dirs; k++) {
						int ai = i + dirs[k][0], aj = j + dirs[k][1];
						if (ai >= 0 && ai < n && aj >= 0 && aj <  n && mines[ai][aj] != '*')
							mines[ai][aj]++;
					}
				}
		bool mine_touched = false;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cin >> game[i][j];
				if (game[i][j] == 'x') {
					if ((game[i][j] = mines[i][j]) == '*')
						mine_touched = true;
				}
			}
		// If a mine has been touched, all positions with a mine should be marked with '*'.
		if (mine_touched) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (mines[i][j] == '*')
						game[i][j] = '*';
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				cout << game[i][j];
			cout << endl;
		}
		if (g)
			cout << endl;
	}
	return 0;
}

