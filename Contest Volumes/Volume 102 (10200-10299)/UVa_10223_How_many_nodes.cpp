
/*
	UVa 10223 - How many nodes ?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10223_How_many_nodes.cpp
*/

/*
	The possible number of binary search trees that can be created with n nodes is given by the n-th Catalan number.
*/

#include <cstdio>
#include <cstdlib>
using namespace std;

const long long catalan_numbers[] = { // catalan_numbers[i] is i-th Catalan number
	1, 1, 2, 5, 14, 42, 132, 429,
	1430, 4862, 16796, 58786, 208012, 742900, 2674440, 9694845,
	35357670, 129644790, 477638700, 1767263190, 6564120420
};

int compare_long_long(const void* i, const void* j)
{
	return *reinterpret_cast<const long long*>(i) - *reinterpret_cast<const long long*>(j);
}

int main()
{
	long long n;
	while (scanf("%lld", &n) != EOF) {
		long long* p = reinterpret_cast<long long*>(bsearch(&n, catalan_numbers, sizeof(catalan_numbers) / sizeof(long long),
			sizeof(long long), compare_long_long));
		printf("%d\n", p - catalan_numbers);
	}
	return 0;
}

