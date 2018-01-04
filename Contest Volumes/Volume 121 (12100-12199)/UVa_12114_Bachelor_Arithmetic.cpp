
/*
	UVa 12114 - Bachelor Arithmetic

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12114_Bachelor_Arithmetic.cpp
*/

#include <cstdio>

int main()
{
	for (int cn = 1; ; cn++) {
		int B, S;
		scanf("%d %d", &B, &S);
		if (!B && !S)
			break;
		printf("Case %d: ", cn);
		if (B == 1)
			puts(":-\\");
		else if (S >= B)
			puts(":-|");
		else {
			long long b = static_cast<long long>(B), s = static_cast<long long>(S);
			long long d = b * (s - 1) - (b - 1) * s;
			if (d > 0)
				puts(":-)");
			else if (d < 0)
				puts(":-(");
			else
				puts(":-|");
		}
	}
	return 0;
}

