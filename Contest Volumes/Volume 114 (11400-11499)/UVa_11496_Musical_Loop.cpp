
/*
	UVa 11496 - Musical Loop

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11496_Musical_Loop.cpp
*/

#include <cstdio>

const int n_max = 10000;
int samples[n_max + 2];

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			scanf("%d", &samples[i]);
		int peaks = n;
		if (n > 2) {
			samples[n] = samples[0]; samples[n + 1] = samples[1];
			for (int i = 1; i <= n; i++)
				if (samples[i + 1] > samples[i] && samples[i] > samples[i - 1] ||
					samples[i + 1] < samples[i] && samples[i] < samples[i - 1])
					peaks--;
		}
		printf("%d\n", peaks);
	}
	return 0;
}

