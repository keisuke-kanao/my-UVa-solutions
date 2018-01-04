
/*
	UVa 460 - Overlapping Rectangles

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_460_Overlapping_Rectangles.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

struct point {
	int x, y;
};

struct rectangle {
	point ll, ur;
};

bool point_in_rectangle(const point& p, const rectangle& r)
{
	return p.x > r.ll.x && p.x < r.ur.x && p.y > r.ll.y && p.y < r.ur.y;
}

bool is_part(const rectangle& r1, const rectangle& r2)
{
	if (r1.ll.x == r2.ll.x && r1.ur.x == r2.ur.x &&
		(r1.ll.y >= r2.ll.y && r1.ur.y <= r2.ur.y || r2.ll.y >= r1.ll.y && r2.ur.y <= r1.ur.y))
		return true;
	else if (r1.ll.y == r2.ll.y && r1.ur.y == r2.ur.y &&
		(r1.ll.x >= r2.ll.x && r1.ur.x <= r2.ur.x || r2.ll.x >= r1.ll.x && r2.ur.x <= r1.ur.x))
		return true;
	else
		return false;
}

bool is_upper_or_lower(const rectangle& r1, const rectangle& r2)
{
	return r1.ll.x == r2.ll.x && r1.ur.x == r2.ur.x &&
		(r1.ll.y > r2.ll.y && r1.ll.y < r2.ur.y || r2.ll.y > r1.ll.y && r2.ll.y < r1.ur.y);
}

bool is_left_or_right(const rectangle& r1, const rectangle& r2)
{
	return r1.ll.y == r2.ll.y && r1.ur.y == r2.ur.y &&
		(r1.ll.x > r2.ll.x && r1.ll.x < r2.ur.x || r2.ll.x > r1.ll.x && r2.ll.x < r1.ur.x);
}

bool is_center(const rectangle& r1, const rectangle& r2)
{
	return r2.ll.x >= r1.ll.x && r2.ur.x <= r1.ur.x && r1.ll.y >= r2.ll.y && r1.ur.y <= r2.ur.y;
}

bool is_point(const rectangle& r1, const rectangle& r2)
{
	point ul, lr;
	ul.x = r1.ll.x; ul.y = r1.ur.y;
	lr.x = r1.ur.x; lr.y = r1.ll.y;
	return point_in_rectangle(r1.ll, r2) || point_in_rectangle(r1.ur, r2) ||
		point_in_rectangle(ul, r2) || point_in_rectangle(lr, r2);
}

bool is_overlapped(const rectangle& r1, const rectangle& r2)
{
	if (is_part(r1, r2))
		return true;
	else if (is_upper_or_lower(r1, r2))
		return true;
	else if (is_left_or_right(r1, r2))
		return true;
	else if (is_center(r1, r2) || is_center(r2, r1))
		return true;
	else if (is_point(r1, r2) || is_point(r2, r1))
		return true;
	else
		return false;
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		rectangle r1, r2, r;
		cin >> r1.ll.x >> r1.ll.y >> r1.ur.x >> r1.ur.y;
		cin >> r2.ll.x >> r2.ll.y >> r2.ur.x >> r2.ur.y;
		if (is_overlapped(r1, r2))
			cout << max(r1.ll.x, r2.ll.x) << ' ' << max(r1.ll.y, r2.ll.y) << ' ' <<
				min(r1.ur.x, r2.ur.x) << ' ' << min(r1.ur.y, r2.ur.y) << endl;
		else
			cout << "No Overlap\n";
		if (t)
			cout << endl;
	}
	return 0;
}

