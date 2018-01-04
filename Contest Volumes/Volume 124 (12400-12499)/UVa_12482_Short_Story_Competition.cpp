
/*
	UVa 12482 - Short Story Competition

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12482_Short_Story_Competition.cpp
*/

#include <cstdio>

const int N_max = 1000, C_max = 70;
char s[N_max * (C_max + 1)];

int main()
{
	int N, L, C;
	while (scanf("%d %d %d", &N, &L, &C) != EOF) {
		while (getchar() != '\n')
			;
		gets(s);
		if (!s[0]) {
			puts("0");
			continue;
		}
		int l = 1, c = 0, d;
		char *p = s, *q = p;
		while (true) {
			while (*p && *p != ' ')
				p++;
			d = p - q;
			if (!*p)
				break;
			if (c + d == C) {
				l++, c = 0;
#ifdef DEBUG
				*p = '\n';
#endif
				p++;
			}
			else {
				p++, d++;
				if (c + d > C) {
					l++, c = p - q;
#ifdef DEBUG
					*(q - 1) = '\n';
#endif
				}
				else if (c + d == C) {
					l++, c = 0;
#ifdef DEBUG
					*(p - 1) = '\n';
#endif
				}
				else
					c += d;
			}
			q = p;
		}
		if (c + d > C)
			l++;
#ifdef DEBUG
		puts(s);
#endif
		printf("%d\n", (l + L - 1) / L);
	}
	return 0;
}

