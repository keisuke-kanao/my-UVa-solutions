
/*
	UVa 11040 - Add bricks in the wall

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11040_Add_bricks_in_the_wall.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const int nr_rows = 9;
	int bricks[nr_rows][nr_rows];
	int n;
	cin >> n;
	while (n--) {
		for (int i = 0; i < nr_rows; i++)
			for (int j = 0; j < i; j++)
				bricks[i][j] = 0;
		for (int i = 0; i < nr_rows; i += 2)
			for (int j = 0; j <= i; j += 2)
				cin >> bricks[i][j];
		for (int i = 2; i < nr_rows; i += 2)
			for (int j = 1; j < i; j += 2)
				bricks[i][j] = (bricks[i - 2][j - 1] - bricks[i][j - 1] - bricks[i][j + 1]) / 2;
		for (int i = 1; i < nr_rows; i += 2)
			for (int j = 0; j <= i; j++)
				bricks[i][j] = bricks[i + 1][j] + bricks[i + 1][j + 1];
		for (int i = 0; i < nr_rows; i++) {
			for (int j = 0; j <= i; j++) {
				if (j)
					cout << ' ';
				cout << bricks[i][j];
			}
			cout << endl;
		}
	}
	return 0;
}

