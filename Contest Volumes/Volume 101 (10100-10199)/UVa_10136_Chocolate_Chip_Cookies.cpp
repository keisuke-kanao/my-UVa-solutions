
/*
	13.6.4 Chocolate Chip Cookies
	PC/UVa IDs: 111304/10136, Popularity: C, Success rate: average Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10136_Chocolate_Chip_Cookies.cpp
*/

/*
	Choose a pair of points of chips in turn.
	Calculate the distance between them.
	If the distance is equal to the diameter of the cutter (5 cm), then:
		Place the cutter such that its center is on the middle point of the two point.
		See if the other points are in the cutter.
	Else if the distance is less than the diameter of the cutter, then:
		Place the cutter such that its center crosses perpendicularly at the middle point of line 
			that connects the two points.
		See if the other points are in the cutter.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

// const double pi = 3.14159265358979323846;
const double pi = 2.0 * acos(0.0);

struct point {
	double x, y;

	point() : x(0.0), y(0.0) {}
	point(double _x, double _y) : x(_x), y(_y) {}
};

struct line {
	double a; // x-coefficient
	double b; // y-coefficient
	double c; // constant term
};

void points_to_line(const point& p1, const point& p2, line& l)
{
	if (p1.x == p2.x) {
		l.a = 1; l.b = 0; l.c = -p1.x;
	}
	else {
		l.b = 1;
		l.a = -(p1.y - p2.y)/(p1.x - p2.x);
		l.c = -(l.a * p1.x) - l.b * p1.y;
	}
}

double square_distance(const point& a, const point& b)
{
	double dx = a.x - b.x, dy = a.y - b.y;
	return dx * dx + dy * dy;
}

int get_center_points_of_circles(double diameter, const point& p1, const point& p2,
	point& c1, point& c2)
{
	double sd = square_distance(p1, p2), dd = diameter * diameter;
	point m((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0);
	if (sd > dd)
		return 0;
	else if (sd == dd) {
		c1 = m; // middle point btween p1 and p2 is the center of a circle
#ifdef DEBUG
		cout << "p1(" << p1.x << ", " << p1.y << "), p2(" << p2.x << ", " << p2.y <<
			"), c1(" << c1.x << ", " << c1.y << ")\n";
#endif
		return 1;
	}
	else {
		line l;
		points_to_line(p1, p2, l);
		double slope_angle = atan2(-l.a, l.b);
		double radius = diameter / 2.0;
		double d = sqrt(radius * radius - square_distance(p1, m));
			// distance between the center of the circles and the middle point btween p1 and p2
		// Since the line between the center of the circles and the middle point is perpendicular to l,
		// x/y components of the distance are calcualted using (slope angle + pi / 2)
		double dx = d * cos(slope_angle + pi / 2.0), dy = d * sin(slope_angle + pi / 2.0);
		c1 = point(m.x - dx, m.y - dy);
		c2 = point(m.x + dx, m.y + dy);
#ifdef DEBUG
		cout << "p1(" << p1.x << ", " << p1.y << "), p2(" << p2.x << ", " << p2.y <<
			"), c1(" << c1.x << ", " << c1.y << "), c2(" << c2.x << ", " << c2.y << ")\n";
#endif
		return 2;
	}
}

int count_in_points(double radius, const point &c, const vector<point>& points)
{
	int count = 0;
	for (int i = 0; i < points.size(); i++)
		if (square_distance(c, points[i]) <= radius * radius)
			count++;
	return count;
}

int main(int /* argc */, char** /* argv */)
{
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int nr_cases;
	iss >> nr_cases;
	iss.clear();
	if (!nr_cases)
		return 0;
	getline(cin, line); // skip a blank line
	for (int c = 0; c < nr_cases; c++) {
		vector<point> points;
		while (getline(cin, line)) {
			if (line.empty()) // a blank line between two consecutive test cases
				break;
			iss.str(line);
			point p;
			iss >> p.x >> p.y;
			points.push_back(p);
			iss.clear();
		}
		int in_points_max = 1;
		for (int i = 0; i < points.size() - 1; i++)
			for (int j = i + 1; j < points.size(); j++) {
				point c1, c2;
				// get the center points of the circles such that the two points are on their circumferences
				int circles = get_center_points_of_circles(5.0, points[i], points[j], c1, c2);
				if (!circles)
					continue;
				// see if the other points are inside the circle
				in_points_max = max(in_points_max, count_in_points(2.5, c1, points));
				if (circles > 1)
					in_points_max = max(in_points_max, count_in_points(2.5, c2, points));
			}
		cout << in_points_max << endl;
		if (c < nr_cases - 1)
			cout << endl; // print a blank line between the two consecutive cases
	}
	return 0;
}

