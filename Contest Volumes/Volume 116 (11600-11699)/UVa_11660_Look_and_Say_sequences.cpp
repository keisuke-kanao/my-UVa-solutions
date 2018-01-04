
/*
	UVa 11660 - Look-and-Say sequences

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11660_Look_and_Say_sequences.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int i_max = 1000;

void look_and_say_sequence(const char* s, char* t)
{
	int ctr = 1;
	char d = *s++;
	char* u = t;
	for ( ; *s; s++) {
		if (*s != d) {
			*t++ = ctr + '0';
			*t++ = d;
			if (t - u >= i_max) {
				*t = '\0';
				return;
			}
			ctr = 1;
			d = *s;
		}
		else
			ctr++;
	}
	*t++ = ctr + '0';
	*t++ = d;
	*t = '\0';
}

int main()
{
	while (true) {
		int i, j;
		char s[i_max + 1], t[i_max + 1];
		scanf("%s %d %d", s, &i, &j);
		if (s[0] == '0' && !i && !j)
			break;
		char *p = s, *q = t;
		for (int k = 1; k < i; k++) {
			look_and_say_sequence(p, q);
			swap(p, q);
#ifdef DEBUG
			printf("%s\n", p);
#endif
		}
		printf("%c\n", *(p + j - 1));
	}
	return 0;
}

