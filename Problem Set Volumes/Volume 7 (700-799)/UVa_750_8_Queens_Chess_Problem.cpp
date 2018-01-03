
/*
	UVa 750 - 8 Queens Chess Problem

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_750_8_Queens_Chess_Problem.cpp
*/

#include <cstdio>
#include <cstdlib>
using namespace std;

const int nr_rows = 8, nr_columns = 8;
int nr_solutions, rows[nr_columns + 1];

void eight_queens(int ci, int c)
{
	if (ci > nr_columns) {
		printf("%2d     ", nr_solutions++);
		for (int i = 1; i <= nr_columns; i++)
			printf(" %d", rows[i]);
		putchar('\n');
	}
	else if (ci == c)
		eight_queens(ci + 1, c);
	else {
		int i, j;
		for (i = 1; i <= nr_rows; i++) {
			if (i == rows[c] || abs(ci - c) == abs(i - rows[c]))
				continue;
			for (j = 1; j < ci; j++)
				if (i == rows[j] || abs(ci - j) == abs(i - rows[j]))
					break;
			if (j == ci) {
				rows[ci] = i;
				eight_queens(ci + 1, c);
			}
		}
	}
}

int main()
{
	int ds;
	scanf("%d", &ds);
	while (ds--) {
		int r, c;
		scanf("%d %d", &r, &c);
		rows[c] = r;
		printf("SOLN       COLUMN\n #      1 2 3 4 5 6 7 8\n\n");
		nr_solutions = 1;
		eight_queens(1, c);
		if (ds)
			putchar('\n');
	}
	return 0;
}

