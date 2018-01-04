
/*
	UVa 11968 - In The Airport

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11968_In_The_Airport.cpp
*/

#include <cstdio>
#include <cstdlib>

const int N_max = 1000;
int prices[N_max];

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N, M, K;
		scanf("%d %d %d", &N, &M, &K);
		long long s = 0;
		for (int i = 0; i < N; i++) {
			scanf("%d", &prices[i]);
			s += prices[i];
		}
		int ci = 0, di = M;
		long long n = N, dc = llabs(n * prices[ci] - s), dd = llabs(n * prices[di] - s);
		for (int i = 1; i < M; i++) {
			long long d = llabs(n * prices[i] - s);
			if (d < dc || d == dc && prices[i] < prices[ci]) {
				ci = i;
				dc = d;
			}
		}
		for (int i = M + 1; i < M + K; i++) {
			long long d = llabs(n * prices[i] - s);
			if (d < dd || d == dd && prices[i] < prices[di]) {
				di = i;
				dd = d;
			}
		}
		printf("Case #%d: %d %d\n", t, prices[ci], prices[di]);
	}
	return 0;
}

