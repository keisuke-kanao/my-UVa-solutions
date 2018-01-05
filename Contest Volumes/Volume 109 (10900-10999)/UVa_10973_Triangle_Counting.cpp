
/*
	UVa 10973 - Triangle Counting

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10973_Triangle_Counting.cpp
*/

#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 3000;
vector<int> edges[n_max + 1];
bool matrix[n_max + 1][n_max + 1];

void triangle_counting(int n, int ci, int ei, int t[], int& ctr)
{
	if (ci == 2) {
#ifdef DEBUG
		printf("%d %d %d\n", t[0], t[1], ei);
#endif
		if (matrix[t[0]][ei])
			ctr++;
	}
	else {
		t[ci] = ei;
		const vector<int>& es = edges[ei];
		for (size_t i = 0, j = es.size(); i < j; i++)
			triangle_counting(n, ci + 1, es[i], t, ctr);
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			edges[i].clear();
			for (int j = i + 1; j <= n; j++)
				matrix[i][j] = matrix[j][i] = false;
		}
		while (m--) {
			int i, j;
			scanf("%d %d", &i, &j);
			if (i > j)
				swap(i, j);
			edges[i].push_back(j);
			matrix[i][j] = matrix[j][i] = true;
		}
		for (int i = 1; i <= n; i++)
			sort(edges[i].begin(), edges[i].end());
		int t[2], ctr = 0;
		for (int i = 1; i <= n; i++) {
			t[0] = i;
			const vector<int>& es = edges[i];
			for (size_t j = 0, k = es.size(); j < k; j++)
				triangle_counting(n, 1, es[j], t, ctr);
		}
		printf("%d\n", ctr);
	}
	return 0;
}

