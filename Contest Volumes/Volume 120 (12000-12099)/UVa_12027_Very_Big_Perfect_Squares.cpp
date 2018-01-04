
/*
	UVa 12027 - Very Big Perfect Squares

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12027_Very_Big_Perfect_Squares.cpp
*/

#include <cstdio>
#include <cstring>
#include <cmath>

int main()
{
	const int sqrts[] = {
		0,
		1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
	};
	while (true) {
		const int nr_digits_max = 1001;
		char N[nr_digits_max + 1], A[nr_digits_max + 1];
		scanf("%s", N);
		if (N[0] == '0')
			break;
		int nr_digits = strlen(N), nr_zeros = (nr_digits - 1) / 2, n = N[0] - '0';
		if (!(nr_digits & 1)) {
			n *= 10;
			n += N[1] - '0';
		}
		A[0] = sqrts[n] + '0';
		memset(A + 1, '0', nr_zeros);
		A[nr_zeros + 1] = '\0';
		puts(A);
	}
	return 0;
}

