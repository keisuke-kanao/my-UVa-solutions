
/*
	UVa 11352 - Crazy King

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11352_Crazy_King.cpp
*/

#include <queue>
#include <utility>
#include <cstdio>
#include <cstring>
using namespace std;

const int m_max = 100, n_max = 100;

char forest[m_max][n_max + 1];
bool visited[m_max][n_max];

bool in_forest(const pair<int, int>& r, const pair<int, int>& p)
{
	return p.first >= 0 && p.first < r.first && p.second >= 0 && p.second < r.second;
}

void mark_horse(const pair<int, int>& r, const pair<int, int>& p,
	const pair<int, int>& a, const pair<int, int>& b)
{
	if (in_forest(r, p) && p != a && p != b)
		visited[p.first][p.second] = true;
}

void mark_horses(const pair<int, int>& r, const pair<int, int>& p,
	const pair<int, int>& a, const pair<int, int>& b)
{
	mark_horse(r, make_pair(p.first - 1, p.second - 2), a, b);
	mark_horse(r, make_pair(p.first - 2, p.second - 1), a, b);
	mark_horse(r, make_pair(p.first - 2, p.second + 1), a, b);
	mark_horse(r, make_pair(p.first - 1, p.second + 2), a, b);
	mark_horse(r, make_pair(p.first + 1, p.second - 2), a, b);
	mark_horse(r, make_pair(p.first + 2, p.second - 1), a, b);
	mark_horse(r, make_pair(p.first + 2, p.second + 1), a, b);
	mark_horse(r, make_pair(p.first + 1, p.second + 2), a, b);
}

int bfs(const pair<int, int>& r, const pair<int, int>& a, const pair<int, int>& b)
{
	const int nr_dirs = 8;
	const int dirs[nr_dirs][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

	queue< pair< pair<int, int>, int>  > q;
	visited[a.first][a.second] = true;
	q.push(make_pair(a, 0));
	while (!q.empty()) {
		pair< pair<int, int>, int> i = q.front(); q.pop();
		if (i.first == b)
			return i.second;
		for (int j = 0; j < nr_dirs; j++) {
			pair<int, int> k = make_pair(i.first.first + dirs[j][0], i.first.second + dirs[j][1]);
			if (in_forest(r, k) && !visited[k.first][k.second] && forest[k.first][k.second] != 'Z') {
				visited[k.first][k.second] = true;
				q.push(make_pair(k, i.second + 1));
			}
		}
	}
	return -1;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		pair<int, int> r, a, b;
		scanf("%d %d", &r.first, &r.second);
		getchar();
		int i, j;
		for (i = 0; i < r.first; i++) {
			gets(forest[i]);
			for (j = 0; j < r.second; j++)
				if (forest[i][j] == 'A')
					a = make_pair(i, j);
				else if (forest[i][j] == 'B')
					b = make_pair(i, j);
		}
		memset(visited, 0, sizeof(visited));
		for (i = 0; i < r.first; i++)
			for (j = 0; j < r.second; j++)
				if (forest[i][j] == 'Z')
					mark_horses(r, make_pair(i, j), a, b);
		int l = bfs(r, a, b);
		if (l != -1)
			printf("Minimal possible length of a trip is %d\n", l);
		else
			puts("King Peter, you can't go now!");
	}
	return 0;
}

