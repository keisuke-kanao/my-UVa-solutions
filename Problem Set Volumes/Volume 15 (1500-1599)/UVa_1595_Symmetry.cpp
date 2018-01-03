
/*
	UVa 1595 - Symmetry

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1595_Symmetry.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int N_max = 1000;

struct dot {
	int x_, y_;

	dot() {}
	dot(int x, int y) : x_(x), y_(y) {}
	bool operator<(const dot &d) const {return (x_ != d.x_) ? x_ < d.x_ : y_ < d.y_;}
} dots[N_max];

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int N;
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d %d", &dots[i].x_, &dots[i].y_);
		bool yes = true;
		if (N > 1) {
			sort(dots, dots + N);
			int s = dots[0].x_ + dots[N - 1].x_;
			for (int i = 0; i < N; i++)
				if (!binary_search(dots, dots + N, dot(s - dots[i].x_, dots[i].y_))) {
					yes = false; break;
				}
		}
		puts((yes) ? "YES" : "NO");
	}
	return 0;
}

