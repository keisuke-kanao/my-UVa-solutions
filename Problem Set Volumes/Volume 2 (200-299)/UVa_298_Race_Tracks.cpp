
/*
	UVa 298 - Race Tracks

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_298_Race_Tracks.cpp
*/

#include <queue>
#include <limits>
#include <cstdio>
using namespace std;

const int infinite = numeric_limits<int>::max();
const int X_max = 30, Y_max = 30, v_min = -3, v_max = 3, vc_min = -1, vc_max = 1;
const int nr_vs = v_max - v_min + 1;

int nr_hops[X_max][Y_max][nr_vs][nr_vs];
	// nr_hops[x][y][vx - v_min][vy - v_min] is the number of hops at (x, y) with the velocity of (vx, vy)

bool obstacles[X_max][Y_max]; // obstacles[x][y] is true if there is an obstacle at (x, y)

struct path {
	int x_, y_, vx_, vy_, nr_;
	path(int x, int y, int vx, int vy, int nr) : x_(x), y_(y), vx_(vx), vy_(vy), nr_(nr) {}
};

int main()
{
	int N;
	scanf("%d", &N);
	while (N--) {
		int X, Y;
		scanf("%d %d", &X, &Y);
		for (int i = 0; i < X; i++)
			for (int j = 0; j < Y; j++) {
				obstacles[i][j] = false;
				for (int vi = 0; vi < nr_vs; vi++)
					for (int vj = 0; vj < nr_vs; vj++)
						nr_hops[i][j][vi][vj] = infinite;
			}
		int sx, sy, fx, fy;
		scanf("%d %d %d %d", &sx, &sy, &fx, &fy);
		int P;
		scanf("%d", &P);
		while (P--) {
			int x1, x2, y1, y2;
			scanf("%d %d %d %d", &x1, &x2, &y1, &y2);
			for (int i = x1; i <= x2; i++)
				for (int j = y1; j <= y2; j++)
					obstacles[i][j] = true;
		}
		queue<path> q;
		nr_hops[sx][sy][-v_min][-v_min] = 0;
		q.push(path(sx, sy, -v_min, -v_min, 0));
		while (!q.empty()) {
			path p = q.front();
			q.pop();
#ifdef DEBUG
			printf("(%d, %d) with v(%d, %d): %d\n", p.x_, p.y_, p.vx_ + v_min, p.vy_ + v_min, p.nr_);
#endif
			int nr = p.nr_ + 1;
			for (int vcx = vc_min; vcx <= vc_max; vcx++) {
				int vx = p.vx_ + v_min + vcx;
				if (vx < v_min || vx > v_max)
					continue;
				int x = p.x_ + vx;
				if (x < 0 || x >= X)
					continue;
				for (int vcy = vc_min; vcy <= vc_max; vcy++) {
					int vy = p.vy_ + v_min + vcy;
					if (vy < v_min || vy > v_max)
						continue;
					int y = p.y_ + vy;
					if (y < 0 || y >= Y || obstacles[x][y])
						continue;
					if (nr_hops[x][y][vx - v_min][vy - v_min] <= nr)
						continue;
#ifdef DEBUG
			printf("  (%d, %d) with v(%d, %d): %d\n", x, y, vx + v_min, vy + v_min, nr);
#endif
					nr_hops[x][y][vx - v_min][vy - v_min] = nr;
					q.push(path(x, y, vx - v_min, vy - v_min, nr));
				}
			}
		}
		int nr = infinite;
		for (int vi = 0; vi < nr_vs; vi++)
			for (int vj = 0; vj < nr_vs; vj++)
				if (nr_hops[fx][fy][vi][vj] < nr)
					nr = nr_hops[fx][fy][vi][vj];
		if (nr < infinite)
			printf("Optimal solution takes %d hops.\n", nr);
		else
			puts("No solution.");
	}
	return 0;
}

