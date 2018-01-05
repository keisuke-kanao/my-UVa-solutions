
/*
	UVa 11058 - Encoding

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11058_Encoding.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	const int nr_chars = 128, nr_letters = 'z' - 'a' + 1, S_max = 100;
	for (int N = 1; ; N++) {
		char S[S_max + 1], s[S_max + 1];
		if (scanf("%s", S) == EOF)
			break;
		char replacements[nr_chars];
		for (int i = 0; i < nr_letters; i++) {
			char c;
			scanf("%s", &c);
			replacements['a' + i] = c;
		}
		char *p, *q;
		for (p = S, q = s; *p; p++, q++)
			*q = replacements[*p];
		*q = '\0';
#ifdef DEBUG
		printf("%s\n", s);
#endif
		int R;
		scanf("%d", &R);
		while (R--) {
			int P;
			char X, Y;
			scanf("%d %c %c", &P, &X, &Y);
			for (p = S + P, q = s + P; *p; p++, q++)
				if (*p == X)
					*q = Y;
		}
		printf("Case #%d: The encoding string is %s.\n\n", N, s);
	}
	return 0;
}

