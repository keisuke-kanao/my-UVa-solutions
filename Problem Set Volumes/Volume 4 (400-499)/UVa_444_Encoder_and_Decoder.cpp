
/*
	UVa 444 - Encoder and Decoder

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_444_Encoder_and_Decoder.cpp
*/

#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

int main()
{
	const int nr_chars_max = 256;
	char s[nr_chars_max], t[nr_chars_max];
	while (gets(s)) {
		int length = strlen(s);
		if (isdigit(s[0])) { // encoded message
			int si = length - 1, ti = 0;
			while (si > 0) {
				char c = s[si--] - '0';
				if (c == 1) {
					c *= 100;
					c += (s[si--] - '0') * 10;
				}
				else
					c *= 10;
				c += s[si--] - '0';
				t[ti++] = c;
			}
			t[ti] = '\0';
			printf("%s\n", t);
		}
		else { // normal message
			int si = 0, ti = nr_chars_max - 1;
			t[ti--] = '\0';
			while (s[si]) {
				char c = s[si++];
				if (c >= 100) {
					c -= 100;
					t[ti--] = '1';
				}
				t[ti--] = c / 10 + '0';
				t[ti--] = c % 10 + '0';
			}
			printf("%s\n", &t[ti + 1]);
		}
	}
	return 0;
}

