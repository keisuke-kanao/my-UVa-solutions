
/*
	UVa 12414 - Calculating Yuan Fen

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12414_Calculating_Yuan_Fen.cpp
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int nr_letters_max = 10, st_max = 10000, nr_chars_max = 127;
char previous[nr_chars_max + 1], current[nr_chars_max + 1];

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	char s[nr_letters_max + 1];
	while (scanf("%s", s) != EOF) {
		int st, n, length = strlen(s);
		bool found = false;
		for (st = 1; st <= st_max; st++) {
			char* p = &previous[nr_chars_max];
			for (int i = length - 1; i >= 0; i--) {
				n = st + s[i] - 'A';
				do {
					*--p = '0' + n % 10;
					n /= 10;
				} while (n);
			}
#ifdef DEBUG
			printf("%s\n", p);
#endif
			char *ps = p, *cs = current, *pp, *cp;
			while (true) {
				for (pp = ps + 1, cp = cs; *pp; *pp++, *cp++)
					*cp = (*(pp - 1) - '0' + *pp - '0') % 10 + '0';
				*cp = '\0';
#ifdef DEBUG
				printf("%s\n", cs);
#endif
				if (cp - cs == 3 && cs[0] == '1' && cs[1] == '0' && cs[2] == '0') {
					found = true; break;
				}
				else if (cp - cs < 3)
					break;
				swap(ps, cs);
			}
			if (found)
				break;
		}
		if (found)
			printf("%d\n", st);
		else
			puts(":(");
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

