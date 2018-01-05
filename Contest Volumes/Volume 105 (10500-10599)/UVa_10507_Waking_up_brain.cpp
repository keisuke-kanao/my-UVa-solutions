
/*
	UVa 10507 - Waking up brain

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_10507_Waking_up_brain.cpp
*/

#include <cstdio>
#include <queue>
#include <utility>
using namespace std;

const int nr_letters = 26;
int visited[nr_letters];
bool matrix[nr_letters][nr_letters];

int bfs(int n, int si, int sj, int sk)
{
	for (int i = 0; i < nr_letters; i++)
		visited[i] = 0;
	queue< pair<int, int> > q;
	int years = 0;
	visited[si] = visited[sj] = visited[sk] = 3;
	q.push(make_pair(years, si));
	q.push(make_pair(years, sj));
	q.push(make_pair(years, sk));
	while (!q.empty()) {
		pair<int, int> u = q.front(); q.pop();
		if (u.first > years)
			years++;
		for (int v = 0; v < nr_letters; v++)
			if (matrix[u.second][v] && visited[v] < 3) {
				if (++visited[v] == 3) {
					q.push(make_pair(years + 1, v));
				}
			}
	}
	int nr_visited = 0;
	for (int i = 0; i < nr_letters; i++)
		if (visited[i] >= 3)
			nr_visited++;
	return (nr_visited == n) ? years : -1;
}

int main()
{
	const int nr_chars_max = 8;
	int n, m;
	while (scanf("%d", &n) != EOF) {
		scanf("%d", &m);
		for (int i = 0; i < nr_letters; i++)
			for (int j = 0; j < nr_letters; j++)
				matrix[i][j] = false;
		char initial_areas[nr_chars_max];
		scanf("%s", initial_areas);
		while (m--) {
			char areas[nr_chars_max];
			scanf("%s", areas);
			int u = areas[0] - 'A', v = areas[1] - 'A';
			matrix[u][v] = matrix[v][u] = true;
		}
		int years = bfs(n, initial_areas[0] - 'A', initial_areas[1] - 'A', initial_areas[2] - 'A');
		if (years == -1)
			puts("THIS BRAIN NEVER WAKES UP");
		else
			printf("WAKE UP IN, %d, YEARS\n", years);

	}
	return 0;
}


