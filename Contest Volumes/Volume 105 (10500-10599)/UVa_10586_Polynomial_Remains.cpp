
/*
	UVa 10586 - Polynomial Remains

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10586_Polynomial_Remains.cpp
*/

#include <cstdio>

const int n_max = 10000;
int coefficients[n_max + 1];

int main()
{
	while (true) {
		int n, k;
		scanf("%d %d", &n, &k);
		if (n == -1)
			break;
		for (int i = 0; i <= n; i++)
			scanf("%d", &coefficients[i]);
		for (int i = n - k, j = n; i >= 0; i--, j--)
			if (coefficients[j]) {
				coefficients[i] -= coefficients[j];
				coefficients[j] = 0;
			}
		int i;
		for (i = k - 1; i >= 0; i--)
			if (coefficients[i])
				break;
		if (i >= 0) {
			for (int j = 0; j <= i; j++) {
				printf("%d%c", coefficients[j], ((j < i) ? ' ' : '\n'));
				coefficients[j] = 0;
			}
		}
		else
			puts("0");
	}
	return 0;
}

