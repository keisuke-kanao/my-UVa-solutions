
/*
	UVa 12068 - Harmonic Mean

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12068_Harmonic_Mean.cpp

	This is an accepted solution.
*/

#include <cstdio>

long long gcd(long long x, long long y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int main()
{
	int S;
	scanf("%d", &S);
	for (int s = 1; s <= S; s++) {
		const int N_max = 8;
		int N, numbers[N_max];
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d", &numbers[i]);
		long long numerator = N, denominator = 0;
		for (int i = 0; i < N; i++) {
			numerator *= numbers[i];
			long long d = 1;
			for (int j = 0; j < N - 1; j++)
				d *= numbers[(i + j) % N];
			denominator += d;
		}
		long long g = gcd(numerator, denominator);
		printf("Case %d: %lld/%lld\n", s, numerator / g, denominator / g);
	}
	return 0;
}

