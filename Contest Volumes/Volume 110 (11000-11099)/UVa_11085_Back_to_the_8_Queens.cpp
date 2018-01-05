
/*
	UVa 11085 - Back to the 8-Queens

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11085_Back_to_the_8_Queens.cpp
*/

#include <cstdio>
#include <cstdlib>
using namespace std;

const int nr_rows = 8, nr_columns = 8;

void eight_queens(int ci, int nr, int* pnr, const int irows[], int rows[])
{
	if (ci > nr_columns) {
		if (nr < *pnr)
			*pnr = nr;
	}
	else {
		int i, j;
		for (i = 1; i <= nr_rows; i++) {
			for (j = 1; j < ci; j++)
				if (i == rows[j] || abs(ci - j) == abs(i - rows[j]))
					break;
			if (j == ci) {
				rows[ci] = i;
				eight_queens(ci + 1, ((i == irows[ci]) ? nr : nr + 1), pnr, irows, rows);
			}
		}
	}
}

int main()
{
	int irows[nr_columns + 1], rows[nr_columns + 1];
	for (int case_nr = 1; ; case_nr++) {
		if (scanf("%d %d %d %d %d %d %d %d",
			&irows[1], &irows[2], &irows[3], &irows[4], &irows[5], &irows[6], &irows[7], &irows[8]) == EOF)
			break;
		int nr = nr_rows;
		eight_queens(1, 0, &nr, irows, rows);
		printf("Case %d: %d\n", case_nr, nr);
	}
	return 0;
}

