
/*
	UVa 232 - Crossword Answers

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_232_Crossword_Answers.cpp
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	const int r_max = 10, c_max = 10;
	char grid[r_max][c_max];
	int definitions[r_max][c_max];
	for (int pn = 1; ; pn++) {
		int r, c;
		cin >> r;
		if (!r)
			break;
		cin >> c;
		for (int i = 0, n = 1; i < r; i++)
			for (int j = 0; j < c; j++) {
				cin >> grid[i][j];
				definitions[i][j] = (grid[i][j] != '*' &&
					(!i || !j || grid[i - 1][j] == '*' || grid[i][j - 1] == '*')) ? n++ : 0;
			}
		if (pn > 1)
			cout << endl;
		cout << "puzzle #" << pn << ":\n";
		cout << "Across\n";
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				if (definitions[i][j] && (!j || grid[i][j - 1] == '*')) {
					cout << setfill(' ') << setw(3) << definitions[i][j] << '.';
					for (int k = j; k < c; k++) {
						if (grid[i][k] == '*')
							break;
						else
							cout << grid[i][k];
					}
					cout << endl;
				}
		cout << "Down\n";
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				if (definitions[i][j] && (!i || grid[i - 1][j] == '*')) {
					cout << setfill(' ') << setw(3) << definitions[i][j] << '.';
					for (int k = i; k < r; k++) {
						if (grid[k][j] == '*')
							break;
						else
							cout << grid[k][j];
					}
					cout << endl;
				}
	}
	return 0;
}

