
/*
	UVa 10870 - Recurrences

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10870_Recurrences.cpp
*/

/*
 |  f(n+1)  |   | a1 a2 ...... ad |   |  f(n)  |
 |  f(n)    |   | 1  0  0 .... 0  |   | f(n-1) |
 |    .     | = | 0  1  0 .... 0  | * |   .    |
 |    .     |   | ..............  |   |   .    |
 | f(n-d+1) |   | ...........1 0  |   | f(n-d) |

 Generalization:

 |  f(n+k)  |   | a1 a2 ...... ad |^k    |  f(n)  |
 | f(n+k-1) |   | 1  0  0 .... 0  |      | f(n-1) |
 |    .     | = | 0  1  0 .... 0  |  *   |   .    |
 |    .     |   | ..............  |      |   .    |
 |f(n+k-d+1)|   | ...........1 0  |      | f(n-d) |

 Answer is f(n+k) , k = n-d
*/

#include <cstdio>

const int d_max = 15;

void identity_matrix(int d, int a[d_max + 1][d_max + 1])
{
	for (int i = 1; i <= d; i++)
		for (int j = 1; j <= d; j++)
            a[i][j] = (i == j) ? 1 : 0;
}

void matrix_multiply(int d, int m, int ma[d_max + 1][d_max + 1], int mb[d_max + 1][d_max + 1])
{
	int result[d_max + 1][d_max + 1];
	for (int i = 1; i <= d; i++)
		for (int j = 1; j <= d; j++) {
			int r = 0;
            for (int k = 1; k <= d; k++) {
				r += ma[i][k] * mb[k][j] % m;
				r %= m;
			}
			result[i][j] = r;
		}
	for (int i = 1; i <= d; i++)
		for (int j = 1; j <= d; j++)
			ma[i][j] = result[i][j];
}

void matrix_power(int d, int n, int m, int matrix[d_max + 1][d_max + 1], int result[d_max + 1][d_max + 1])
{
	identity_matrix(d, result);
	while (n) {
		if (n % 2 == 0) {
			matrix_multiply(d, m, matrix, matrix);
			n /= 2;
		}
        else {
			matrix_multiply(d, m, result, matrix);
			n--;
		}
	}
}

int main()
{
	while (true) {
		int d, n, m;
		scanf("%d %d %d", &d, &n, &m);
		if (!d)
			break;
		int f[d_max + 1], matrix[d_max + 1][d_max + 1];
		for (int i = 1; i <= d; i++) {
			scanf("%d", &matrix[1][i]);
			matrix[1][i] %= m;
		}
		for (int i = 1; i <= d; i++) {
			scanf("%d", &f[i]);
			f[i] %= m;
		}
		if (n <= d)
			printf("%d\n", f[n]);
		else {
			int result[d_max + 1][d_max + 1];
			for (int i = 2; i <= d; i++)
				for (int j = 1; j <= d; j++)
					matrix[i][j] = (i == j + 1) ? 1 : 0;
			matrix_power(d, n - d, m, matrix, result);
#ifdef DEBUG
			for (int i = 1; i <= d; i++)
				for (int j = 1; j <= d; j++)
					printf("%d%c", result[i][j], ((j < d) ? ' ' : '\n'));
#endif
			int r = 0;
			for (int i = 1; i <= d; i++) {
				r += result[1][i] * f[d - i + 1] % m;
				r %= m;
			}
			printf("%d\n", r);
		}
	}
	return 0;
}

