
/*
	UVa 11149 - Power of Matrix

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11149_Power_of_Matrix.cpp
*/

#include <vector>
#include <cstdio>
using namespace std;

const int n_max = 40, k_max = 1000000;

struct matrix {
	vector< vector<int> > entries_;
	matrix(int n) : entries_(n, vector<int>(n)) {}
};

int n;
matrix I(n_max); // identity matrix

void add_matrix(matrix& a, matrix& b, matrix& result)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			result.entries_[i][j] = (a.entries_[i][j] + b.entries_[i][j]) % 10;
}

void multiply_matrix(matrix& a, matrix& b, matrix& result)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			int r = 0;
			for (int k = 0; k < n; k++) {
				r += a.entries_[i][k] * b.entries_[k][j] % 10;
				r %= 10;
			}
			result.entries_[i][j] = r;
		}
}

void power_of_matrix(int k, matrix& a, matrix& result)
{
	if (k == 1) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				result.entries_[i][j] = a.entries_[i][j];
	}
	else {
		matrix p(n);
		power_of_matrix(k / 2, a, p);
		if (k & 1) {
			matrix r(n);
			multiply_matrix(p, p, r);
			multiply_matrix(r, a, result);
		}
		else
			multiply_matrix(p, p, result);
	}
}

/*
S(k) = A + A^2 + A^3 + ... + A^k, then
	S(1) = A
	S(k) = S(k / 2) * (I + A^(k / 2)) if n is even
	S(k) = S(k / 2) * (I + A^(k / 2)) + A^k if n is odd
*/

void sum_of_powers(int k, matrix& a, matrix& result)
{
	if (k == 1) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				result.entries_[i][j] = a.entries_[i][j];
	}
	else {
		matrix s(n), p(n), r(n);
		sum_of_powers(k / 2, a, s);
		power_of_matrix(k / 2, a, p);
		add_matrix(I, p, r);
		if (k & 1) { // k is odd
			matrix rr(n);
			multiply_matrix(s, r, rr);
			power_of_matrix(k, a, p);
			add_matrix(rr, p, result);
		}
		else
			multiply_matrix(s, r, result);
	}
}

int main()
{
	for (int i = 0; i < n_max; i++)
		for (int j = 0; j < n_max; j++)
			I.entries_[i][j] = (i == j) ? 1 : 0;
	while (true) {
		int k;
		scanf("%d %d", &n, &k);
		if (!n)
			break;
		matrix a(n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				scanf("%d", &a.entries_[i][j]);
				a.entries_[i][j] %= 10;
			}
		matrix result(n);
		sum_of_powers(k, a, result);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				printf("%d%c", result.entries_[i][j], ((j < n - 1) ? ' ' : '\n'));
		putchar('\n');
	}
	return 0;
}

