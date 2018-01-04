
/*
	UVa 12893 - Count It

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_12893_Count_It.cpp
*/

#include <cstdio>

long long count_it(long long n)
{
	if (!n)
		return 0;
	long long cn = count_it(n / 2);
	if (n & 1)
		cn++;
	return cn;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		long long n;
		scanf("%lld", &n);
		printf("%lld\n", count_it(n));
	}
	return 0;
}

