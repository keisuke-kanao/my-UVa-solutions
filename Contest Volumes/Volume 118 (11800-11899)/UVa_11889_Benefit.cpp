
/*
	UVa 11889 - Benefit

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11889_Benefit.cpp
*/

#include <cstdio>

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int A, C;
		scanf("%d %d", &A, &C);
		if (C % A)
			puts("NO SOLUTION");
		else { 
			int B = C / A;
			for (int i = B; B <= C; B += i)
				if (B / gcd(A, B) == i)
					break;
			printf("%d\n", B);
		}
	}
	return 0;
}

