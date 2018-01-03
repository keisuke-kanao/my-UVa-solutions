
/*
	UVa 1239 - Greatest K-Palindrome Substring

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1239_Greatest_K-Palindrome_Substring.cpp

	This solution has not been submitted but if it were, it would probably been verdicted as Time Limit Exceeded.
*/

#include <cstdio>
#include <cstring>

const int nr_chars_max = 1000;
int K;
char S[nr_chars_max + 1];

bool is_k_palindrome(int i, int j)
{
	int k = 0;
	for (j--; i < j; i++, j--)
		if (S[i] != S[j] && ++k > K)
			return false;
	return true;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%s %d", S, &K);
		int length = strlen(S), longest = K + 1;
		for (int i = 0; i < length; i++)
			for (int j = length; j; j--)
				if (j - i > longest && is_k_palindrome(i, j))
					longest = j - i;
		printf("%d\n", longest);
	}
	return 0;
}

