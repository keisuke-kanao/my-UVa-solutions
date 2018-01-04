
/*
	UVa 326 - Extrapolation Using a Difference Table

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_326_Extrapolation.cpp

	from ACM  North Central Regionals 1993
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1993/prob_c.html)
	Note that "Expected Output from Judged runs" in the above page is WRONG.
*/

#include <cstdio>

int main()
{
	while (true) {
		const int n_max = 10;
		int n, k, values[n_max], entries[n_max];
		scanf("%d", &n);
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			scanf("%d", &values[i]);
		scanf("%d", &k);
		for (int i = n - 1; i >= 0; i--) {
			for (int j = 0; j < i; j++)
				values[j] = values[j + 1] - values[j];
			entries[i] = values[i];
		}
#ifdef DEBUG
		for (int i = 0; i < n; i++)
			printf("%d%c", entries[i], ((i == n - 1) ? '\n' : ' '));
#endif
		int t = n;
		while (k--) {
			int s = 0;
			for (int i = 0; i < n; i++) {
				entries[i] += s;
				s = entries[i];
			}
			t++;
		}
		printf("Term %d of the sequence is %d\n", t, entries[n - 1]);
	}
	return 0;
}

