
/*
	UVa 10086 - Test the Rods

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10086_Test_the_Rods.cpp
*/

#include <algorithm>
#include <limits>
#include <cstdio>
#include <cstring>
using namespace std;

const int infinite = numeric_limits<int>::max();
const int T_max = 300, n_max = 30, m_max = 20;

struct site {
	int m_;
	int c1_[m_max + 1], c2_[m_max + 1];
} sites[n_max + 1];

int ssites[n_max + 1];

int T1, T2, n, costs[n_max + 1][T_max + 1];
	// costs[i][j] is the minimum cost for testing j samples at NCPC up to i-th site
int prevs[n_max + 1][T_max + 1]; // costs[i - 1][prevs[i][j]] contributes to costs[i][j]

void print_samples(int i, int t, int pt)
{
	if (i == 1)
		printf("%d", t);
	else {
		print_samples(i - 1, pt, prevs[i - 1][pt]);
		printf(" %d", t - pt);
	}
}

int main()
{
	while (true) {
		scanf("%d %d", &T1, &T2);
		if (!T1 && !T2)
			break;
		scanf("%d", &n);
		for (int i = 1, ss = 0; i <= n; i++) {
			site& s = sites[i];
			scanf("%d", &s.m_);
			for (int j = 1; j <= s.m_; j++)
				scanf("%d", &s.c1_[j]);
			for (int j = 1; j <= s.m_; j++)
				scanf("%d", &s.c2_[j]);
			ss += s.m_;
			ssites[i] = ss;
		}
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= T1; j++)
				costs[i][j] = infinite;
		costs[0][0] = 0;
		for (int i = 1; i <= n; i++) {
			const site& s = sites[i];
			for (int j = max(0, ssites[i] - T2); j <= min(T1, ssites[i]); j++)
				for (int k = max(0, j - s.m_); k <= j; k++)
					if (costs[i - 1][k] < infinite) {
						int c = costs[i - 1][k] + s.c1_[j - k] + s.c2_[s.m_ - (j - k)];
/*
#ifdef DEBUG
						printf("costs[%d][%d]: costs[%d][%d]:%d + s.c1_[%d]:%d + s.c2_[%d]:%d)\n",
							i, j, i - 1, k, costs[i - 1][k], j - k, s.c1_[j - k], s.m_ - (j - k), s.c2_[s.m_ - (j - k)]);
#endif
*/
						if (c < costs[i][j]) {
							costs[i][j] = c;
							prevs[i][j] = k;
						}
					}
#ifdef DEBUG
			for (int j = 0; j <= min(T1, ssites[i]); j++)
				if (costs[i][j] < infinite)
					printf("costs[%d][%d]:%d prevs[%d][%d]:%d\n", i, j, costs[i][j], i, j, prevs[i][j]);
#endif
		}
		printf("%d\n", costs[n][T1]);
		print_samples(n, T1, prevs[n][T1]);
		printf("\n\n");
	}
	return 0;
}

