
/*
	UVa 868 - Numerical Maze

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_868_Numerical_Maze.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

const int nr_dirs = 4;
const pair<int, int> dirs[nr_dirs] = {make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1), make_pair(0, -1)};

struct path {
	int i_, j_;
	int next_, last_;

	path() {}
	path(int i, int j, int next, int last) : i_(i), j_(j), next_(next), last_(last) {}
};

void bfs(int r, int c, int cj, const vector< vector<int> >& maze, path& min_path)
{
	min_path.j_ = c;
	queue<path> q;
	q.push(path(0, cj, 1, 2));
	while (!q.empty()) {
		path p = q.front(); q.pop();
		if (p.i_ == r - 1) {
			if (p.j_ < min_path.j_)
				min_path = p;
		}
		else {
			for (int i = 0; i < nr_dirs; i++) {
				int ni = p.i_ + dirs[i].first, nj = p.j_ + dirs[i].second;
				if (ni >= 0 && ni < r && nj >= 0 && nj < c && maze[ni][nj] == p.next_) {
					int next = p.next_, last = p.last_;
					if (next == last) {
						next = 1; last++;
					}
					else
						next++;
					q.push(path(ni, nj, next, last));
				}
			}
		}
	}
}

int main()
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		int N, M;
		cin >> N >> M;
		vector< vector<int> > maze(N, vector<int>(M));
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				cin >> maze[i][j];
		int min_j;
		path min_path;
		min_path.j_ = M;
		for (int j = 0; j < M; j++)
			if (maze[0][j] == 1) {
				path p;
				bfs(N, M, j, maze, p);
				if (p.j_ < min_path.j_) {
					min_j = j;
					min_path = p;
					break;
				}
			}
		cout << "1 " << min_j + 1 << endl;
		cout << N << ' ' << min_path.j_ + 1 << endl;
		if (nr_cases)
			cout << endl;
	}
	return 0;
}

/*
Sample Input
1

10 11
1 6 5 2 1 1 2 3 2 1 4
1 2 6 3 2 1 1 3 4 5 6
1 2 3 2 1 3 2 5 6 4 2
2 3 1 2 2 3 3 4 5 2 1
3 4 2 3 4 5 3 2 1 4 2
4 3 4 4 5 6 4 3 2 5 3
5 4 2 1 2 3 4 4 3 6 4
6 5 3 2 3 4 5 5 4 1 1
1 6 4 3 5 5 6 6 1 2 3
2 1 5 1 6 6 1 2 2 3 4

Sample Output
1 6
10 3

*/

