
/*
	UVa 929 - Number Maze

	To build using Visucal Studio 2012:
		cl -EHsc UVa_929_Number_Maze.cpp

	An accepted solution.
*/

#include <set>
#include <utility>
#include <limits>
#include <cstdio>
using namespace std;

const int n_max = 999, m_max = 999;
int distances[n_max][m_max], maze[n_max][m_max];
bool visited[n_max][m_max];
	// visited[i][j] is true if maze[i][j] has already been reached (so the distances[i][j] has already been settled)

struct distance_comparator {
	bool operator () (pair<int, int> p, pair<int, int> q) const
	{
		if(distances[p.first][p.second] == distances[q.first][q.second])
			return p < q;
		else
			return distances[p.first][p.second] < distances[q.first][q.second];
	}
};

int dijkstra_shortest_path(int n, int m)
{
	const int nr_dirs = 4;
	const int dirs[nr_dirs][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			distances[i][j] = numeric_limits<int>::max();
			visited[i][j] = false;
		}
	distances[0][0] = maze[0][0];
	set <pair<int, int>, distance_comparator> pq; // priority queue
	pq.insert(make_pair(0, 0));
	while(!pq.empty()) {
		pair<int, int> u = *pq.begin();
		pq.erase(pq.begin());
		visited[u.first][u.second] = true;
		if (u.first == n - 1 && u.second == m - 1) // reached at the bottom-left conner
			break;
		int d = distances[u.first][u.second];
		for(int i = 0; i < nr_dirs; i++) {
			int vi = u.first + dirs[i][0], vj = u.second + dirs[i][1];
			if (vi >= 0 && vi < n && vj>= 0 && vj < m &&
				!visited[vi][vj] &&
				distances[vi][vj] > d + maze[vi][vj]) {
				pair<int, int> v = make_pair(vi, vj);
				pq.erase(v); // remove v if it has already been in the queue
				distances[vi][vj] = d + maze[vi][vj];
				pq.insert(v);
			}
		}
	}
	return distances[n - 1][m - 1];
}

int main()
{
	int nr_mazes;
	scanf("%d", &nr_mazes);
	while (nr_mazes--) {
		int n, m;
		scanf("%d", &n);
		scanf("%d", &m);
		for (int r = 0; r < n; r++)
			for (int c = 0; c < m; c++)
				scanf("%d", &maze[r][c]);
		// apply Dijkstra's shortest path algorithm
		printf("%d\n", dijkstra_shortest_path(n, m));
	}
	return 0;
}

