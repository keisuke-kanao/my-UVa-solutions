
/*
	UVa 11536 - Smallest Sub-Array

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11536_Smallest_Sub_Array.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int N_max = 1000000, K_max = 100;
int seq[N_max + 1], freqs[K_max + 1]; // freqs[i] is the number of occurences of i

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N, M, K;
		scanf("%d %d %d", &N, &M, &K);
		if (K < 4) {
			printf("Case %d: %d\n", t, K);
			continue;
		}
		for (int i = 1; i <= K; i++)
			freqs[i] = 0;
		seq[1] = 1, seq[2] = 2, seq[3] = 3;
		freqs[1] = freqs[2] = freqs[3] = 1;
		int k = 3, min_length = N + 1;
		for (int i = 4, pi = 1; i <= N; i++) {
			int s = (seq[i - 1] + seq[i - 2] + seq[i - 3]) % M + 1;
			seq[i] = s;
			if (s <= K) {
				if (!freqs[s]++) {
					if (++k == K)
						min_length = min(min_length, i - pi + 1);
				}
				else {
					for ( ; pi < i; pi++) {
						int p = seq[pi];
						if (p > K)
							continue;
						if (freqs[p] < 2)
							break;
						freqs[p]--;
					}
					if (k == K)
						min_length = min(min_length, i - pi + 1);
				}
			}
		}
		printf("Case %d: ", t);
		if (min_length > N)
			puts("sequence nai");
		else
			printf("%d\n", min_length);
	}
	return 0;
}

