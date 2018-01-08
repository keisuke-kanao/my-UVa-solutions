
/*
	UVa 10250 - The Other Two Trees

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10250_The_Other_Two_Trees.cpp
*/

/*
	Let (mx, my) be the midpoint of (x1, y1), (x2, y2), then:
		mx = (x1 + x2) / 2, my = (y1 + y2) / 2.
	Let also dx, dy be the horizontal and vertical distance of (x1, y1), (x2, y2) respectively, then:
		dx = x1 - x2, dy = y1 - y2.
	The other two points are:
		(mx - dy / 2, my + dx / 2), (mx + dy / 2, my - dx / 2)
*/

#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	double x1, x2, y1, y2;
	while (cin >> x1 >> y1 >> x2 >> y2) {
		double mx = (x1 + x2) / 2.0, my = (y1 + y2) / 2.0;
		double dx = x1 - x2, dy = y1 - y2;
		double ax1 = mx - dy / 2.0, ay1 = my + dx / 2.0, ax2 = mx + dy / 2.0, ay2 = my - dx / 2.0;
		printf("%.10f %.10f %.10f %.10f\n", ax1, ay1, ax2, ay2);
	}
	return 0;
}

