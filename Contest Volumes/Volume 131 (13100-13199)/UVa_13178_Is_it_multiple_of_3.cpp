
/*
	UVa 13178 Is it multiple of 3?

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_13178_Is_it_multiple_of_3.cpp
*/

#include <cstdio>

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		int n;
		scanf("%d", &n);
		long long s = static_cast<long long>(n) * (n + 1) / 2;
		puts((s % 3) ? "NO" : "YES");
	}
	return 0;
}

