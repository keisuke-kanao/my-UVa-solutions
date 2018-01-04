
/*
	UVa 11955 - Binomial Theorem

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11955_Binomial_Theorem.cpp
*/

#include <cstdio>
#include <cstdlib>

int main()
{
	const int k_max = 50;
	long long bc[k_max + 1][k_max + 1]; // binomial coefficient
	for (int i = 0; i <= k_max; i++)
		bc[i][0] = 1;
	for (int j = 0; j <= k_max; j++)
		bc[j][j] = 1;
	for (int i = 1; i <= k_max; i++)
		for (int j = 1; j < i; j++)
			bc[i][j] = bc[i - 1][j - 1] + bc[i - 1][j];

	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		const int nr_chars_max = 100;
		char s[nr_chars_max + 1], a[nr_chars_max + 1], b[nr_chars_max + 1];
		scanf("%s", s);
		const char* p = s + 1;
		char* q;
		for (q = a; *p != '+'; p++, q++)
			*q = *p;
		p++;
		*q = '\0';
		for (q = b; *p != ')'; p++, q++)
			*q = *p;
		p += 2;
		*q = '\0';
		int k = atoi(p);
#ifdef DEBUG
		printf("%s %s %d\n", a, b, k);
#endif
		printf("Case %d: ", t);
		for (int i = k, j = 0; i >= 0; i--, j++) {
			if (bc[k][j] > 1)
				printf("%lld*", bc[k][j]);
			if (i) {
				printf("%s", a);
				if (i > 1)
					printf("^%d", i);
			}
			if (i && j)
				putchar('*');
			if (j) {
				printf("%s", b);
				if (j > 1)
					printf("^%d", j);
			}
			if (i)
				putchar('+');
		}
		putchar('\n');
	}
	return 0;
}

