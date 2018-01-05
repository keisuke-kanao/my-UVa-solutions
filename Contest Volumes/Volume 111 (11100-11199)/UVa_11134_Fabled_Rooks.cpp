
/*
	UVa 11134 - Fabled Rooks

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11134_Fabled_Rooks.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int n_max = 5000;

struct rectangle {
	int i_;
	int xl_, yl_, xr_, yr_;
	int x_, y_;
} rectangles[n_max];

bool placed[n_max];

bool compare_by_x(const rectangle& i, const rectangle& j)
{
	return (i.xr_ != j.xr_) ? i.xr_ < j.xr_ : i.xl_ > j.xl_;
}

bool compare_by_y(const rectangle& i, const rectangle& j)
{
	return (i.yr_ != j.yr_) ? i.yr_ < j.yr_ : i.yl_ > j.yl_;
}

bool compare_by_order(const rectangle& i, const rectangle& j)
{
	return i.i_ < j.i_;
}

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		for (int i = 0; i < n; i++) {
			rectangles[i].i_ = i;
			scanf("%d %d %d %d", &rectangles[i].xl_, &rectangles[i].yl_, &rectangles[i].xr_, &rectangles[i].yr_);
		}
		bool possible = true;
		memset(placed, 0, sizeof(placed));
        sort(rectangles, rectangles + n, compare_by_x);
		for (int i = 0; i < n; i++) {
			int j;
			for (j = rectangles[i].xl_; j <= rectangles[i].xr_; j++)
				if (!placed[j]) {
					placed[j] = true;
					rectangles[i].x_ = j;
					break;
				}
			if (j > rectangles[i].xr_) {
				possible = false;
				break;
			}
		}
		if (possible) {
			memset(placed, false, sizeof(placed));
			sort(rectangles, rectangles + n, compare_by_y);
			for(int i = 0; i < n; i++) {
				int j;
				for(j = rectangles[i].yl_; j <= rectangles[i].yr_; j++)
					if (!placed[j]) {
						placed[j] = true;
						rectangles[i].y_ = j;
						break;
					}
				if (j > rectangles[i].yr_) {
					possible = false;
					break;
				}
			}
		}
		if (possible) {
			sort(rectangles, rectangles + n, compare_by_order);
			for (int i = 0; i < n; i++)
				printf("%d %d\n", rectangles[i].x_, rectangles[i].y_);
        }
        else
			puts("IMPOSSIBLE");
	}
	return 0;
}

