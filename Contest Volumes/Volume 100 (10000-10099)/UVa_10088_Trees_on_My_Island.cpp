
/*
	14.7.7 Trees on My Island
	PC/UVa IDs: 111407/10088, Popularity: C, Success rate: average Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10088_Trees_on_My_Island.cpp
*/

/*
PickÅfs theorem gives an exact relation between the area of a lattice polygon P (a
non-intersecting figure whose vertices all lie on lattice points) and the number of lattice
points on/in the polygon.Suppose there are I(P) lattice points inside of P and B(P)
lattice points on the boundary of P. Then the area A(P) of P is given by
	A(P) = I(P) + B(P)/2 - 1
*/

#include <iostream>
#include <vector>
#include <utility>
#include <cstdio>
using namespace std;

struct point {
	long long x, y;

	point() : x(0), y(0) {}
	point(long long _x, long long _y) : x(_x), y(_y) {}
	point(const point &p) : x(p.x), y(p.y) {}
	bool operator==(const point& p) const {return x == p.x && y == p.y;}
};

inline long long get_abs(long long x)
{
	return (x >= 0) ? x : -x;
}

long long gcd(long long x, long long y)
{
	if (x < y)
		return gcd(y, x);
	if (!y)
		return x;
	else
		return gcd(y, x % y);
}

pair<long long, long long> polygon_area(const vector<point>& points)
{
	long long area = 0, boundary_points = 0;
	for (int i = 0; i < points.size(); i++) {
		int j = (i + 1) % points.size();
		area += points[i].x * points[j].y - points[j].x * points[i].y;
		long long dx = get_abs(points[i].x - points[j].x), dy = get_abs(points[i].y - points[j].y);
		boundary_points += gcd(dx, dy);
	}
	return make_pair(get_abs(area / 2), boundary_points);
}

int main(int /* argc */, char** /* argv */)
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		vector<point> points;
		while (n--) {
			point p;
			cin >> p.x >> p.y;
			points.push_back(p);
		}
		pair<long long, long long> ar_bp = polygon_area(points);
		cout << ar_bp.first + 1 - ar_bp.second / 2 << endl;
	}
	return 0;
}

