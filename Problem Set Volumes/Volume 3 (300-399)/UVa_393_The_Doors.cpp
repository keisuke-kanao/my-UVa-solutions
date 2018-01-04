
/*
	UVa 393 - The Doors

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_393_The_Doors.cpp

	ACM Mid-Central Regionals 1996, Problem #2
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidCen/1996/index.html)
*/

#include <algorithm>
#include <limits>
#include <cstdio>
#include <cmath>
using namespace std;

const double infinite = numeric_limits<double>::max(), epsilon = numeric_limits<double>::epsilon();
const int nr_walls_max = 18, nr_ys = 4;

struct wall {
	double x_;
	double ys_[nr_ys];
} walls[nr_walls_max + 2] = { // walls[0] is the chamber's left wall and walls[nr_walls_max + 1] is the chamber's right wall
	{0.0, {5.0, 5.0, 5.0, 5.0}}
};

int nr_walls;
double distances[nr_walls_max + 2][nr_ys][nr_walls_max + 2][nr_ys];
	// distances[si][sj][ei][ej] is the distance between walls[si].ys_[sj] and walls[ei].ys_[ej]

double get_distance(int si, int sj, int ei, int ej)
{
	double dx = walls[ei].x_ - walls[si].x_, dy = walls[ei].ys_[ej] - walls[si].ys_[sj], dm  = dy / dx;
	for (int i = si + 1; i < ei; i++) {
		double y = walls[si].ys_[sj] + dm * (walls[i].x_ - walls[si].x_);
		if (y >= walls[i].ys_[0] - epsilon && y <= walls[i].ys_[1] + epsilon ||
			y >= walls[i].ys_[2] - epsilon && y <= walls[i].ys_[3] + epsilon)
			;
		else
			return infinite;
	}
	return sqrt(dx * dx + dy * dy);
}

int main()
{
	while (true) {
		scanf("%d", &nr_walls);
		if (nr_walls == -1)
			break;
		for (int i = 1; i <= nr_walls; i++) {
			wall& w = walls[i];
			scanf("%lf %lf %lf %lf %lf", &w.x_, &w.ys_[0], &w.ys_[1], &w.ys_[2], &w.ys_[3]);
		}
		nr_walls++;
		walls[nr_walls].x_ = 10.0;
		walls[nr_walls].ys_[0] = walls[nr_walls].ys_[1] = walls[nr_walls].ys_[2] = walls[nr_walls].ys_[3] = 5.0;
		for (int si = 0; si <= nr_walls; si++)
			for (int sj = 0; sj < nr_ys; sj++)
				for (int ei = 0; ei <= nr_walls; ei++)
					for (int ej = 0; ej < nr_ys; ej++)
						distances[si][sj][ei][ej] = (ei > si) ? get_distance(si, sj, ei, ej) : infinite;
		for (int mi = 1; mi <= nr_walls; mi++)
			for (int mj = 0; mj < nr_ys; mj++)
				for (int ei = 1; ei <= nr_walls; ei++)
					for (int ej = 0; ej < nr_ys; ej++)
						if (distances[0][0][mi][mj] < infinite && distances[mi][mj][ei][ej] < infinite)
							distances[0][0][ei][ej] = min(distances[0][0][ei][ej], distances[0][0][mi][mj] + distances[mi][mj][ei][ej]);
		printf("%.2lf\n", distances[0][0][nr_walls][0]);
	}
	return 0;
}

