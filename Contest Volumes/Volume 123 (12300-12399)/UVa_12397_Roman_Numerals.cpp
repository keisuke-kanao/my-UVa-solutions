
/*
	UVa 12397 - Roman Numerals

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12397_Roman_Numerals.cpp

	This problem is similar to 11616 - Roman Numerals.
*/

#include <cstdio>

int parse_numbers(int n)
{
	// I: 1, V: 2, X: 2, L: 2, C: 2, D: 3, M: 4
	int d, s = 0;
	for ( ; n >= 1000; n -= 1000)
		s += 4; // M
	if (n >= 100) {
		d = n / 100;
		if (d == 9)
			s += 6; // CM
		else if (d >= 5) {
			s += 3; // D
			for (d -= 5; d; d--)
				s += 2; // C
		}
		else if (d == 4)
			s += 5; // CD
		else {
			for ( ; d; d--)
				s += 2; // C
		}
		n %= 100;
	}
	if (n >= 10) {
		d = n / 10;
		if (d == 9)
			s += 4; // XC
		else if (d >= 5) {
			s += 2; // L
			for (d -= 5; d; d--)
				s += 2; // X
		}
		else if (d == 4)
			s += 4; // XL
		else {
			for ( ; d; d--)
				s += 2; // X
		}
		n %= 10;
	}
	if (n == 9)
		s += 3; // IX
	else if (n >= 5) {
		s += 2; // V
		for (n -= 5; n; n--)
			s++; // I;
	}
	else if (n == 4)
		s += 3; // IV
	else {
		for ( ; n; n--)
			s++; // I
	}
	return s;
}

int main()
{
	int N;
	while (scanf("%d", &N) != EOF)
		printf("%d\n", parse_numbers(N));
	return 0;
}

