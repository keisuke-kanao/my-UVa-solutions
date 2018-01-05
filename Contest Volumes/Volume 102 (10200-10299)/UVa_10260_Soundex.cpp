
/*
	UVa 10260 - Soundex

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10260_Soundex.cpp
*/

#include <iostream>
#include <cstdio>
#include <cctype>
using namespace std;

int main()
{
	const int nr_chars_max = 32;
	char s[nr_chars_max];
	while (gets(s)) {
		char pc = 0, t[nr_chars_max];
		char* q = t;
		for (const char*p = s; *p; p++) {
			char c;
			switch (*p) {
			case 'B': case 'F': case 'P': case 'V':
				c = '1'; break;
			case 'C': case 'G': case 'J': case 'K': case 'Q': case 'S': case 'X': case 'Z':
				c = '2'; break;
			case 'D': case 'T':
				c = '3'; break;
			case 'L':
				c = '4'; break;
			case 'M': case 'N':
				c = '5'; break;
			case 'R':
				c = '6'; break;
			default:
				c = 0; break;
			}
			if (c && c != pc)
				*q++ = c;
			pc = c;
		}
		*q = '\0';
		puts(t);
	}
	return 0;
}

