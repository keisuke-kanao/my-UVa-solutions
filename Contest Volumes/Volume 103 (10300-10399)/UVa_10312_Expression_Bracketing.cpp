
/*
	UVa 10312 - Expression Bracketing

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10312_Expression_Bracketing.cpp
*/

#include <cstdio>

const int n_max = 26;
long long cns[n_max + 1] = { // catalan numbers
	1,
	1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796,
	58786, 208012, 742900, 2674440, 9694845, 35357670, 129644790, 477638700, 1767263190, 6564120420,
	24466267020, 91482563640, 343059613650, 1289904147324, 4861946401452, 18367353072152
};

long long scns[n_max + 1] = { // super catalan numbers
	0,
	1, 1, 3, 11, 45, 197, 903, 4279, 20793, 103049,
	518859, 2646723, 13648869, 71039373, 372693519, 1968801519, 10463578353, 55909013009, 300159426963, 1618362158587,
	8759309660445, 47574827600981, 259215937709463, 1416461675464871, 7760733824437545, 42624971294485657
};
/*
	scns[1] = scns[2] = 1;
	for (int i = 3; i <= n_max; i++)
		scns[i] = (3 * (2 * i - 3) * scns[i - 1] - (i - 3) * scns[i - 2]) / i;
*/

int main()
{
/*
	The number of bracketings on n letters is given by the super catalan number of n.
	The number of binary bracketings of n letters is given by the catalan number of (n - 1).
*/
	int n;
	while (scanf("%d", &n) != EOF)
		printf("%lld\n", scns[n] - cns[n - 1]);
	return 0;
}

