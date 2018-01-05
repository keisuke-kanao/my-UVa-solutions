
/*
	UVa 10739 - String to Palindrome

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10739_String_to_Palindrome.cpp
*/

#include <cstdio>
#include <cstring>
#include<algorithm>
using namespace std;

const int nr_chars_max = 1000;
int memo[nr_chars_max][nr_chars_max];
char s[nr_chars_max + 1];

int palindrome(int l, int r)
{
	if (l >= r)
		return 0;
	if (memo[l][r] != -1)
		return memo[l][r];
	int result = palindrome(l + 1, r) + 1; // add s[r] to the left and increment l
	result = min(result, palindrome(l, r - 1) + 1); // deleted s[r] and decrement r
	result = min(result, palindrome(l + 1, r - 1) + (s[l] != s[r])); // replace s[l] with s[r], increment l, and decrement r
	return memo[l][r] = result;
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		scanf("%s", s);
		int length = strlen(s);
		for (int i = 0; i < length; i++)
			for (int j = 0; j < length; j++)
				memo[i][j] = -1;
		printf("Case %d: %d\n", case_nr, palindrome(0, length - 1));
	}
	return 0;
}

