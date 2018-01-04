
/*
	UVa 227 - Puzzle

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_227_Puzzle.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
	const int n = 5;
	char puzzle[n + 1][n + 1];
	for (int case_nr = 1; ; case_nr++) {
		int r, c;
		gets(puzzle[0]);
		if (puzzle[0][0] == 'Z')
			break;
		if (case_nr > 1)
			putchar('\n');
		for (int j = 0; j < n; j++)
			if (puzzle[0][j] == ' ') {
				r = 0; c = j;
			}
		for (int i = 1; i < n; i++) {
			gets(puzzle[i]);
			for (int j = 0; j < n; j++)
				if (puzzle[i][j] == ' ') {
					r = i; c = j;
				}
		}
		bool illegal = false;
		int dc;
		while ((dc = getchar()) != '0') {
			if (illegal)
				continue;
			switch (dc) {
			case 'A':
				if (r) {
					swap(puzzle[r][c], puzzle[r - 1][c]);
					r--;
				}
				else
					illegal = true;
				break;
			case 'B':
				if (r < n - 1) {
					swap(puzzle[r][c], puzzle[r + 1][c]);
					r++;
				}
				else
					illegal = true;
				break;
			case 'L':
				if (c) {
					swap(puzzle[r][c], puzzle[r][c - 1]);
					c--;
				}
				else
					illegal = true;
				break;
			case 'R':
				if (c < n - 1) {
					swap(puzzle[r][c], puzzle[r][c + 1]);
					c++;
				}
				else
					illegal = true;
				break;
			}
		}
		getchar(); // skip '\n'
		printf("Puzzle #%d:\n", case_nr);
		if (illegal)
			printf("This puzzle has no final configuration.\n");
		else {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					printf("%c%c", puzzle[i][j], (j == n - 1) ? '\n' : ' ');
		}
	}
	return 0;
}

