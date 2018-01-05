
/*
	UVa 11195 - Another n-Queen Problem

	To build using Visucal Studio 2012:
		cl -EHsc -O2 UVa_11195_Another_n-Queen_Problem.cpp

	An accepted solution.
*/

#include <cstdio>
#include <cstdlib>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

const int n_max = 15;
int n, nr_solutions, squares[n_max];
const int pre_calculated_nr_solutions[] = {0, 1, 0, 0, 2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712, 365596, 2279184};

void n_queens(int r, int left, int down, int right)
{
	if (r == n)
        nr_solutions++;
	else {
		int bitmap = squares[r] & ~(left | down | right); // not-threatened columns
		while (bitmap) {
			int bit = -bitmap & bitmap; // least significant bit
            bitmap ^= bit;
            n_queens(r + 1, (left | bit) << 1, down | bit, (right | bit) >> 1);
		}
	}
}

int main()
{
	for (int cn = 1; ; cn++) {
		scanf("%d", &n);
		if (!n)
			break;
		bool bad = false;
		for (int i = 0; i < n; i++) {
			char s[n_max + 1];
			scanf("%s", s);
			squares[i] = 0;
			for (int j = 0, b = 1 << (n - 1); j < n; j++, b >>= 1) {
				if (s[j] == '.')
					squares[i] |= b;
				else
					bad = true;
			}
		}
		if (bad) {
#ifdef __ELAPSED_TIME__
			clock_t start = clock();
#endif
			nr_solutions = 0;
			n_queens(0, 0, 0, 0);
#ifdef __ELAPSED_TIME__
			fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
		}
		else
			nr_solutions = pre_calculated_nr_solutions[n];
		printf("Case %d: %d\n", cn, nr_solutions);
	}
	return 0;
}

/*
Sample Input
8
........
........
........
........
........
........
........
........
4
.*..
....
....
....
0

Sample Output

Case 1: 92
Case 2: 1


8
........
........
........
........
......*.
....*...
........
.....*..
4
....
....
..*.
....
0

Case 1: 61
Case 2: 2

*/
