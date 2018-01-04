
/*
	UVa 11965 - Extra Spaces

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11965_Extra_Spaces.cpp
*/

#include <cstdio>
#include <cctype>

int main()
{
	int t;
	scanf("%d", &t);
	getchar();
	for (int cn = 1; cn <= t; cn++) {
		printf("Case %d:\n", cn);
		int n;
		scanf("%d", &n);
		getchar();
		while (n--) {
			const int nr_chars_max = 500;
			char s[nr_chars_max + 1], t[nr_chars_max + 1];
			gets(s);
			bool in_spaces = false;
			char* q = t;
			for (const char *p = s; *p; p++) {
				if (in_spaces) {
					if (!isspace(*p)) {
						in_spaces = false;
						*q++ = *p;
					}
				}
				else {
					if (isspace(*p)) {
						in_spaces = true;
						*q++ = ' ';
					}
					else
						*q++ = *p;
				}
			}
			*q = '\0';
			puts(t);
		}
		if (cn < t)
			putchar('\n');
	}
	return 0;
}

