
/*
	UVa 12085 - Mobile Casanova

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12085_Mobile_Casanova.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int N;
		scanf("%d", &N);
		if (!N)
			break;
		printf("Case %d:\n", case_nr);
		const int nr_chars_max = 15;
		char ss[nr_chars_max + 1], es[nr_chars_max + 1], s[nr_chars_max + 1];
		scanf("%s", ss);
		strcpy(es, ss);
		int sn = atoi(ss), en = sn, n;
		while (--N) {
			scanf("%s", s);
			n = atoi(s);
			if (n != en + 1) {
				const char *pss = ss, *pes = es;
				for ( ; *pss && *pss == *pes; pss++, pes++)
					;
				if (*pes)
					printf("%s-%s\n", ss, pes);
				else
					printf("%s\n", ss);
				strcpy(ss, s);
				strcpy(es, s);
				sn = en = n;
			}
			else {
				strcpy(es, s);
				en = n;
			}
		}
		const char *pss = ss, *pes = es;
		for ( ; *pss && *pss == *pes; pss++, pes++)
			;
		if (*pes)
			printf("%s-%s\n", ss, pes);
		else
			printf("%s\n", ss);
		putchar('\n');
	}
	return 0;
}

