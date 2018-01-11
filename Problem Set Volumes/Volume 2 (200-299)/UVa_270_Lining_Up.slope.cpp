
/*
	UVa 270 - Lining Up

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_270_Lining_Up.slope.cpp

	An accepted solution.
	This implementation assumes that all points are unique.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cfloat>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

struct point {
	double x_, y_;

	point() : x_(0), y_(0) {}
	point(double x, double y) : x_(x), y_(y) {}
	point(const point &p) : x_(p.x_), y_(p.y_) {}
	bool operator==(const point& p) const {return x_ == p.x_ && y_ == p.y_;}
};

const int nr_points_max = 700;
point points[nr_points_max];
double slopes[nr_points_max];

double calculate_slope(const point& p1, const point& p2)
{
	double dx = p1.x_ - p2.x_, dy = p1.y_ - p2.y_;
	if (dx == 0.0)
		return FLT_MAX;
	return dy / dx;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int nr_cases;
	cin >> nr_cases;
	string line;
	getline(cin, line); // skip '\n'
	getline(cin, line); // skip a blank line
	while (nr_cases--) {
		int nr_points = 0;
		while (true) {
			getline(cin, line);
			if (line.empty())
				break;
			istringstream iss(line);
			int x, y;
			iss >> x >> y;
			points[nr_points].x_ = static_cast<double>(x);
			points[nr_points].y_ = static_cast<double>(y);
			nr_points++;
		}
		if (nr_points < 3)
			cout << nr_points << endl << endl;
		else {
			int max_nr_collinear = 2;
			for (int i = 0; i < nr_points; i++) {
				int j, k;
				for (j = 0, k = 0; j < i; j++, k++)
					slopes[k] = calculate_slope(points[i], points[j]);
				for (j = i + 1; j < nr_points; j++, k++)
					slopes[k] = calculate_slope(points[i], points[j]);
				sort(slopes, slopes + nr_points - 1);
				int nr_collinear = 0;
				for (j = 0, k = 1; k < nr_points - 1; k++)
					if (fabs(slopes[j] - slopes[k]) > FLT_EPSILON) {
						if (j + 1 < k)
							max_nr_collinear = max(max_nr_collinear, k - j + 1);
						j = k;
					}
				if (j + 1 < k)
					max_nr_collinear = max(max_nr_collinear, k - j + 1);
			}
			cout << max_nr_collinear << endl;
		}
		if (nr_cases)
			cout << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

