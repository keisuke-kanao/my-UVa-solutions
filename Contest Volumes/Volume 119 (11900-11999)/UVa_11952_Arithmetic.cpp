
/*
	UVa 11952 - Arithmetic

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11952_Arithmetic.cpp
*/

#include <cstdio>

int base_one_number(const char* s)
{
	int length = 0;
	for ( ; *s; s++, length++)
		if (*s != '1')
			return -1;
	return length;
}

int number(const char* s, int base)
{
	int n = 0;
	for ( ; *s; *s++) {
		int d = *s - '0';
		if (d >= base)
			return -1;
		n *= base;
		n += d;
	}
	return n;
}

int main()
{
	int N;
	scanf("%d", &N);
	while (N--) {
		const int nr_chars_max = 7;
		char A[nr_chars_max + 1], B[nr_chars_max + 1], C[nr_chars_max + 1];
		scanf("%s%*s%s%*s%s", A, B, C);
		int a, b, c, base = 0;
		if ((a = base_one_number(A)) != -1 && (b = base_one_number(B)) != -1 &&
			(c = base_one_number(C)) != -1 && a + b == c)
			base = 1;
		if (!base) {
			for (int bs = 2; bs <= 18; bs++)
				if ((a = number(A, bs)) != -1 && (b = number(B, bs)) != -1 &&
					(c = number(C, bs)) != -1 && a + b == c) {
					base = bs; break;
				}
		}
		printf("%d\n", base);
	}
	return 0;
}

/*
SAMPLE INPUT

4
155 + 102 = 301
1022 + 221 = 1303
6502 + 6800 = 11202
515 + 7 = 522

SAMPLE OUTPUT

6
4
0
10
*/

