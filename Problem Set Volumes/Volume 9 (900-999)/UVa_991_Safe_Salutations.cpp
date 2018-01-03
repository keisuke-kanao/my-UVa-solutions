
/*
	UVa 991 - Safe Salutations

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_991_Safe_Salutations.cpp
*/

#include <cstdio>

const int catalan_numbers[] = { // catalan_numbers[i] is i-th Catalan number
	1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796
};

int main()
{
	bool printed = false;
	int n;
	while (scanf("%d", &n) != EOF) {
		if (printed)
			putchar('\n');
		else
			printed = true;
		printf("%d\n", catalan_numbers[n]);
	}
	return 0;
}

