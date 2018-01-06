
/*
	UVa 10094 - Place the Guards

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10094_Place_the_Guards.cpp
*/

/*
Explicit solutions[edit]
These brute-force algorithms to count the number of solutions are computationally manageable for n = 8, 
but would be intractable for problems of n >= 20, as 20! = 2.433 Å~ 1018. 
If the goal is to find a single solution then explicit solutions exist for all n >= 4, 
requiring no combinatorial search whatsoever. 
The explicit solutions exhibit stair-stepped patterns, as in the following examples for n = 8, 9 and 10:
...

The examples above can be obtained with the following formulas. 
Let (i, j) be the square in column i and row j on the n Å~ n chessboard, k an integer.

If n is even and n != 6k + 2, 
  then place queens at (i, 2i) and (n/2 + i, 2i - 1) for i = 1, 2, ..., n / 2.
If n is even and n != 6k, 
  then place queens at (i, 1 + (2i + n/2 - 3 (mod n))) and (n + 1 - i, n - (2i + n/2 - 3 (mod n))) 
  for i = 1, 2, ..., n / 2.
If n is odd, then use one of the patterns above for (n - 1) and add a queen at (n, n).
*/

#include <cstdio>
#ifdef DEBUG
#include <cassert>
#include <cstdlib>
#endif

const int n_max = 1000;
int rows[n_max + 1]; // rows[i] is the row number for i-th column

#ifdef DEBUG
bool validate_rows(int n)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i != j) {
				if (rows[i] == rows[j] || abs(i - j) == abs(rows[i] - rows[j]))
					return false;
			}
	return true;
}
#endif

int main()
{
	int n;
	while (scanf("%d", &n) != EOF) {
		if (n < 4)
			puts("Impossible");
		else {
			int m = n;
			if (m & 1) { // odd
				rows[m] = m;
				m--;
			}
			int i, j, k;
			if ((m - 2) % 6)
				for (i = 1, j = m / 2; i <= j; i++) {
					k = 2 * i;
					rows[i] = k, rows[j + i] = k - 1;
				}
			else
				for (i = 1, j = m / 2; i <= j; i++) {
					k = (2 * i + j - 3) % m;
					rows[i] = 1 + k, rows[m + 1 - i] = m - k;
				}
#ifdef DEBUG
			assert(validate_rows(n));
#endif
			for (int i = 1; i <= n; i++)
				printf("%d%c", rows[i], ((i < n) ? ' ' : '\n'));
		}
	}
	return 0;
}

