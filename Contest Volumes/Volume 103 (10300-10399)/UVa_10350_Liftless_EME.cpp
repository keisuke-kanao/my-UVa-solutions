
/*
	UVa 10350 - Liftless EME

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10350_Liftless_EME.cpp
*/

#include <algorithm>
#include <limits>
#include <cstdio>
using namespace std;

const int nr_chars_max = 12, n_max = 120, m_max = 15, ladder = 2;
int times[n_max][m_max][m_max];
	// times[i][j][k] is the time from the i-th floor's j-th hole to the (i + 1)-th floor's k-th hole
int min_times[n_max][m_max]; // min_times[i][j] is the min. time needed to reach i-th floor's j-th hole

int main()
{
	char s[nr_chars_max + 1];
	while (scanf("%s", s) != EOF) {
		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n - 1; i++)
			for (int j = 0; j < m; j++)
				for (int k = 0; k < m; k++)
					scanf("%d", &times[i][j][k]);
		for (int j = 0; j < m; j++)
			min_times[0][j] = 0;
		for (int i = 1; i < n; i++)
			for (int j = 0; j < m; j++) {
				int min_t = numeric_limits<int>::max();
				for (int k = 0; k < m; k++)
					min_t = min(min_t, min_times[i - 1][k] + times[i - 1][k][j]);
				min_times[i][j] = min_t;
			}
		int min_t = numeric_limits<int>::max();
		for (int j = 0; j < m; j++)
			min_t = min(min_t, min_times[n - 1][j]);
		min_t += ladder * (n - 1);
		printf("%s\n%d\n", s, min_t);
	}
	return 0;
}

