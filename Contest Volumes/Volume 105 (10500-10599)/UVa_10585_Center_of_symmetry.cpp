
/*
	UVa 10585 - Center of symmetry

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10585_Center_of_symmetry.cpp
*/

/*
Sort the input points based on x-axis first. If there are ties, sort by y-axis, 
then greedyly compute the mid point of point 1 and n, and then check whether points (2,n-1),(3,n-2)... and so on 
have exactly the same middle point...
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 10000;

struct point {
	int x_, y_;

	bool operator<(const point& p) const {
		if (x_ < p.x_)
			return true;
		else if (x_ > p.x_)
			return false;
		else
			return y_ < p.y_;
	}
} points[n_max];

int main()
{
	int c;
	scanf("%d", &c);
	while (c--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d %d", &points[i].x_, &points[i].y_);
		sort(points, points + n);
		bool yes = true;
		int mx = points[0].x_ + points[n - 1].x_, my = points[0].y_ + points[n - 1].y_;
		for (int i = 1, j = n - 2; i <= j && yes; i++, j--)
			if (points[i].x_ + points[j].x_ != mx || points[i].y_ + points[j].y_ != my)
				yes = false;
		puts((yes) ? "yes" : "no");
	}
	return 0;
}

