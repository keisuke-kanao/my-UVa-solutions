
/*
	UVa 1583 - Digit Generator

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1583_Digit_Generator.cpp
*/

#include <cstdio>

const int N_max = 100000;
int generators[N_max + 1];

int digit_sum(int n)
{
	int s = n;
	do {
		s += n % 10;
		n /= 10;
	} while (n);
	return s;
}

int main()
{
	for (int i = 1; i <= N_max; i++) {
		int ds = digit_sum(i);
		if (ds <= N_max && !generators[ds])
			generators[ds] = i;
	}
	int T;
	scanf("%d", &T);
	while (T--) {
		int N;
		scanf("%d", &N);
		printf("%d\n", generators[N]);
	}
	return 0;
}

