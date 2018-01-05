
/*
	UVa 11296 - Counting Solutions to an Integral Equation

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11296_Counting_Solutions_to_an_Integral_Equation.cpp
*/

#include <cstdio>

int main()
{
	int n;
	while (scanf("%d", &n) != EOF) {
		long long m = (n + 2) / 2;
		printf("%lld\n", m * (m + 1) / 2);
	}
	return 0;
}

