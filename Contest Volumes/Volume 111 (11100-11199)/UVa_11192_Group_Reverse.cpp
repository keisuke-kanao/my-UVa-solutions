
/*
	UVa 11192 - Group Reverse

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11192_Group_Reverse.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	while (true) {
		int g;
		scanf("%d", &g);
		if (!g)
			break;
		const int nr_chars_max = 100;
		char s[nr_chars_max + 1];
		scanf("%s", s);
		int length = strlen(s);
		int n = length / g;
		for (int i = 0; i < length; i += n) {
			for (int j = i, k = j + n - 1; j < k; j++, k--) {
				char c = s[j];
				s[j] = s[k]; s[k] = c;
			}
		}
		printf("%s\n", s);
	}
	return 0;
}

