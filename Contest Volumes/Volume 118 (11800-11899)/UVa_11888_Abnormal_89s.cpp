
/*
	UVa 11888 - Abnormal 89's

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11888_Abnormal_89s.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_chars_max = 200000;
char pattern[nr_chars_max + 1], text[nr_chars_max * 2 + 1];
int lps[nr_chars_max];
	// lps[i] is the length of the maximum matching proper prefix which is also a suffix of pattern[0..i]

int kmp(const char* p, int pl, const char* t, int tl)
{
	// calculate the KMP (Knuth-Morris-Pratt) lps
	// lps[0] is always 0
	for (int i = 1, length = 0 /* length of the previous longest prefix suffix */; i < pl; ) {
		if (p[i] == p[length])
			lps[i++] = ++length;
		else {
			if (length)
				length = lps[length - 1];
			else
				lps[i++] = 0;
		}
	}
#ifdef DEBUG
	for (int i = 0; i < pl; i++)
		printf("[%d]:%d%c", i, lps[i], ((i < pl - 1) ? ' ' : '\n'));
#endif
	for (int pi = 0, ti = 0; ti < tl; ) {
		if (p[pi] == t[ti])
			pi++, ti++;
		if (pi == pl)
			return ti - pi;
		// mismatch after j matches
		else if (ti < tl && p[pi] != t[ti]) {
			if (pi)
                pi = lps[pi - 1];
			else
                ti++;
		}
    }
	return -1;
}

bool is_alindrome(const char* s, int length)
{
	if (length & 1) {
		if (length == 1)
			return false;
		char c = s[0];
		for (int i = 1; i < length; i++)
				if (s[i] != c)
					return false;
		return true;
	}
	else
		return !memcmp(s, s + length / 2, length / 2);
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%s", text);
		int n = strlen(text);
		if (n == 1) {
			puts("palindrome");
			continue;
		}
		// seach reverse of the text in text + text
		memcpy(text + n, text, n);
		for (int i = 0; i < n; i++)
			pattern[i] = text[n - 1 - i]; // reverser of the string
		int ti = kmp(pattern, n, text, n * 2);
		if (ti == -1)
			puts("simple");
		else if (ti || is_alindrome(text, n))
			puts("alindrome");
		else
			puts("palindrome");
	}
	return 0;
}

