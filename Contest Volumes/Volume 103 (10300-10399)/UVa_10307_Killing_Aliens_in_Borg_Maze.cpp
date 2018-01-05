
/*
	UVa 10307 - Killing Aliens in Borg Maze

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10307_Killing_Aliens_in_Borg_Maze.cpp
*/

#include <vector>
#include <utility>
#include <queue>
#include <set>
#include <limits>
#include <cstdio>
#include <cstring>
using namespace std;

const int x_max = 50, y_max = 50;
char maze[y_max][x_max + 1];

struct edge {
	int v_;
	int w_;
	edge(int v, int w) : v_(v), w_(w) {}
};

void bfs(int x, int y, int u, const pair<int, int>& p, vector<int>& sa_distances)
{
	const int nr_dirs = 4;
	const pair<int, int> dirs[nr_dirs] = {make_pair(1, 0), make_pair(0, 1), make_pair(-1, 0), make_pair(0, -1)};

	vector< vector<int> > distances(y, vector<int>(x, -1));
	queue< pair<int, int> > q;
	distances[p.first][p.second] = 0;
	sa_distances[u] = 0;
	q.push(p);
	while (!q.empty()) {
		pair<int, int> pu = q.front(); q.pop();
		for (int i = 0; i < nr_dirs; i++) {
			int j = pu.first + dirs[i].first, k = pu.second + dirs[i].second;
			if (maze[j][k] != '#' && distances[j][k] == -1) {
				distances[j][k] = distances[pu.first][pu.second] + 1;
				if (maze[j][k] != ' ')
					sa_distances[-maze[j][k]] = distances[j][k];
				q.push(make_pair(j, k));
			}
		}
	}
}

struct distance_comparator {
	const vector<int>& distances_;

	distance_comparator(const vector<int>& distances) : distances_(distances) {}
	bool operator() (int i, int j) const
	{
		return (distances_[i] != distances_[j]) ? distances_[i] < distances_[j] : i < j;
	}
};

int mst_prim(int n, const vector< vector<edge> >& edges)
{
	vector<bool> visited(n, false);
	vector<int> distances(n, numeric_limits<int>::max());
	distances[0] = 0;
	int mst_distance = 0;
	set<int, distance_comparator> pq(distances); // priority queue
	pq.insert(0);
	while (!pq.empty()) {
		int u = *pq.begin();
		pq.erase(pq.begin());
		visited[u] = true;
		mst_distance += distances[u];
		const vector<edge>& es = edges[u];
		for (size_t i = 0, j = es.size(); i < j; i++) {
			int v = es[i].v_, w = es[i].w_;
			if (!visited[v] && w < distances[v]) {
				pq.erase(v); // remove v if it has already been in the queue
				distances[v] = w;
				pq.insert(v);
			}
		}
	}
	return mst_distance;
}

int main()
{
	int N;
	scanf("%d", &N);
	while (N--) {
		int x, y;
		scanf("%d %d", &x, &y);
		getchar(); // skip '\n'
		int s = 0, n = 0; // total number of the start and the aliens
		vector< pair<int, int> > points; // positions of the start and the aliens
		for (int i = 0; i < y; i++) {
			gets(maze[i]);
			for (int j = 0; j < x; j++)
				if (maze[i][j] == 'S') {
					points.insert(points.begin(), make_pair(i, j));
					s++;
					maze[i][j] = 0;
				}
				else if (maze[i][j] == 'A') {
					points.push_back(make_pair(i, j));
					n++;
					maze[i][j] = -n;
				}
		}
		if (!s || !n) {
			puts("0"); continue;
		}
		n++; // n += s
		vector< vector<edge> > edges(n);
		// calculate the distance between the start and the aliens
		for (int i = 0; i < n; i++) {
			vector<int> distances(n, -1);
			bfs(x, y, i, points[i], distances);
			vector<edge>& es = edges[i];
			for (int j = 0; j < n; j++)
				if (i != j && distances[j] != -1)
					es.push_back(edge(j, distances[j]));
#ifdef DEBUG
			printf("%d: [%d %d] ", i, points[i].first, points[i].second);
			for (size_t j = 0; j < es.size(); j++)
				printf("%d: %d%c", es[j].v_, es[j].w_, ((j < es.size() - 1) ? ' ' : '\n'));
#endif
		}
		// apply Prim's minimum spanning tree algorithm
		printf("%d\n", mst_prim(n, edges));
	}
	return 0;
}

