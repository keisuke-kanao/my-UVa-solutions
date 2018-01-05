
/*
	UVa 10326 - The Polynomial Equation

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10326_The_Polynomial_Equation.cpp
*/

#include <cstdio>

int main()
{
	int N;
	while (scanf("%d", &N) != EOF) {
/*
		if (!N) {
			puts("+ 0 = 0");
			continue;
		}
*/
		const int N_max = 50;
		long long coefficients[N_max];
		for (int i = 0; i < N; i++)
			coefficients[i] = 0;
		for (int i = 0; i < N; i++) {
			int root;
			scanf("%d", &root);
			for (int j = i; j; j--)
				coefficients[j] += coefficients[j - 1] * root;
			coefficients[0] += root;
		}
		if (N > 1)
			printf("x^%d ", N);
		else
			printf("x ");
		for (int i = 0; i < N; i++) {
			long long c = coefficients[i];
			if (!(i & 1))
				c = -c;
			if (i < N - 1) {
				if (c) {
					printf((c >= 0) ? "+ " : "- ");
					if (c < 0)
						c = -c;
					if (c > 1)
						printf("%lldx", c);
					else
						putchar('x');
					if (i < N - 2)
						printf("^%d ", N - i - 1);
					else
						putchar(' ');
				}
			}
			else {
				printf((c >= 0) ? "+ " : "- ");
				if (c < 0)
					c = -c;
				printf("%lld ", c);
			}
		}
		puts("= 0");
	}
	return 0;
}

