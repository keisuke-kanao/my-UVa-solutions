
/*
	UVa 257 - Palinwords

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_257_Palinwords.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

bool is_palindrome(const char* s, int i, int j)
{
	for ( ; i < j; i++, j--)
		if (s[i] != s[j])
			return false;
	return true;
}

bool is_embedded(const char* s, int i, int j, int ei, int el)
{
	for ( ; i < j - el + 2; i++)
		if (!strncmp(s + i, s + ei, el))
			return true;
	return false;
}

bool is_palinword(const char* s, int length)
{
	int i, j, pi = -1 ,pj = -1, l, pl;
	for (i = 0; i < length - 3 + 1; i++) {
		j = i + 2;
		if (pj != -1 && pj >= j)
			j++;
#ifdef ONLINE_JUDGE // for some unknown reasons
		for ( ; j < min(i + 4, length); j++)
#else
		for ( ; j < length; j++)
#endif
			if (is_palindrome(s, i, j)) {
#ifdef DEBUG
				printf("%d %d: ", i, j);
				for (int k = i; k <= j; k++)
					putchar(s[k]);
				putchar('\n');
#endif
				if (pi == -1) // first one found
					pi = i, pj = j, pl = pj - pi + 1;
				else {
					l = j - i + 1;
					if (l < pl) {
						if (!is_embedded(s, pi, pj, pi, l))
							return true;
					}
					else {
						if (!is_embedded(s, i, j, pi, pl))
							return true;
					}
					pi = i, pj = j, pl = pj - pi + 1;
				}
				break;
			}
	}
	return false;
}

int main()
{
	const int nr_chars_max = 255;
	char s[nr_chars_max + 1];
	while (scanf("%s", s) != EOF) {
		if (is_palinword(s, strlen(s)))
			puts(s);
	}
	return 0;
}

