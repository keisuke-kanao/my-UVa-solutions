
/*
	UVa 865 - Substitution Cypher

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_865_Substitution_Cypher.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	int n;
	scanf("%d", &n);
	getchar();
	getchar();
	const int nr_chars_max = 64, nr_substitution_chars = 128;
	char p[nr_chars_max + 1], s[nr_chars_max + 1], t[nr_chars_max + 1];
	char substitutions[nr_substitution_chars];
	while (n--) {
		gets(p);
		gets(s);
		memset(substitutions, 0, sizeof(substitutions));
		for (const char *pp = p, *ps = s; *pp; pp++, ps++)
			substitutions[*pp] = *ps;
		puts(s);
		puts(p);
		while (gets(t) && t[0]) {
			for (char* pt = t; *pt; pt++)
				if (substitutions[*pt])
					*pt = substitutions[*pt];
			puts(t);
		}
		if (n)
			putchar('\n');
	}
	return 0;
}

