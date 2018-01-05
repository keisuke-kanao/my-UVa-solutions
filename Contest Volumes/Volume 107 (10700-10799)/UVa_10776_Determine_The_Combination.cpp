
/*
	UVa 10776 - Determine The Combination

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10776_Determine_The_Combination.cpp
*/

#include <cstdio>
#include <cstring>
using namespace std;

// Instead of working with the sorted string, work with frequencies of each letter, and always generate words in nondecreasing order.

const int nr_letters = 26, nr_chars_max = 30;
int frequencies[nr_letters]; // frequencies[i] is the frequency of 'a' + i
int rfrequencies[nr_letters]; // rfrequencies[i] is the sum of frequencies from i to 'z'

void generate_combination_strings(int r, int fi, int si, char* s)
{
	if (si == r)
		puts(s);
	else if (fi < nr_letters && r - si <= rfrequencies[fi]) {
		if (frequencies[fi]) {
			char c = 'a' + fi;
			int i;
			for (i = 0; i < r - si && i < frequencies[fi]; i++)
				s[si + i] = c;
			for (i--; i >= 0; i--)
				generate_combination_strings(r, fi + 1, si + i + 1, s);
		}
		generate_combination_strings(r, fi + 1, si, s);
	}
}

int main()
{
	char s[nr_chars_max + 1];
	int r;
	while (scanf("%s %d", s, &r) != EOF) {
		memset(frequencies, 0, sizeof(frequencies));
		for (const char* p = s; *p; p++)
			frequencies[*p - 'a']++;
		for (int i = nr_letters - 1, rs = 0; i >= 0; i--) {
			rs += frequencies[i];
			rfrequencies[i] = rs;
		}
		s[r] = '\0';
		generate_combination_strings(r, 0, 0, s);
	}
	return 0;
}

