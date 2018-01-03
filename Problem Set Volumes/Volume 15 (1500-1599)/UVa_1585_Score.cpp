
/*
	UVa 1585 - Score

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1585_Score.cpp
*/

#include <cstdio>

int main()
{
	const int nr_chars_max = 80;
	char s[nr_chars_max + 1];
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%s", s);
		int ss = 0, ps = 0;
		for (const char* p = s; *p; p++) {
			if (*p == 'O') {
				ps++;
				ss += ps;
			}
			else
				ps = 0;
		}
		printf("%d\n", ss);
	}
	return 0;
}

