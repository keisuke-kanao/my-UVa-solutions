
/*
	UVa 11713 - Abstract Names

	To build using Visual Studio 2008:
		cl -EHsc UVa_11713_Abstract_Names.cpp
*/

#include <cstdio>

bool is_same_name(const char* s, const char* t)
{
// Two names are considered same if they are of same length and they only vary at positions where vowels occur.
	for ( ; *s && *t; s++, t++) {
		char sc = *s, tc = *t;
		if (sc == 'a' || sc == 'e' || sc == 'i' || sc == 'o' || sc == 'u') { // vowels
			if (tc == 'a' || tc == 'e' || tc == 'i' || tc == 'o' || tc == 'u')
				;
			else
				return false;
		}
		else if (sc != tc)
			return false;
	}
	return (*s || *t) ? false : true;
}

int main()
{
	int n;
	scanf("%d", &n);
	getchar();
	while (n--) {
		const int nr_chars_max = 20;
		char s[nr_chars_max + 1], t[nr_chars_max + 1];
		gets(s);
		gets(t);
		printf("%s\n", (is_same_name(s, t) ? "Yes" : "No"));
	}
	return 0;
}

