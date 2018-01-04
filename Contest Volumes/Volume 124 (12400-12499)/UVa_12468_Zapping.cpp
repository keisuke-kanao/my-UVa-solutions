
/*
	UVa 12468 - Zapping

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_12468_Zapping.cpp
*/

#include <cstdio>

int main()
{
	while (true) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a == -1 && b == -1)
			break;
		int a_to_b = b - a, b_to_a = a - b;
		if (a_to_b < 0)
			a_to_b += 100;
		if (b_to_a < 0)
			b_to_a += 100;
		printf("%d\n", (a_to_b < b_to_a) ? a_to_b : b_to_a);
	}
	return 0;
}

