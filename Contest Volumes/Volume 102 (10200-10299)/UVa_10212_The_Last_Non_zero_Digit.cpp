
/*
	UVa 10212 The Last Non-zero Digit

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10212_The_Last_Non_zero_Digit.cpp
*/

#include <cstdio>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

const int N_max = 20000000;
const int pow2s[] = {1,
	2, 4, 8, 16, 32, 64, 128, 256,
	512, 1024, 2048, 4096, 8192, 16384, 32768, 65536,
	131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216,
	33554432
};
const int p2s[] = {6, 2, 4, 8};
const int pow5s[] = {1,
	5, 25, 125, 625, 3125, 15625, 78125, 390625,
	1953125, 9765625, 48828125
};
char twos[N_max + 1], fives[N_max + 1];
char integers[N_max + 1];

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int i = 1; i < sizeof(pow2s) / sizeof(int) - 1; i++)
		for (long long j = pow2s[i]; j <= N_max; j += pow2s[i]) {
			twos[j]++;
		}
	for (int i = 1; i < sizeof(pow5s) / sizeof(int) - 1; i++)
		for (long long j = pow5s[i]; j <= N_max; j += pow5s[i])
			fives[j]++;
	for (int i = 1; i <= N_max; i++)
		integers[i] = static_cast<char>(i / pow2s[twos[i]] / pow5s[fives[i]] % 10);
	int N, M;
	while (scanf("%d %d", &N, &M) != EOF) {
		int p = 1;
		int t = 0, f = 0;
		for (int i = N, j = N - M; i > j; i--) {
			p *= integers[i];
			p %= 10;
			t += twos[i]; f += fives[i];
		}
#ifdef DEBUG
		printf("%d %d %d\n", p, t, f);
#endif
		if (t || f) {
			if (t > f) {
				p *= p2s[(t - f) % 4];
				p %= 10;
			}
			else if (t < f) {
				p *= 5;
				p %= 10;
			}
		}
		printf("%d\n", p);
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

