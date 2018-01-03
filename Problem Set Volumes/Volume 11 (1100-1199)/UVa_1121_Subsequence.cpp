
/*
	UVa 1121 - Subsequence

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1121_Subsequence.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 100000;
int integers[n_max];

int main()
{
	int N, S;
	while (scanf("%d %d", &N, &S) != EOF) {
		int s = 0, min_length = N + 1;
		for (int i = 0, pi = 0; i < N; i++) {
			scanf("%d", &integers[i]);
			if ((s += integers[i]) >= S) {
				for ( ; pi < i; pi++) {
					if (s - integers[pi] < S)
						break;
					s -= integers[pi];
				}
				min_length = min(min_length, i - pi + 1);
			}
		}
		if (min_length > N)
			min_length = 0;
		printf("%d\n", min_length);
	}
	return 0;
}

