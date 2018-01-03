
/*
	UVa 1209 - Wordfish

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1209_Wordfish.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int nr_passwords = 21, nr_letters = 26, nr_chars_max = 20;

int main()
{
	char p[nr_chars_max + 1], passwords[nr_passwords][nr_chars_max + 1];
	while (scanf("%s", p) != EOF) {
		int n = strlen(p), i = nr_passwords / 2, psi, pei;
		strcpy(passwords[i], p);
		for (i++; i < nr_passwords && next_permutation(p, p + n); i++)
			strcpy(passwords[i], p);
		pei = i;
		i = nr_passwords / 2;
		strcpy(p, passwords[i]);
		for (i--; i >= 0 && prev_permutation(p, p + n); i--)
			strcpy(passwords[i], p);
		psi = i + 1;
#ifdef DEBUG
		for (i = psi; i < pei; i++)
			printf("%s, ", passwords[i]);
		putchar('\n');
#endif
		int max_min_d = 0, max_min_d_i;
		for (i = psi; i < pei; i++) {
			int min_d = nr_letters;
			char (&pp)[nr_chars_max + 1] = passwords[i];
			for (int j = 0; j < n - 1; j++)
				min_d = min(min_d, abs(pp[j + 1] - pp[j]));
#ifdef DEBUG
			printf("%s %d\n", passwords[i], min_d);
#endif
			if (min_d > max_min_d) {
				max_min_d = min_d;
				max_min_d_i = i;
			}
		}
		printf("%s%d\n", passwords[max_min_d_i], max_min_d);
	}
	return 0;
}

