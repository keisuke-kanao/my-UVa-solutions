
/*
	UVa 11565 - Simple Equations

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11565_Simple_Equations.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

const int ABC_max = 10000;
int nr_factors, factors[ABC_max];

bool satisfy_equation(int A, int B, int C, int x, int y, int& z)
{
	int k = x * y;
	if (!(B % k)) {
		z = B / k;
		if (x != z && y != z && x + y + z == A && x * x + y * y + z * z == C)
			return true;
	}
	return false;
}

bool solve_equation(int A, int B, int C, int& x, int& y, int& z)
{
	int i, j;
	for (i = nr_factors - 1; i > 0; i--) {
		x = -factors[i];
		for (j = i - 1; j >= 0; j--) {
			y = -factors[j];
			if (satisfy_equation(A, B, C, x, y, z))
				return true;
		}
		for (j = 0; j < i; j++) {
			y = factors[j];
			if (satisfy_equation(A, B, C, x, y, z))
				return true;
		}
	}
	for (int i = 0; i < nr_factors - 1; i++) {
		x = factors[i];
		for (int j = nr_factors - 1; j > i; j--) {
			y = -factors[j];
			if (satisfy_equation(A, B, C, x, y, z))
				return true;
		}
		for (int j = i + 1; j < nr_factors; j++) {
			y = factors[j];
			if (satisfy_equation(A, B, C, x, y, z))
				return true;
		}
	}

	return false;
}

int main()
{
	int N;
	scanf("%d", &N);
	while (N--) {
		int A, B, C;
		scanf("%d %d %d", &A, &B, &C);
		nr_factors = 0;
		for (int i = 1, j = static_cast<int>(sqrt(static_cast<double>(B))); i <= j; i++)
			if (!(B % i)) {
				factors[nr_factors++] = i;
				if (i < B / i)
					factors[nr_factors++] = B / i;
			}
		sort(factors, factors + nr_factors);
		int x, y, z;
		if (solve_equation(A, B, C, x, y, z))
			printf("%d %d %d\n", x, y, z);
		else
			puts("No solution.");
	}
	return 0;
}

