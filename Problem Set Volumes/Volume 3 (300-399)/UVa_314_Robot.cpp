
/*
	UVa 314 - Robot

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_314_Robot.cpp

	from ACM Central European Regionals 1996
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_CERC/1996/index.html)
	Note that the test data (g.out) from the above site is wrong. the solution (g.c) may also be wrong.
*/

#include <queue>
#include <utility>
#include <cstdio>
using namespace std;

enum {north, south, east, west};

struct path {
	pair<int, int> pos_;
	int dir_;
	int seconds_;
};

const int m_max = 50, n_max = 50;
bool store[m_max][n_max], visited[m_max][n_max][west - north + 1];

int go_forward(int m, int n, int step, const path& p, queue<path>& q)
{
	path np;
	switch (p.dir_) {
	case north:
		if (p.pos_.first - step - 1 < 0 ||
			store[p.pos_.first - step - 1][p.pos_.second - 1] || store[p.pos_.first - step - 1][p.pos_.second])
			return -1;
		np.pos_ = make_pair(p.pos_.first - step, p.pos_.second);
		break;
	case south:
		if (p.pos_.first + step >= m ||
			store[p.pos_.first + step][p.pos_.second - 1] || store[p.pos_.first + step][p.pos_.second])
			return -1;
		np.pos_ = make_pair(p.pos_.first + step, p.pos_.second);
		break;
	case east:
		if (p.pos_.second + step >= n ||
			store[p.pos_.first][p.pos_.second + step] || store[p.pos_.first - 1][p.pos_.second + step])
			return -1;
		np.pos_ = make_pair(p.pos_.first, p.pos_.second + step);
		break;
	default:
		if (p.pos_.second - step - 1 < 0 ||
			store[p.pos_.first][p.pos_.second  - step - 1] || store[p.pos_.first - 1][p.pos_.second - step - 1])
			return -1;
		np.pos_ = make_pair(p.pos_.first, p.pos_.second - step);
		break;
	}
	np.dir_ = p.dir_;
	if (visited[np.pos_.first][np.pos_.second][np.dir_])
		return 0;
	np.seconds_ = p.seconds_ + 1;
	visited[np.pos_.first][np.pos_.second][np.dir_] = true;
	q.push(np);
	return 1;
}

bool turn(bool right, const path &p, queue<path>& q)
{
	path np;
	switch (p.dir_) {
	case north:
		np.dir_ = (right) ? east : west; break;
	case south:
		np.dir_ = (right) ? west : east; break;
	case east:
		np.dir_ = (right) ? south : north; break;
	default:
		np.dir_ = (right) ? north : south; break;
	}
	if (visited[p.pos_.first][p.pos_.second][np.dir_])
		return false;
	np.pos_ = p.pos_; np.seconds_ = p.seconds_ + 1;
	visited[np.pos_.first][np.pos_.second][np.dir_] = true;
	q.push(np);
	return true;
}

int bfs(int m, int n, const pair<int, int>&b, const pair<int, int>&e, int dir)
{
	path p;
	p.pos_ = b; p.dir_ = dir; p.seconds_ = 0;
	queue<path> q;
	visited[b.first][b.second][dir] = true;
	q.push(p);
	while (!q.empty()) {
		path p = q.front(); q.pop();
#ifdef DEBUG
		printf("%d %d %d, %d\n", p.pos_.first, p.pos_.second, p.dir_, p.seconds_);
#endif
		if (p.pos_ == e)
			return p.seconds_;
		turn(false, p, q); // turn left
		turn(true, p, q); // turn right
		for (int step = 1; step <= 3; step++)
			if (go_forward(m, n, step, p, q) == -1)
				break;
	}
	return -1;
}

int main()
{
	while (true) {
		int m, n;
		scanf("%d %d", &m, &n);
		if (!m && !n)
			break;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++) {
				visited[i][j][north] = visited[i][j][south] = visited[i][j][east] = visited[i][j][west] = false;
				int zeor_or_one;
				scanf("%d", &zeor_or_one);
				store[i][j] = zeor_or_one;
			}
		pair<int, int> b, e;
		char s[8];
		scanf("%d %d %d %d %s", &b.first, &b.second, &e.first, &e.second, s);
		int dir;
		switch (s[0]) {
		case 'n':
			dir = north; break;
		case 's':
			dir = south; break;
		case 'e':
			dir = east; break;
		default:
			dir = west; break;
		}
		printf("%d\n", bfs(m, n, b, e, dir));
	}
	return 0;
}

