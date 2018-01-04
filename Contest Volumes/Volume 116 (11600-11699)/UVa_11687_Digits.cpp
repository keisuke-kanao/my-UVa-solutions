
/*
	UVa 11687 - Digits

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11687_Digits.cpp
*/

const int nr_digits_max = 1000000;
char x0[nr_digits_max + 1];

#include <cstdio>
#include <cstring>
#include <cmath>

int main()
{
	while (true) {
		scanf("%s", x0);
		if (x0[0] == 'E')
			break;
		int x = strlen(x0);
		int i = 1;
		if (x > 1 || x0[0] != '1') {
			if (x > 1)
				i++;
			do
				i++;
			while ((x = static_cast<int>(log10(static_cast<double>(x)))) > 0);
		}
		printf("%d\n", i);
	}
	return 0;
}

