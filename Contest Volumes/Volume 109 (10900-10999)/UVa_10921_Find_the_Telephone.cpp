
/*
	UVa 10921 - Find the Telephone

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10921_Find_the_Telephone.cpp
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
		for (char* p = s; *p; p++) {
			char c = *p;
			if (isalpha(c)) {
				switch (c) {
				case 'A': case 'B': case 'C':
					c = '2'; break;
				case 'D': case 'E': case 'F':
					c = '3'; break;	
				case 'G': case 'H' : case 'I':
					c = '4'; break;
				case 'J': case 'K': case 'L':
					c = '5'; break;
				case 'M': case 'N': case 'O':
					c = '6'; break;
				case 'P': case 'Q': case 'R': case 'S':
					c = '7'; break;
				case 'T': case 'U': case 'V':
					c = '8'; break;
				default: // WXYZ
					c = '9'; break;
				}
				*p = c;
			}
		}
		puts(s);
	}
	return 0;
}

