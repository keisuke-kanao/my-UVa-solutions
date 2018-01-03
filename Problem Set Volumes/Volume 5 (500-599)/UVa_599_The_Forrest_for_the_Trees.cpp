
/*
	UVa 599 - The Forrest for the Trees

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_599_The_Forrest_for_the_Trees.cpp
*/

#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_points = 'Z' - 'A' + 1;
const int nr_chars_max = nr_points * 2;
bool points[nr_points], matrix[nr_points][nr_points];

int bfs(int u)
{
	int nr = 1;
	queue<int> q;
	points[u] = false;
	q.push(u);
	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (int v = 0; v < nr_points; v++)
			if (matrix[u][v] && points[v]) {
				nr++;
				points[v] = false;
				q.push(v);
			}
	}
	return nr;
}

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		memset(points, 0, sizeof(points));
		memset(matrix, 0, sizeof(matrix));
		char s[nr_chars_max + 1];
		while (true) {
			scanf("%s", s);
			if (s[0] == '*')
				break;
			int u = s[1] - 'A', v = s[3] - 'A';
			matrix[u][v] = matrix[v][u] = true;
		}
		scanf("%s", s);
		for (const char* p = s; ; p++) {
			points[*p++ - 'A'] = true;
			if (!*p)
				break;
		}
		int nr_trees = 0, nr_acorns = 0;
		for (int i = 0; i < nr_points; i++)
			if (points[i]) {
				if (bfs(i) > 1)
					nr_trees++;
				else
					nr_acorns++;
			}
		printf("There are %d tree(s) and %d acorn(s).\n", nr_trees, nr_acorns);
	}
	return 0;
}

