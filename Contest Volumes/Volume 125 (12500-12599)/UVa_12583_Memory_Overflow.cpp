
/*
	UVa 12583 - Memory Overflow

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12583_Memory_Overflow.cpp
*/

#include <cstdio>

int main()
{
	int t;
	scanf("%d", &t);
	for (int cn = 1; cn <= t; cn++) {
		int n, k;
		const int n_max = 500;
		char names[n_max + 1];
		scanf("%d %d %s", &n, &k, names);
		int rc = 0;
		for (int i = 1; i < n; i++) {
			int j = i - k;
			if (j < 0)
				j = 0;
			for ( ; j < i; j++)
				if (names[i] == names[j]) {
					rc++; break;
				}
		}
		printf("Case %d: %d\n", cn, rc);
	}
	return 0;
}

