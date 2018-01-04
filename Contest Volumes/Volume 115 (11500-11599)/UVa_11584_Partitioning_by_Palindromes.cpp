
/*
	UVa 11584 - Partitioning by Palindromes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11584_Partitioning_by_Palindromes.cpp

	This is an accepted solution.
*/

/*
Dynamic Programming Solution.
First, we compute boolean table pal[i][j]=true iff s[i..j] is a palindrome.
This table can be computed in O(N^2).
Then we compute f[i]=minimum number of paritions of s[1..i]; 
This can also be computed in O(N^2), given that we already have the table "pal".
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_chars_max = 1000;

bool palindromes[nr_chars_max][nr_chars_max];
	// palindromes[i][j] is true if sub-string of s from i upto j is a palindrome
int partitions[nr_chars_max + 1];
	// partitions[i] is the number of partitions for the sub-string of s from 0 upto i

int main()
{
	int n;
	scanf("%d", &n);
	while (n--) {
		char s[nr_chars_max + 1];
		scanf("%s", s);
		int nr_chars = strlen(s);
		for (int i = 0; i < nr_chars; i++)
			palindromes[i][i] = true;
		for (int k = 1; k < nr_chars; k++)
			for (int i = 0; i < nr_chars - k; i++) {
				int j = i + k;
				if (k == 1)
					palindromes[i][j] = s[i] == s[j];
				else
					palindromes[i][j] = palindromes[i + 1][j - 1] && s[i] == s[j];
			}
#ifdef DEBUG
		for (int i = 0; i < nr_chars; i++)
			for (int j = 0; j < nr_chars; j++)
				printf("%d%c", palindromes[i][j], ((j < nr_chars - 1) ? ' ' : '\n'));
		putchar('\n');
#endif
		partitions[0] = 0; partitions[1] = 1;
		for (int i = 1; i < nr_chars; i++) {
			int p = nr_chars + 1;
			for (int j = 0; j <= i; j++)
				if (palindromes[j][i])
					p = min(p, partitions[j] + 1);
			partitions[i + 1] = p;
		}
#ifdef DEBUG
		for (int i = 0; i <= nr_chars; i++)
			printf("%d%c", partitions[i], ((i < nr_chars) ? ' ' : '\n'));
#endif
		printf("%d\n", partitions[nr_chars]);
	}
	return 0;
}

