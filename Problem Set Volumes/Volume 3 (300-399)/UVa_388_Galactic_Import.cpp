
/*
	UVa 388 - Galactic Import

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_388_Galactic_Import.cpp

	from ACM Mid-Central Regionals - 1995, Problem #4
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidCen/1995/index.html)
*/

#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
using namespace std;

const int nr_planets = 26;
bool matrix[nr_planets][nr_planets];
double exports[nr_planets];
int paths[nr_planets];

void bfs(int s)
{
	queue< pair<int, int> > q;
	q.push(make_pair(s, 0));
	while (!q.empty()) {
		pair<int, int> p = q.front(); q.pop();
		int u = p.first;
		for (int v = 0; v < nr_planets; v++)
			if (matrix[u][v] && paths[v] > p.second + 1) {
				paths[v] = p.second + 1;
				q.push(make_pair(v, paths[v]));
			}
	}
}

int main()
{
	double costs[nr_planets];
	costs[0] = 1.0;
	for (int i = 1; i < nr_planets; i++)
		costs[i] = costs[i - 1] * 0.95;
	int N;
	while (scanf("%d", &N) != EOF) {
		memset(matrix, 0, sizeof(matrix));
		memset(exports, 0, sizeof(exports));
		for (int i = 0; i < nr_planets; i++)
			paths[i] = nr_planets;
		for (int i = 0; i < N; i++) {
			char s[2], t[nr_planets + 1];
			double e;
			scanf("%s %lf %s", s, &e, t);
			int j = s[0] - 'A';
			exports[j] = e;
			for (const char* p = t; *p; p++)
				if (*p == '*')
					paths[j] = 0;
				else
					matrix[j][*p - 'A'] = true;
		}
		for (int i = 0; i < nr_planets; i++)
			if (exports[i] && !paths[i])
				bfs(i);
		int max_i = -1;
		double max_export = -1.0;
		for (int i = 0; i < nr_planets; i++)
			if (exports[i] && paths[i] < nr_planets) {
				double e = exports[i];
				if (paths[i])
					e *= costs[paths[i]];
#ifdef DEBUG
				printf("%c: %d %lf\n", i + 'A', paths[i], e);
#endif
				if (e > max_export) {
					max_i = i; max_export = e;
				}
			}
		printf("Import from %c\n", max_i + 'A');
	}
	return 0;
}

