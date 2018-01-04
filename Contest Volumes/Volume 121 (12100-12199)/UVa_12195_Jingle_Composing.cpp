
/*
	UVa 12195 - Jingle Composing

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12195_Jingle_Composing.cpp
*/

#include <cstdio>

int main()
{
	const int nr_letters = 26, durations_per_measure = 64;
	int durations[nr_letters]; // durations[i] is the durations of identifier i
	durations['W' - 'A'] = durations_per_measure / 1;
	durations['H' - 'A'] = durations_per_measure / 2;
	durations['Q' - 'A'] = durations_per_measure / 4;
	durations['E' - 'A'] = durations_per_measure / 8;
	durations['S' - 'A'] = durations_per_measure / 16;
	durations['T' - 'A'] = durations_per_measure / 32;
	durations['X' - 'A'] = durations_per_measure / 64;

	const int nr_chars_max = 200;
	char s[nr_chars_max + 1];
	while (true) {
		scanf("%s", s);
		if (s[0] == '*')
			break;
		int nr = 0, d = 0;
		for (const char* p = s + 1; *p; p++) {
			if (*p == '/') {
				if (d == durations_per_measure)
					nr++;
				d = 0;
			}
			else
				d += durations[*p - 'A'];
		}
		printf("%d\n", nr);
	}
	return 0;
}

