
/*
	UVa 10637 - Coprimes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10637_Coprimes.cpp
*/

#include <cstdio>

const int S_max = 100;

bool coprimes[S_max + 1][S_max + 1];
	// coprimes[i][j] is true if i and j (i <= j) is co-prime

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

void partition(int S, int t, int ti, int numbers[])
{
	if (S) {
		for (int i = (!ti || numbers[ti - 1] == 1) ? 1 : numbers[ti - 1] + 1; i <= S; i++) {
			int j;
			for (j = 0; j < ti; j++)
				if (!coprimes[numbers[j]][i])
					break;
			if (j == ti) {
				numbers[ti] = i;
				partition(S - i, t, ti + 1, numbers);
			}
		}
	}
	else if (ti == t) {
		for (int i = 0; i < t; i++)
			printf("%d%c", numbers[i], ((i < t - 1) ? ' ' : '\n'));
	}
}

int main()
{
	for (int i = 1; i <= S_max; i++)
		coprimes[1][i] = true;
	for (int i = 2; i < S_max; i++)
		for (int j = i + 1; j <= S_max; j++)
			coprimes[i][j] = gcd(i, j) == 1;
	int N;
	scanf("%d", &N);
	for (int cn = 1; cn <= N; cn++) {
		int S, t;
		scanf("%d %d", &S, &t);
		printf("Case %d:\n", cn);
		int numbers[S_max];
		partition(S, t, 0, numbers);
	}
	return 0;
}

