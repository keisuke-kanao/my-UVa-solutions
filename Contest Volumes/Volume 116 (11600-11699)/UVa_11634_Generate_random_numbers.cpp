
/*
	UVa 11634 - Generate random numbers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11634_Generate_random_numbers.cpp
*/

#include <cstdio>
#include <cstring>

const int a0_max = 10000 - 1;
bool numbers[a0_max + 1]; // numbers[i] is true if i has already been produced

int main()
{
	while (true) {
		int a;
		scanf("%d", &a);
		if (!a)
			break;
		memset(numbers, 0, sizeof(numbers));
		int nr = 0;
		while (true) {
			if (numbers[a])
				break;
			numbers[a] = true;
			a *= a;
			a /= 100;
			a %= 10000;
			nr++;
		}
		printf("%d\n", nr);
	}
	return 0;
}

