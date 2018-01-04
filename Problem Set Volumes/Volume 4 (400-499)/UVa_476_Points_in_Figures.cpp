
/*
	UVa 476 - Points in Figures: Rectangles

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_476_Points_in_Figures.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

struct rectangle {
	double left_, top_, right_, bottom_;
	rectangle(double left, double top, double right, double bottom) :
		left_(left), top_(top), right_(right), bottom_(bottom) {}
};

int main()
{
	char c;
	vector<rectangle> rectangles;
	while (true) {
		cin >> c;
		if (c == '*')
			break;
		double l, t, r, b;
		cin >> l >> t >> r >> b;
		rectangles.push_back(rectangle(l, t, r, b));
	}
	size_t nr_rectangles = rectangles.size();
	for (int p = 1; ; p++) {
		double x, y;
		cin >> x >> y;
		if (x == 9999.9 && y == 9999.9)
			break;
		bool contained = false;
		for (size_t i = 0; i < nr_rectangles; i++)
			if (x > rectangles[i].left_ && x < rectangles[i].right_ &&
				y > rectangles[i].bottom_ && y < rectangles[i].top_) {
				contained = true;
				cout << "Point " << p << " is contained in figure " << i + 1 << endl;
			}
		if (!contained)
			cout << "Point " << p << " is not contained in any figure\n";
	}
	return 0;
}


