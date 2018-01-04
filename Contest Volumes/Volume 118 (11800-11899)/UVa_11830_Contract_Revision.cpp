
/*
	UVa 11830 - Contract Revision

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11830_Contract_Revision.cpp
*/

#include <cstdio>

const char* skip_zero_digits(const char* s)
{
	for ( ; *s; s++)
		if (*s != '0')
			return s;
	return NULL;
}

int main()
{
	const int nr_digits_max = 100;
	while (true) {
		int d;
		char s[nr_digits_max + 1], t[nr_digits_max + 1];
		scanf("%d %s", &d, s);
		if (!d && !skip_zero_digits(s))
			break;
		char cd = d + '0';
		char* pt = t;
		for (const char* ps = s; *ps; ps++)
			if (*ps != cd)
				*pt++ = *ps;
		*pt = '\0';
		const char* p = skip_zero_digits(t);
		if (p)
			puts(p);
		else
			puts("0");
	}
	return 0;
}

