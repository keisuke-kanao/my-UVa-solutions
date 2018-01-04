
/*
	UVa 11714 - Blind Sorting

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11714_Blind_Sorting.cpp
*/

#include <cstdio>
#include <cmath>

/*
Find the 2nd largest element in an array with minimum # of comparisom
  http://stackoverflow.com/questions/3628718/find-the-2nd-largest-element-in-an-array-with-minimum-of-comparisom
Lower bound for finding second largest element
  http://math.stackexchange.com/questions/1601/lower-bound-for-finding-second-largest-element
*/

int main()
{
	long long n;
	while (scanf("%lld", &n) != EOF)
		printf("%lld\n", n + static_cast<long long>(ceil(log2(static_cast<double>(n)))) - 2);
	return 0;
}

