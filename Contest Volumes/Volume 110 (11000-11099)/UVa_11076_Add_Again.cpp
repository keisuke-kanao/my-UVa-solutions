
/*
	UVa 11076 - Add Again

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11076_Add_Again.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_digits = '9' - '0' + 1, N_max = 12;
int freqs[nr_digits], factorials[N_max + 1];

int main()
{
	factorials[0] = factorials[1] = 1;
	for (int i = 2; i <= N_max; i++)
		factorials[i] = factorials[i - 1] * i;
	while (true) {
		int N;
		scanf("%d", &N);
		if (!N)
			break;
		memset(freqs, 0, sizeof(freqs));
		for (int i = 0; i < N; i++) {
			int d;
			scanf("%d", &d);
			freqs[d]++;
		}
		unsigned long long ds = 0;
		for (int i = 1; i < nr_digits; i++)
			if (freqs[i]) {
				int f = factorials[N - 1];
				for (int j = 0; j < nr_digits; j++)
					if (freqs[j]) {
						if (i == j)
							f /= factorials[freqs[j] - 1];
						else
							f /= factorials[freqs[j]];
					}
				ds += i * f;
#ifdef DEBUG
				printf("%d: %d %llu\n", i, i * f, ds);
#endif
			}
		unsigned long long s = 0;
		for (int i = 0; i < N; i++, ds *= 10)
			s += ds;
		printf("%llu\n", s);
	}
	return 0;
}

