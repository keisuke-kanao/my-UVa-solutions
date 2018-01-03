
/*
	UVa 741 - Burrows Wheeler Decoder

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_741_Burrows_Wheeler_Decoder.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
	const int nr_chars_max = 300;
	char d[nr_chars_max + 1], s[nr_chars_max + 1], t[nr_chars_max + 1];
	bool printed = false;
	while (true) {
		int di;
		scanf("%s%d", d, &di);
		if (!strcmp(d, "END") && !di)
			break;
		if (printed)
			putchar('\n');
		di--;
		int length = strlen(d);
		strcpy(s, d);
		sort(s, s + length);
		t[0] = s[di];
#ifdef DEBUG
		printf("%c ", s[di]);
#endif
		int pi;
		for (pi = 0, di--; di >= 0 && s[di] == t[0]; di--)
			pi++;
		for (int ti = 1; ti < length; ti++) {
			for (di = 0; di < length; di++)
				if (d[di] == t[ti - 1]) {
					if (!pi--)
						break;
				}
			t[ti] = s[di];
#ifdef DEBUG
			printf("%c ", s[di]);
#endif
			for (pi = 0, di--; di >= 0 && s[di] == t[ti]; di--)
				pi++;
		}
		t[length] = '\0';
		printed = true;
		printf("%s\n", t);
	}
}

