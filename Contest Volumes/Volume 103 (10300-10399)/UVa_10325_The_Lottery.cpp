
/*
	UVa 10325 - The Lottery

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10325_The_Lottery.cpp
*/

#include <cstdio>

long long gcd(long long x, long long y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

long long lcm(long long x, long long y)
{
	long long l = x;
	return (l / gcd(x, y)) * y;
}

int main()
{
	const int m_max = 15;
	const int power_of_2s[m_max + 1] = { // power_of_2s[i] is 2^i
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768
	};
	int N, M;
	while (scanf("%d %d", &N, &M) != EOF) {
		int numbers[m_max];
		for (int m = 0; m < M; m++)
			scanf("%d", &numbers[m]);
		long long nr = N;
		for (int i = 1; i < power_of_2s[M]; i++) {
			int j = 0, k = 0;
			long long l;
			for (int b = 1; k < M; k++, b <<= 1)
				if (i & b) {
					j++;
					if (j > 1) {
						if ((l = lcm(l, numbers[k])) > N)
							break; // Since N doesn't have factors of l, calculating the LCM any further isn't needed.
					}
					else
						l = numbers[k];
				}
			if (k == M) {
				if (j & 1)
					nr -= N / l;
				else
					nr += N / l;
			}
		}
		printf("%lld\n", nr);
	}
	return 0;
}

