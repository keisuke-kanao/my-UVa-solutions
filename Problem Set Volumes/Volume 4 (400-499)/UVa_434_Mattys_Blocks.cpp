
/*
	UVa 434 - Matty's Blocks

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_434_Mattys_Blocks.cpp
*/

#include <algorithm>
#include <functional>
#include <cstdio>
using namespace std;

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		const int K_max = 8;
		int K;
		scanf("%d", &K);
		int i, j, f[K_max], sf[K_max], r[K_max], sr[K_max];
		for (i = 0; i < K; i++) {
			scanf("%d", &f[i]);
			sf[i] = f[i];
		}
		for (i = 0; i < K; i++) {
			scanf("%d", &r[i]);
			sr[i] = r[i];
		}
		sort(sf, sf + K, greater<int>());
		sort(sr, sr + K, greater<int>());
		int min_blocks = 0;
		for (i = 0, j = 0; i < K && j < K; ) {
			if (sf[i] == sr[j]) {
				min_blocks += sf[i];
				i++; j++;
			}
			else if (sf[i] < sr[j])
				min_blocks += sr[j++];
			else
				min_blocks += sf[i++];
		}
		if (i < K) {
			for ( ; i < K; i++)
				min_blocks += sf[i];
		}
		else if (j < K) {
			for ( ; j < K; j++)
				min_blocks += sr[j];
		}
		int max_blocks = 0;
		for (i = 0; i < K; i++)
			for (j = 0; j < K; j++)
				max_blocks += min(f[i], r[j]);
		printf("Matty needs at least %d blocks, and can add at most %d extra blocks.\n", min_blocks, max_blocks - min_blocks);
	}
	return 0;
}

