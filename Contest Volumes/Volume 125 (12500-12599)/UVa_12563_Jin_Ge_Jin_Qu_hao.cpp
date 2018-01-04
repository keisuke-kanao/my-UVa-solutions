
/*
	UVa 12563 - Jin Ge Jin Qu hao

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12563_Jin_Ge_Jin_Qu_hao.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 50, t_max = 180 * n_max, jin_ge_jin_qu = 678;
int ts[n_max + 1][t_max + 1];

int main()
{
	int T;
	scanf("%d", &T);
	for (int c = 1; c <= T; c++) {
		int n, t;
		scanf("%d %d", &n, &t);
		int s = 0;
		for (int i = 1; i <= n; i++) {
			int st;
			scanf("%d", &st);
			for (int j = 1; j <= s + st; j++)
				ts[i][j] = 0;
			ts[i][st] = 1;
			for (int j = 1; j <= s; j++) {
				if (ts[i - 1][j]) {
					ts[i][j] = max(ts[i][j], ts[i - 1][j]);
					if (j + st < t)
						ts[i][j + st] = max(ts[i][j + st], ts[i - 1][j] + 1);
				}
			}
			s += st;
		}
#ifdef DEBUG
		for (int i = 1; i <= s; i++)
			if (ts[n][i])
				printf("%d:%d ", i, ts[n][i]);
		putchar('\n');
#endif
		int max_songs = 0, max_length = 0;
		for (int i = 1; i <= min(s, t); i++)
			if (ts[n][i]) {
				if (max_songs < ts[n][i])
					max_songs = ts[n][i], max_length = i;
				else if (max_songs == ts[n][i] && max_length < i)
					max_length = i;
 			}
		printf("Case %d: %d %d\n", c, max_songs + 1, max_length + jin_ge_jin_qu);
	}
	return 0;
}

