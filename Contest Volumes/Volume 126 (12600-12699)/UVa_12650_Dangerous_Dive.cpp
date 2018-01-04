
/*
	UVa 12650 - Dangerous Dive

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12650_Dangerous_Dive.cpp
*/

#include <cstdio>

const int N_max = 10000, R_max = 10000;

bool volunteers[N_max + 1];

int main()
{
	int N, R;
	while (scanf("%d %d", &N, &R) != EOF) {
		if (R < N)
			for (int i = 1; i <= N; i++)
				volunteers[i] = false;
		for (int i = 0; i < R; i++) {
			int j;
			scanf("%d", &j);
			volunteers[j] = true;
		}
		if (R < N) {
			N -= R;
			for (int i = 1; N; i++)
				if (!volunteers[i]) {
					N--;
					printf("%d ", i);
				}
			putchar('\n');
		}
		else
			puts("*");
	}
	return 0;
}

