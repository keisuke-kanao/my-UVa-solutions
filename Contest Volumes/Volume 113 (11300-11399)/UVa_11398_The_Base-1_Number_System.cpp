
/*
	UVa 11398 - The Base-1 Number System

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11398_The_Base-1_Number_System.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	const int nr_digits_max = 32;
	char s[nr_digits_max + 1], t[nr_digits_max + 1];
	while (true) {
		scanf("%s", s);
		if (s[0] == '~')
			break;
		char flag = 0, *p = t;
		do {
			int length = strlen(s);
			if (length == 1)
				flag = '1';
			else if (length == 2)
				flag = '0';
			else if (flag) {
				length -= 2;
				memset(p, flag, length);
				p += length;
			}
			scanf("%s", s);
		} while (s[0] != '#');
		*p = '\0';
		int n = 0;
		for (p = t; *p; p++) {
			n <<= 1;
			n += *p - '0';
		}
		printf("%d\n", n);
	}
	return 0;
}

