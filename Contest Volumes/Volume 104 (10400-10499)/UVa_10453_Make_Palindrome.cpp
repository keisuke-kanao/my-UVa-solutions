
/*
	UVa 10453 - Make Palindrome

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10453_Make_Palindrome.cpp
*/

/*
The idea is that to make the shortest palindrome, 
calculate the longest common subsequence of the string and its reverse - 
this will give you the optimal overlap in the palindrome. The rest can be added on.
*/

#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_chars_max = 1000;
enum {upper_left, upper, left};
int c[nr_chars_max + 1][nr_chars_max + 1], b[nr_chars_max + 1][nr_chars_max + 1];

struct cs { // common subsequence
	int i_, j_;
} css[nr_chars_max + 1];

void trace_lcs(const char* s, int i, int j, int& ctr)
{
	if (!i || !j)
		return;
	if (b[i][j] == upper_left) {
		trace_lcs(s, i - 1, j - 1, ctr);
		ctr++;
		css[ctr].i_ = i, css[ctr].j_ = j;
#ifdef DEBUG
		printf("s[%d] t[%d]:%c ", i, j, s[i]);
#endif
	}
	else if (b[i][j] == upper)
		trace_lcs(s, i - 1, j, ctr);
	else
		trace_lcs(s, i, j - 1, ctr);
}

int main()
{
	char s[nr_chars_max + 2], t[nr_chars_max + 2];
	while (gets(s + 1)) {
		int n = strlen(s + 1);
		if (!n) {
			puts("0");
			continue;
		}
		reverse_copy(s + 1, s + n + 1, t + 1);
		t[n + 1] = '\0';
		// calculate the Longest Common Subsequrnce of s and t
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= n; j++)
				c[i][j] = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (s[i] == t[j]) {
					c[i][j] = c[i - 1][j - 1] + 1;
					b[i][j] = upper_left;
				}
				else if (c[i - 1][j] > c[i][j - 1]) {
					c[i][j] = c[i - 1][j];
					b[i][j] = upper;
				}
				else {
					c[i][j] = c[i][j - 1];
					b[i][j] = left;
				}
#ifdef DEBUG
		printf("%s\n%s\n", s + 1, t + 1);
		printf("%d\n", c[n][n]);
#endif
		int ctr = 0;
		trace_lcs(s, n, n, ctr);
#ifdef DEBUG
		putchar('\n');
#endif
		printf("%d ", n - ctr);
		char u[nr_chars_max * 2 + 2];
		int i = 1, j = 1, k = 1;
		for (int csi = 1; csi <= ctr; csi++) {
			if (i < css[csi].i_)
				do
					u[k++] = s[i++];
				while (i < css[csi].i_);
			if (j < css[csi].j_)
				do
					u[k++] = t[j++];
				while (j < css[csi].j_);
			u[k++] = s[css[csi].i_];
			i++, j++;
		}
		if (i <= n)
			do
				u[k++] = s[i++];
			while (i <= n);
		if (j <= n)
			do
				u[k++] = t[j++];
			while (j <= n);
		u[k] = '\0';
		printf("%s\n", u + 1);
	}
	return 0;
}

