
/*
	UVa 688 - Mobile Phone Coverage

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_688_Mobile_Phone_Coverage.cpp
*/

#include <cstdio>
#include <algorithm>
using namespace std;

const int n_max = 100;

struct point {
	double x_, y_;
};

struct event {
	int ri_; // index of rects[]
	bool type_; // type of event, 0 for lower-left, 1 for upper-right
	event() {}
	event(int ri, int type) : ri_(ri), type_(type) {}
};

point rects[n_max][2]; // each rectangle consists of 2 points, rects[][0] for lower-left, rects[][1] for upper-right
event vertical_events[n_max * 2]; // events for sweeping in horizontal (x) direction
event horizontal_events[n_max * 2]; // events for sweeping in vertical (y) direction
bool active_set[n_max]; // active_set[i] is true if rects[i] is in the active set, false otherwise

bool compare_x(const event& a, const event& b)
{
	return rects[a.ri_][a.type_].x_ < rects[b.ri_][b.type_].x_;
}

bool compare_y(const event& a, const event& b)
{
	return rects[a.ri_][a.type_].y_ < rects[b.ri_][b.type_].y_;
}

int main()
{
	for (int sn = 1; ; sn++) {
		int n, nr_events = 0;
		scanf("%d", &n);
		if (!n)
			break;
		for (int i = 0; i < n; i++) {
			active_set[i] = false;
			double x, y, r;
			scanf("%lf %lf %lf", &x, &y, &r);
			rects[i][0].x_ = x - r; rects[i][0].y_ = y - r; // lower-left coordinate
			rects[i][1].x_ = x + r; rects[i][1].y_ = y + r; // upper-right coordinate
			vertical_events[nr_events] = horizontal_events[nr_events] = event(i, 0);
			nr_events++;
			vertical_events[nr_events] = horizontal_events[nr_events] = event(i, 1);
			nr_events++;
		}
		sort(vertical_events, vertical_events + nr_events, compare_x);
		sort(horizontal_events, horizontal_events + nr_events, compare_y);
		double area = 0.0;
		active_set[vertical_events[0].ri_] = true;
		for (int i = 1; i < nr_events; i++) { // sweep in horizontal (x) direction
			const event& e = vertical_events[i];
			int nr_overlapped = 0; // count of how many rectangles are currently overlapped
			double dx = rects[e.ri_][e.type_].x_ - rects[vertical_events[i - 1].ri_][vertical_events[i - 1].type_].x_;
				// distance between the current sweep line and the previous one
			if (dx != 0.0) {
				double ys;
				for (int j = 0; j < nr_events; j++) // sweep in vertical (y) direction
					if (active_set[horizontal_events[j].ri_]) {
						if (horizontal_events[j].type_ == 0) {
							if (!nr_overlapped++)
								ys = rects[horizontal_events[j].ri_][0].y_; // start of a block
						}
						else {
							if (!--nr_overlapped) { // end of the block
								double dy= rects[horizontal_events[j].ri_][1].y_ - ys;
								area += dx * dy;
							}
						}
					}
			}
			active_set[e.ri_] = e.type_ == 0;
		}
		printf("%d %.2lf\n", sn, area);
	}
	return 0;
}

