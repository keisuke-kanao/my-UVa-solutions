
/*
	UVa 1239 - Greatest K-Palindrome Substring

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1239_Greatest_K-Palindrome_Substring.cpp

	This is an accepted solution.
*/

#include <cstdio>
#include <cstring>

const int nr_chars_max = 1000;
int K;
char S[nr_chars_max + 1];

int nr_changed_chars[nr_chars_max][nr_chars_max];
	// nr_changed_chars[i][j] is the number of changed chars for S[i][j] to be a palindrome

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%s %d", S, &K);
		int length = strlen(S), longest = 1;
		for (int i = 0; i < length; i++)
			nr_changed_chars[i][i] = 0;
		for (int i = 0; i < length - 1; i++) {
			nr_changed_chars[i][i + 1] = (S[i] != S[i + 1]) ? 1 : 0;
			if (nr_changed_chars[i][i + 1] <= K)
				longest = 2;
		}
		for (int l = 3; l <= length; l++)
			for (int i = 0; i < length - l + 1; i++) {
				int j = i + l - 1;
				nr_changed_chars[i][j] = nr_changed_chars[i + 1][j - 1] + ((S[i] != S[j]) ? 1 : 0);
				if (nr_changed_chars[i][j] <= K)
					longest = l;
			}
		printf("%d\n", longest);
	}
	return 0;
}

