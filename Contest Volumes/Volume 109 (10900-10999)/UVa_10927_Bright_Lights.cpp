
/*
	UVa 10927 - Bright Lights

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10927_Bright_Lights.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N_max = 100000;

struct pole {
	int X_, Y_, Z_, x_, y_, gcd_;

	bool operator<(const pole& p) const {
		if (x_ != p.x_)
			return x_ < p.x_;
		if (y_ != p.y_)
			return y_ < p.y_;
		if (gcd_ != p.gcd_)
			return gcd_ < p.gcd_;
		return Z_ < p.Z_;
	}
} poles[N_max];

int invisibles[N_max];

bool compare_invisible(int i, int j)
{
	return (poles[i].X_ != poles[j].X_) ? poles[i].X_ < poles[j].X_ : poles[i].Y_ < poles[j].Y_;
}

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int main()
{
	for (int ds = 1; ; ds++) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		for (int i = 0; i < n; i++) {
			pole& p = poles[i];
			scanf("%d %d %d", &p.X_, &p.Y_, &p.Z_);
			p.gcd_ = gcd(abs(p.X_), abs(p.Y_));
			p.x_ = p.X_ / p.gcd_, p.y_ = p.Y_ / p.gcd_;
		}
		printf("Data set %d:\n", ds);
		sort(poles, poles + n);
#ifdef DEBUG
		for (int i = 0; i < n; i++)
			printf("%d %d %d %d\n", poles[i].x_, poles[i].y_, poles[i].gcd_, poles[i].Z_);
#endif
		int nr_invisibles = 0, x = poles[0].x_, y = poles[0].y_, Z = poles[0].Z_;
		for (int i = 1; i < n; i++) {
			if (poles[i].x_ != x || poles[i].y_ != y) {
				x = poles[i].x_, y = poles[i].y_, Z = poles[i].Z_;
			}
			else {
				if (poles[i].Z_ <= Z)
					invisibles[nr_invisibles++] = i;
				else
					Z = poles[i].Z_;
			}
		}
		if (nr_invisibles) {
			sort(invisibles, invisibles + nr_invisibles, compare_invisible);
			puts("Some lights are not visible:");
			for (int i = 0; i < nr_invisibles; i++)
				printf("x = %d, y = %d%c\n", poles[invisibles[i]].X_, poles[invisibles[i]].Y_,
					((i < nr_invisibles - 1) ? ';' : '.'));
		}
		else
			puts("All the lights are visible.");
	}
	return 0;
}

