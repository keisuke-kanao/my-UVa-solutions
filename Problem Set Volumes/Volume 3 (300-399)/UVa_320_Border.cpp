
/*
	UVa 320 - Border

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_320_Border.cpp

	from ACM Southwestern European Regionals - 1996
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_SWERC/1996/index.html)
*/

#include <iostream>
#include <string>
using namespace std;

const int nr_grids = 32;
char squares[nr_grids][nr_grids];

int main()
{
	int t;
	cin >> t;
	for (int c = 1; c <= t; c++) {
		int x, y;
		cin >> x >> y;
		string moves;
		cin >> moves;
		for (int i = 0; i < nr_grids; i++)
			for (int j = 0; j < nr_grids; j++)
				squares[i][j] = '.';
		for (const char* p = moves.c_str(); *p != '.'; p++) {
			switch (*p) {
			case 'N':
				squares[y][x] = 'X';
				y++;
				break;
			case 'S':
				squares[y - 1][x - 1] = 'X';
				y--;
				break;
			case 'E':
				squares[y - 1][x] = 'X';
				x++;
				break;
			case 'W':
				squares[y][x - 1] = 'X';
				x--;
				break;
			}
		}
		cout << "Bitmap #" << c << endl;
		for (int i = nr_grids - 1; i >= 0; i--) {
			for (int j = 0; j < nr_grids; j++)
				cout << squares[i][j];
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}

