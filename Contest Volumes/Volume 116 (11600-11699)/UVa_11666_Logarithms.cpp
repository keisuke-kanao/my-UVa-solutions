
/*
	UVa 11666 - Logarithms

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11666_Logarithms.cpp
*/

#include <cstdio>
#include <cmath>
#include <climits>

/*
	n / exp(L) = 1 - abs(x) < 1
	if x >= 0
		n / exp(L) = 1 - x < 1
	else if x < 0
		n / exp(L) = 1 - x > 1
	else
		n / exp(L) = 1
*/

int main()
{
	const int L_max = 21 /* static_cast<int>(log(static_cast<double>(INT_MAX))) */;
	double exp_Ls[L_max + 1];
	for (int i = 0; i <= L_max; i++)
		exp_Ls[i] = exp(static_cast<double>(i));
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		for (int L = 0; L <= L_max; L++) {
			double x = 1.0 - n / exp_Ls[L];
			if (fabs(x) < 1.0 &&
				(n < exp_Ls[L] && x > 0.0 || n > exp_Ls[L] && x < 0.0 || n == exp_Ls[L] && x == 0.0)) {
				printf("%d %.8lf\n", L, x);
				break;
			}
		}
	}
	return 0;
}

