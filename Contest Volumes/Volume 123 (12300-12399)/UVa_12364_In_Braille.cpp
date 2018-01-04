
/*
	UVa 12364 - In Braille

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12364_In_Braille.cpp
*/

#include <cstdio>

const int nr_digits = '9' - '0' + 1, D_max = 100, nr_braille_lines = 3, nr_braille_chars = D_max * 3;
char digits[D_max + 1], braille[nr_braille_lines][nr_braille_chars];

const char* braille_numbers[nr_digits][nr_braille_lines] = {
	{".*", "**", ".."},
	{"*.", "..", ".."},
	{"*.", "*.", ".."},
	{"**", "..", ".."},
	{"**", ".*", ".."},
	{"*.", ".*", ".."},
	{"**", "*.", ".."},
	{"**", "**", ".."},
	{"*.", "**", ".."},
	{".*", "*.", ".."}
};

int braille_to_number(int bi)
{
	for (int n = 0; n < nr_digits; n++) {
		const char** b = braille_numbers[n];
		if (braille[0][bi] == b[0][0] && braille[0][bi + 1] == b[0][1] &&
			braille[1][bi] == b[1][0] && braille[1][bi + 1] == b[1][1])
			return n;
	}
	return -1;
}

int main()
{
	while (true) {
		int D;
		scanf("%d", &D);
		if (!D)
			break;
		getchar();
		char sb[8];
		gets(sb);
		if (sb[0] == 'S') {
			gets(digits);
			for (int i = 0, k = 0; i < D; i++, k += 3) {
				const char** b = braille_numbers[digits[i] - '0'];
				for (int j = 0; j < nr_braille_lines; j++) {
					braille[j][k] = b[j][0], braille[j][k + 1] = b[j][1];
					braille[j][k + 2] = (i < D - 1) ? ' ' : '\0';
				}
			}
			for (int i = 0; i < nr_braille_lines; i++)
				puts(braille[i]);
		}
		else {
			for (int i = 0; i < nr_braille_lines; i++)
				gets(braille[i]);
			for (int i = 0, j = 0; i < D; i++, j += 3)
				digits[i] = braille_to_number(j) + '0';
			digits[D] = '\0';
			puts(digits);
		}
	}
	return 0;
}

