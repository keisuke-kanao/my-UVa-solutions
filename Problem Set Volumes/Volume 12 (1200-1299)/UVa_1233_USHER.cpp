
/*
	UVa 1233 - USHER

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1233_USHER.cpp
*/

#include <cstdio>
#include <algorithm>
#include <limits>
using namespace std;

const int p_max = 500;
int dists[p_max + 1][p_max + 1];

int main()
{
	int c;
	scanf("%d", &c);
	while (c--) {
		int b, p;
		scanf("%d %d", &b, &p);
		for (int i = 0; i <= p; i++)
			for (int j = 0; j <= p; j++)
				dists[i][j] = numeric_limits<int>::max();
		int q;
		scanf("%d", &q);
		while (q--) {
			int u;
			scanf("%d", &u);
			dists[0][u] = 0;
		}
		for (int i = 1; i <= p; i++) {
			int j;
			scanf("%d", &j);
			while (j--) {
				int d, u;
				scanf("%d %d", &d, &u);
				dists[i][u] = min(dists[i][u], d);
			}
		}
		for (int k = 0; k <= p; k++)
			for (int i = 0; i <= p; i++)
				if (dists[i][k] != numeric_limits<int>::max())
					for (int j = 0; j <= p; j++)
						if (dists[k][j] != numeric_limits<int>::max() && dists[i][k] + dists[k][j] < dists[i][j])
							dists[i][j] = dists[i][k] + dists[k][j];
		int min_d = dists[0][0], nc = 0, uc = 0;
		while (true) {
			if ((nc += min_d) >= b)
				break;
			nc--;
			uc++;
		}
		printf("%d\n", uc);
	}
	scanf("%*d"); // "0"
	return 0;
}

