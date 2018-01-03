
/*
	UVa 866 - Intersecting Line Segments

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_866_Intersecting_Line_Segments.cpp
*/

#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

struct point{
	int x, y;
};

struct segment{
	point s, e;
};

inline bool in_range(int l, int u, int n)
{
	return n >= l && n <= u;
}

int direction(const point& p1, const point& p2, const point& p3)
{
	return (p1.x - p2.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p2.y);
}

bool on_segment(const point& p1, const point& p2, const point& p3)
{
	return in_range(min(p1.x, p2.x), max(p1.x, p2.x), p3.x) && in_range(min(p1.y, p2.y), max(p1.y, p2.y), p3.y);
}

bool segment_intersect(const point& p1, const point& p2, const point& p3, const point& p4)
{
	int d1 = direction(p3, p4, p1), d2 = direction(p3, p4, p2), d3 = direction(p1, p2, p3), d4 = direction(p1, p2, p4);
	if((d1 > 0 && d2 < 0 || d1 < 0 && d2 > 0) && (d3 > 0 && d4 < 0 || d3 < 0 && d4 > 0))
		return true;
/*
From the problem descrition:
	It is assumed, as a simplification, that no coincidences may occur between coordinates of singular 
	points (intersections or end points).
*/
/*
	if (d1 == 0 && on_segment(p3, p4, p1))
		return true;
	if (d2 == 0 && on_segment(p3, p4, p2))
		return true;
	if (d3 == 0 && on_segment(p1, p2, p3))
		return true;
	if (d4 == 0 && on_segment(p1, p2, p4))
		return true;
*/
	return false;
}

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		int N;
		scanf("%d", &N);
		vector<segment> segments(N);
		for (int i = 0; i < N; i++)
			scanf("%d %d %d %d", &segments[i].s.x, &segments[i].s.y, &segments[i].e.x, &segments[i].e.y);
		int nr_segments = N;
		for (int i = 0; i < N - 1; i++)
			for (int j = i + 1; j < N; j++)
				if (segment_intersect(segments[i].s, segments[i].e, segments[j].s, segments[j].e))
					nr_segments += 2;
		printf("%d\n", nr_segments);
		if (nr_cases)
			putchar('\n');
	}
	return 0;
}

