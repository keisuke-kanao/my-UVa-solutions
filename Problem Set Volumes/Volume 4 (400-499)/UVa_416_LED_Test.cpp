
/*
	UVa 416 - LED Test

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_416_LED_Test.cpp

	from 1995 ACM East Central Regional Contest Problem E
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_EastCen/1995/index.html)
*/

#include <cstdio>

const unsigned char leds[] = {0x7e, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70, 0x7f, 0x7b};
const int n_max = sizeof(leds);

unsigned char s_to_sequence(const char* s)
{
	unsigned char sq = 0, b = 0x40;
	do {
		if (*s++ == 'Y')
			sq |= b;
		b >>= 1;
	} while (b);
	return sq;
}

bool match_sequence(int n, unsigned char sequence[])
{
	for (int ns = n_max; ns >= n; ns--) {
		bool match = true;
		unsigned char not_burned = 0x7f;
		for (int i = 1; i <= n; i++) {
			unsigned char led = leds[ns - i];
			led &= not_burned;
			unsigned char diff = led ^ sequence[i - 1];
			unsigned char db = diff, lb = led;
			for ( ; db; db >>= 1, lb >>= 1)
				if (db & 1 && !(lb & 1))
					break; // no burned-out segments will recover
			if (db) {
				match = false; break;
			}
			not_burned &= ~diff;
		}
		if (match)
			return true;
	}
	return false;
}

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		unsigned char sequence[n_max];
		for (int i = 0; i < n; i++) {
			char s[7 + 1];
			scanf("%s", s);
			sequence[i] = s_to_sequence(s);
		}
		if (match_sequence(n, sequence))
			puts("MATCH");
		else
			puts("MISMATCH");
	}
	return 0;
}

