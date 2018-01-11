
/*
	UVa 111 - History Grading

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_111_History_Grading.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int lcs(int n, const vector<int>& correct_ordering, const vector<int>& ordering)
{
	vector< vector<int> > c(n + 1, vector<int>(n + 1, 0));
	for (int i = 1; i <= n; i++)
		for (int j= 1; j <= n; j++)
			if (correct_ordering[i - 1] == ordering[j - 1])
				c[i][j] = c[i - 1][j - 1] + 1;
			else
				c[i][j] = max(c[i][j - 1], c[i - 1][j]);
	return c[n][n];
}

int main()
{
	int n;
	cin >> n;
	vector<int> correct_ordering(n);
	int i, j;
	for (i = 0; i < n; i++) {
		cin >> j;
		correct_ordering[j - 1] = i + 1;
	}
#ifdef DEBUG
	for (int i = 0; i < n; i++)
		cout << correct_ordering[i] << ((i == n - 1) ? '\n' : ' ');
#endif
	vector<int> ordering(n);
	while (cin >> j) {
		ordering[j - 1] = 1;
		for (i = 1; i < n; i++) {
			cin >> j;
			ordering[j - 1] = i + 1;
		}
#ifdef DEBUG
	for (int i = 0; i < n; i++)
		cout << ordering[i] << ((i == n - 1) ? '\n' : ' ');
#endif
		// calculate the Longest Common Subsequence of correct_ordering and ordering
		cout << lcs(n, correct_ordering, ordering) << endl;
	}
	return 0;
}

