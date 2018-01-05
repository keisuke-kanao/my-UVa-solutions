
/*
	UVa 10843 - Anne's game

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10843_Annes_game.cpp
*/

/*
In mathematics, Cayley's formula is a result in graph theory named after Arthur Cayley. 
It states that for every positive integer n, the number of trees on n labeled vertices is n^{n-2}.
*/

#include <cstdio>

const int n_max = 100, divisor = 2000000011;
int answers[n_max + 1];

int main()
{
	answers[1] = 1;
	for (int i = 2; i <= n_max; i++) {
		long long a = 1;
		for (int j = 0; j < i - 2; j++) {
			a *= i;
			a %= divisor;
		}
		answers[i] = static_cast<int>(a); // i^(i - 2)
	}
	int N;
	scanf("%d", &N);
	for (int cn = 1; cn <= N; cn++) {
		int n;
		scanf("%d", &n);
		printf("Case #%d: %d\n", cn, answers[n]);
	}
	return 0;
}

/*
Sample Input

3
1
2
3

Sample Output

Case #1: 1
Case #2: 1
Case #3: 3

*/

