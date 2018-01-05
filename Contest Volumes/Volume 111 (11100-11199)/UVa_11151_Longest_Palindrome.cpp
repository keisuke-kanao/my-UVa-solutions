
/*
	UVa 11151 - Longest Palindrome

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11151_Longest_Palindrome.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_chars_max = 1000;
char s[nr_chars_max + 1];
int plengths[nr_chars_max][nr_chars_max];
	// plengths[i][j] is the longest palindrome length between i and j

int main()
{
	int t;
	scanf("%d", &t);
	getchar();
	while (t--) {
		gets(s);
		int length = strlen(s), longest_length = 0;
		if (length) {
			for (int i = 0; i < length; i++)
				plengths[i][i] = 1;
/*
		plengths[i][j] = max(max(plengths[i][i + k - 1], plengths[i + 1][i + k]),
			plengths[i + 1][i + k - 1] + ((s[i] == s[i + k]) ? 2 : 0));
*/
			for (int k = 1; k < length; k++)
				for (int i = 0; i < length - k; i++) {
					int l = (s[i] == s[i + k]) ? 2 : 0;
					if (k > 1)
						l += plengths[i + 1][i + k - 1];
					plengths[i][i + k] = max(max(plengths[i][i + k - 1], plengths[i + 1][i + k]), l);
				}
			longest_length = plengths[0][length - 1];
		}
		printf("%d\n", longest_length);
	}
	return 0;
}

