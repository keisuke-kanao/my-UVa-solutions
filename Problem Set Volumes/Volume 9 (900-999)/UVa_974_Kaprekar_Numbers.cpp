
/*
	UVa 974 - Kaprekar Numbers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_974_Kaprekar_Numbers.cpp
*/

#include <cstdio>

const int nr_kaprekar_numbers_max = 40000;
bool kaprekar_numbers[nr_kaprekar_numbers_max + 1];

bool is_kaprekar_number(int n)
{
	int ns = n * n;
	int i = ns, j = 0, k = 1, l;
	while (true) {
		l = i % 10;
		i /= 10;
		if (!i)
			break;
		j += k * l;
		if (j && i + j == n)
			return true;
		k *= 10;
	}
	return false;
}

int main()
{
	for (int i = 2; i <= nr_kaprekar_numbers_max; i++)
		if (is_kaprekar_number(i))
			kaprekar_numbers[i] = true;
	int n;
	scanf("%d", &n);
	for (int cn = 1; cn <= n; cn++) {
		int inf, sup;
		scanf("%d %d", &inf, &sup);
		printf("case #%d\n", cn);
		bool printed = false;
		for (int i = inf; i <= sup; i++)
			if (kaprekar_numbers[i]) {
				printed = true;
				printf("%d\n", i);
			}
		if (!printed)
			puts("no kaprekar numbers");
		if (cn < n)
			putchar('\n');
	}
	return 0;
}

