
/*
	UVa 1584 - Circular Sequence

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1584_Circular_Sequence.cpp
*/

#include <cstdio>
#include <cstring>

int compare_string(const char* s, int length, int i, int j)
{
	for (int k = length; k; k--, i = (i + 1) % length, j = (j + 1) % length) {
		if (s[i] > s[j])
			return 1;
		else if (s[i] < s[j])
			return -1;
	}
	return 0;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		const int nr_chars_max = 100;
		char s[nr_chars_max + 1];
		scanf("%s", s);
		int min_i = 0, length = strlen(s);
		for (int i = 1; i < length; i++)
			if (compare_string(s, length, i, min_i) < 0)
				min_i = i;
		printf("%s", &s[min_i]);
		if (min_i) {
			s[min_i] = '\0';
			printf("%s", s);
		}
/*
		for (int k = length; k; k--, min_i = (min_i + 1) % length)
			putchar(s[min_i]);
*/
		putchar('\n');
	}
	return 0;
}

