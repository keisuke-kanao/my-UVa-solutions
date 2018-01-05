
/*
	UVa 10702 - Travelling Salesman

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10702_Travelling_Salesman.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int c_max = 100, t_max = 1000;
int tp[t_max + 1][c_max + 1]; // tp[k][i] is the k-th total profit of city i
int p[c_max + 1][c_max + 1]; // p[i][j] is the profit when moving from i to j

int main()
{
	while (true) {
		int c, s, e, t;
		scanf("%d %d %d %d", &c, &s, &e, &t);
		if (!c && !s && !e && !t)
			break;
		for (int i = 1; i <= c; i++)
			for (int j = 1; j <= c; j++)
				scanf("%d", &p[i][j]);
		for (int i = 1; i <= c; i++)
			tp[1][i] = p[s][i];
		for (int k = 2; k <= t; k++)
			for (int i = 1; i <= c; i++) {
				int max_p = 0;
				for (int j = 1; j <= c; j++)
					max_p = max(max_p, tp[k - 1][j] + p[j][i]);
				tp[k][i] = max_p;
			}
		int max_tp = 0;
		for (int i = 1; i <= e; i++) {
			int j;
			scanf("%d", &j);
			max_tp = max(max_tp, tp[t][j]);
		}
		printf("%d\n", max_tp);
	}
	return 0;
}

