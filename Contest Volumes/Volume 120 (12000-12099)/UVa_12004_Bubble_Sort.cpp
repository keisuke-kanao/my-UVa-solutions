
/*
	UVa 12004 - Bubble Sort

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12004_Bubble_Sort.cpp
*/

#include <cstdio>

int main()
{
	// expected number of swaps performed by bubblesort = n * (n - 1) / 4
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		long long n;
		scanf("%lld", &n);
		n *= n - 1;
		printf("Case %d: ", t);
		if (!(n % 4))
			printf("%lld\n", n / 4);
		else if (!(n % 2))
			printf("%lld/2\n", n / 2);
		else
			printf("%lld/4\n", n);
	}
	return 0;
}

/*
Sample Input

2
1
2


Sample Output

Case 1: 0
Case 2: 1/2

*/

