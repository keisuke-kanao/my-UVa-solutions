
/*
	UVa 11718 - Fantasy of a Summation

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11718_Fantasy_of_a_Summation.cpp
*/

#include <cstdio>

long long bigmod(long long b, long long p, long long m) // b^p % m
{
	if (!p)
		return 1;
	else if (!(p & 1)) {
		long long bgm = bigmod(b, p / 2, m);
		return (bgm * bgm) % m;
	}
	else
		return ((b % m) * bigmod(b, p - 1, m)) % m;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int n, K, MOD;
		scanf("%d %d %d", &n, &K, &MOD);
		// K * n^(K - 1) * A % MOD
		long long result = bigmod(n, K - 1, MOD);
		result = result * K % MOD;
		long long A = 0;
		for (int i = 0; i < n; i++) {
			int Ai;
			scanf("%d", &Ai);
			A += Ai;
			A %= MOD;
		}
		result = result * A % MOD;
		printf("Case %d: %lld\n", t, result);
	}
	return 0;
}

