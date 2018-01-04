
/*
	UVa 11742 - Social Constraints

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11742_Social_Constraints.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int factorials[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
const int n_max = 8;
int arrangements[n_max];

struct constraint {
	int min_d_, max_d_;
} constraints[n_max][n_max];
/*
	i and j must sit at most constraints[i][j].max_d_ seats apart.
	i and j must sit at least constraints[i][j].min_d_ seats apart.
*/

int main()
{
	while (true) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (!n && !m)
			break;
		else if (!m) {
			printf("%d\n", factorials[n]);
			continue;
		}
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++) {
				constraints[i][j].min_d_ = constraints[j][i].min_d_ = 0;
				constraints[i][j].max_d_ = constraints[j][i].max_d_ = n;
			}
		while (m--) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			if (c > 0)
				constraints[a][b].max_d_ = constraints[b][a].max_d_ = min(constraints[a][b].max_d_, c);
			else
				constraints[a][b].min_d_ = constraints[b][a].min_d_ = max(constraints[a][b].min_d_, -c);
		}
		for (int i = 0; i < n; i++)
			arrangements[i] = i;
		int nr_possible = 0;
		do {
			bool possible = true;
			for (int i = 0; i < n - 1; i++) {
				for (int j = i + 1; j < n; j++) {
					const constraint& c = constraints[arrangements[i]][arrangements[j]];
					if (j - i > c.max_d_ || j - i < c.min_d_) {
						possible = false; break;
					}
				}
				if (!possible)
					break;
			}
			if (possible)
				nr_possible++;
		} while (next_permutation(arrangements, arrangements + n));
		printf("%d\n", nr_possible);
	}
	return 0;
}

