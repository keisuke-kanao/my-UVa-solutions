
/*
	UVa 12751 - An Interesting Game

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12751_An_Interesting_Game.cpp
*/

#include <cstdio>

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N, K, X;
		scanf("%d %d %d", &N, &K, &X);
		printf("Case %d: %d\n", t, (N * N + N + K - K * K) / 2 - K * X);
	}
	return 0;
}

