
/*
	UVa 271 - Simply Syntax

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_271_Simply_Syntax.cpp
*/

#include <cstdio>
#include <cstring>

int get_sentence(const char* s, int i, int length)
{
	if (i >= length)
		return -1;
	char c = s[i];
	if (c == 'N') {
		int j = get_sentence(s, i + 1, length);
		return (j == -1) ? j : j + 1;
	}
	else if (c == 'C' || c == 'D' || c == 'E' || c == 'I') {
		int j = get_sentence(s, i + 1, length);
		if (j == -1)
			return -1;
		int k = get_sentence(s, i + j + 1, length);
		return (k == -1) ? -1 : j + k + 1;
	}
	else
		return 1;
}

int main()
{
	const int nr_chars_max = 256;
	char s[nr_chars_max + 1];
	while (gets(s)) {
		int length = strlen(s);
		printf("%s\n", ((get_sentence(s, 0, length) == length) ? "YES" : "NO"));
	}
	return 0;
}

