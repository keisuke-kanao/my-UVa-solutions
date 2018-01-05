
/*
	UVa 11012 - Cosmic Cabbages

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11012_Cosmic_Cabbages.cpp
*/

/*
The distance between 2 points can be simplified with these 4 possibilities.
max(x[i]+y[i]+z[i])-min(x[j]+y[j]+z[j]);
max(x[i]+y[i]-z[i])-min(x[j]+y[j]-z[j]);
max(x[i]-y[i]+z[i])-min(x[j]-y[j]+z[j]);
max(x[i]-y[i]-z[i])-min(x[j]-y[j]-z[j]);
for all i and j.
and each case takes O(n) time. So the complexity becomes O(n), and the max value of the four cases is the answer.
Maintain a Max and Min for all these 4 values . Output the global max.
*/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int n_max = 100000, p_max = 100000000;

struct point {
	int x_, y_, z_;
} points[n_max];

int main()
{
	int N;
	scanf("%d", &N);
	for (int cn = 1; cn <= N; cn++) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d %d %d", &points[i].x_, &points[i].y_, &points[i].z_);
		int max_d = 0;
#ifdef __BRUTE_FORCE__
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++)
				max_d = max(max_d, abs(points[i].x_ - points[j].x_) + abs(points[i].y_ - points[j].y_) + abs(points[i].z_ - points[j].z_));
#else
		int min_p = p_max * 3 + 1, max_p = -(p_max * 3 + 1);
		for (int i = 0; i < n; i++) {
			int p = points[i].x_ + points[i].y_ + points[i].z_;
			min_p = min(min_p, p);
			max_p = max(max_p, p);
		}
#ifdef DEBUG
		printf("%d %d %d\n", max_p, min_p, max_p - min_p);
#endif
		max_d = max(max_d, max_p - min_p);

		min_p = p_max * 3 + 1, max_p = -(p_max * 3 + 1);
		for (int i = 0; i < n; i++) {
			int p = points[i].x_ + points[i].y_ - points[i].z_;
			min_p = min(min_p, p);
			max_p = max(max_p, p);
		}
#ifdef DEBUG
		printf("%d %d %d\n", max_p, min_p, max_p - min_p);
#endif
		max_d = max(max_d, max_p - min_p);

		min_p = p_max * 3 + 1, max_p = -(p_max * 3 + 1);
		for (int i = 0; i < n; i++) {
			int p = points[i].x_ - points[i].y_ + points[i].z_;
			min_p = min(min_p, p);
			max_p = max(max_p, p);
		}
#ifdef DEBUG
		printf("%d %d %d\n", max_p, min_p, max_p - min_p);
#endif
		max_d = max(max_d, max_p - min_p);

		min_p = p_max * 3 + 1, max_p = -(p_max * 3 + 1);
		for (int i = 0; i < n; i++) {
			int p = points[i].x_ - points[i].y_ - points[i].z_;
			min_p = min(min_p, p);
			max_p = max(max_p, p);
		}
#ifdef DEBUG
		printf("%d %d %d\n", max_p, min_p, max_p - min_p);
#endif
		max_d = max(max_d, max_p - min_p);
#endif
		printf("Case #%d: %d\n", cn, max_d);
	}
	return 0;
}

