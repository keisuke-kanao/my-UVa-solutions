
/*
	UVa 11809 - Floating-Point Numbers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11809_Floating-Point_Numbers.cpp
*/

#include <limits>
#include <cstdio>
#include <cmath>
#include<cstring>
using namespace std;

const double epsilon = 1e-6 /* numeric_limits<float>::epsilon() */;

const int M_max = 9, E_max = 30;

struct fp_value {
	double mantissa_;
	int exponent_;
} max_fp_values[M_max + 1][E_max + 1];

int main()
{
	double A[10][31];
    double a,c;
    double x;
    long long B[10][31];
    long long b,d;
    int i,j;
	for (int i = 0; i<= M_max; i++)
		for (int j = 1; j <= E_max; j++) {
			double m = 1.0 - pow(2.0, static_cast<double>(-i - 1)); // mantissa
			int e = (1 << j) - 1; // exponent
/*
	m * 2^e = x * 10^d
	log10(m) + e * log10(2) = log10(x) + d
	since 1 <= x < 10, 0 <= log10(x) < 1, and d is an integer value, then
		d = log10(m) + e * log10(2) - log10(x) = floor(log10(m) + e * log10(2) - log10(x))
	log10(x) = log10(m) + e * log10(2) - d, then
		x = 10^(log10(m) + e * log10(2) - d)
*/
			double x = log10(m) + e * log10(2.0);
			double d = floor(x);
			max_fp_values[i][j].mantissa_ = pow(10.0, x - d);
			max_fp_values[i][j].exponent_ = static_cast<int>(d);
		}
#ifdef DEBUG
	for (int i = 0; i<= M_max; i++)
		for (int j = 1; j <= E_max; j++)
			printf("[%d][%d]: %.15lfe%d%c", i, j, max_fp_values[i][j].mantissa_, max_fp_values[i][j].exponent_,
				((j < E_max) ? ' ' : '\n'));
#endif
	char s[32];
	while (scanf("%s", s) != EOF) {
		if (!strcmp(s, "0e0"))
			break;
		s[17] = ' '; // replace 'e' with ' '
		double m;
		int e;
        sscanf(s,"%lf %d",&m,&e);
		bool found = false;
		for (int i = 0; i <= M_max && !found; i++)
			for (int j = 1; j <= E_max && !found; j++)
				if (fabs(m - max_fp_values[i][j].mantissa_) < epsilon && e == max_fp_values[i][j].exponent_) {
					found = true;
					printf("%d %d\n", i, j);
				}
	}
	return 0;
}

