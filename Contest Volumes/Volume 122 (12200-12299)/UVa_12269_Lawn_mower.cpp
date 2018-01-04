
/*
	UVa 12269 - Lawn mower

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12269_Lawn_mower.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const double length = 100.0, width = 75.0;
const int nx_max = 1000, ny_max = 1000;

struct pass {
	double l_, h_;

	bool operator<(const pass& p) const {return l_ < p.l_;}
};

pass end_to_ends[nx_max], side_to_sides[ny_max];

bool mow(double h_max, int n, const pass* passes)
{
	const pass& p = passes[0];
	if (passes[0].l_ > 0.0)
		return false;
	double h = passes[0].h_;
	for (int i = 1; i < n; i++) {
		if (h < passes[i].l_)
			return false;
		h = max(h, passes[i].h_);
	}
	return h == h_max;
}

int main()
{
	while (true) {
		int nx, ny;
		double w;
		scanf("%d %d %lf", &nx, &ny, &w);
		if (!nx)
			break;
		for (int i = 0; i < nx; i++) {
			double xi;
			scanf("%lf", &xi);
			end_to_ends[i].l_ = max(0.0, xi - w / 2.0);
			end_to_ends[i].h_ = min(width, xi + w / 2.0);
		}
		for (int i = 0; i < ny; i++) {
			double yi;
			scanf("%lf", &yi);
			side_to_sides[i].l_ = max(0.0, yi - w / 2.0);
			side_to_sides[i].h_ = min(length, yi + w / 2.0);
		}
		sort(end_to_ends, end_to_ends + nx);
		bool yes = mow(width, nx, end_to_ends);
		if (yes) {
			sort(side_to_sides, side_to_sides + ny);
			yes = mow(length, ny, side_to_sides);
		}
		puts((yes) ? "YES" : "NO");
	}
	return 0;
}

