
/*
	UVa 11760 - Brother Arif, Please feed us!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11760_Brother_Arif_Please_feed_us.cpp
*/

#include <cstdio>
#include <cstring>

const int R_max = 10000, C_max = 10000;
bool rows[R_max], columns[C_max];

int main()
{
	for (int cn = 1; ; cn++) {
		int R, C, N;
		scanf("%d %d %d", &R, &C, &N);
		if (!R && !C && !N)
			break;
		memset(rows, 0, sizeof(rows));
		memset(columns, 0, sizeof(columns));
		int r, c;
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &r, &c);
			rows[r] = columns[c] = true;
		}
		scanf("%d %d", &r, &c);
		bool found = (rows[r] || columns[c]) ? false : true;
		if (!found) {
			const int nr_dirs = 4;
			const int dirs[nr_dirs][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
			for (int i = 0; i < nr_dirs; i++) {
				int ri = r + dirs[i][0], ci = c + dirs[i][1];
				if (ri >= 0 && ri < R && ci >= 0 && ci < C && !rows[ri] && !columns[ci]) {
					found = true;
					break;
				}
			}
		}
		printf("Case %d: %s\n", cn,
			((found) ? "Escaped again! More 2D grid problems!" : "Party time! Let's find a restaurant!"));
	}
	return 0;
}

