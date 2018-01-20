
/*
	13.6.8 How Big Is It?
	PC/UVa IDs: 111308/10012, Popularity: B, Success rate: low Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10012_How_Big_Is_It.cpp
*/

#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cfloat>
#include <cstdio>
#include <cmath>
using namespace std;

const int nr_circles_max = 8;

inline double square(double d)
{
	return d * d;
}

inline double square_distance(double dx, double dy)
{
	return dx * dx + dy * dy;
}

double circle_distance(double r1, double r2)
{
	// calculate the distance between the centers of adjacent circles whose radii are r1 and r2
	double d1 = r1 + r2, d2 = r1 - r2;
	return sqrt(d1 * d1 - d2 * d2);
}

double calculate_width(int n, const vector<double>& rs, const vector< vector<double> >& ds, vector<int> cs)
{
	// cs should be a copy since it may be destroyed during the calculation
	int i, j, k, l;
	double width, side;

	for (i = 1; i < n; i++) {
		for (j = i - 1; j >= 0; j--) {
			if (cs[j] == -1)
				continue;
			// try to place cs[i] such that it is left tangent to cs[j]
			double w = ds[cs[j]][cs[i]];
			bool overlapped = false;
			for (l = j, k = j - 1; k >= 0; k--) { // see whether cs[i] is overlapped with cs[j - 1], cs[j - 2], ..., cs[0]
				if (cs[k] == -1)
					continue;
				w += ds[cs[k]][cs[l]]; // distance between cs[i] and cs[j]
				if (square_distance(w, rs[cs[k]] - rs[cs[i]]) < square(rs[cs[k]] + rs[cs[i]])) { // cs[i] is overlapped with cs[k]
					overlapped = true; break;
				}
				l = k;
			}
			if (!overlapped)
				break;
			cs[j] = -1; // mark cs[j] as invalid (i.e., they are not tangent to their adjacent circles)
		}
	}
	// scan cs[] from left to right and find the circle that is tangent to the left side of rectangle
	int left_i = 0;
	side = rs[cs[left_i]];
	width = 0.0;
	for (i = left_i; i < n - 1; i = j) {
		for (j = i + 1; j < n && cs[j] == -1; j++)
			;
		if (j < n) {
			width += ds[cs[i]][cs[j]];
			if (side < rs[cs[j]] - width) {
				left_i = j;
				side = rs[cs[j]]; width = 0.0;
			}
		}
	}
	// scan cs[] from rigtht to left and find the circle that is tangent to the rigtht side of rectangle
	int right_i = n - 1;
	side = rs[cs[right_i]];
	width = 0.0;
	for (i = right_i; i; i = j) {
		for (j = i - 1; j >= 0 && cs[j] == -1; j--)
			;
		if (j >= 0) {
			width += ds[cs[j]][cs[i]];
			if (side < rs[cs[j]] - width) {
				right_i = j;
				side = rs[cs[j]]; width = 0.0;
			}
		}
	}
	width = rs[cs[left_i]] + rs[cs[right_i]];
	for (i = left_i; i <= right_i; i = j) { // calculate the width between cs[left_i] and cs[right_i]
		for (j = i + 1; j <= right_i && cs[j] == -1; j++)
			;
		if (j <= right_i)
			width += ds[cs[i]][cs[j]];
	}
#ifdef DEBUG
	cout << width << endl;
#endif
	return width;
}

void get_box_width(int i_th_circle, int nr_circles,
	const vector<double>& radii, const vector< vector<double> >& distances,
	bitset<nr_circles_max>& used, vector<int>& circles, double& min_width)
{
	if (i_th_circle == nr_circles) {
		double width = calculate_width(nr_circles, radii, distances, circles);
		if (width < min_width)
			min_width = width;
	}
	else {
		for (int i = 0; i < nr_circles; i++)
			if (!used.test(i)) {
				used.set(i);
				circles[i_th_circle] = i;
				get_box_width(i_th_circle + 1, nr_circles, radii, distances, used, circles, min_width);
				used.reset(i);
			}
	}
}

int main(int /* argc */, char** /* argv */)
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		int nr_circles;
		cin >> nr_circles;
		vector<double> radii(nr_circles);
		for (int i = 0; i < nr_circles; i++)
			cin >> radii[i];
		vector< vector<double> > distances(nr_circles, vector<double>(nr_circles, 0.0));
		for (int i = 0; i < nr_circles; i++)
			for (int j = 0; j < nr_circles; j++)
				if (i != j)
					distances[i][j] = circle_distance(radii[i], radii[j]);
		bitset<nr_circles_max> used;
		vector<int> circles(nr_circles);
		double min_width = DBL_MAX;
		get_box_width(0, nr_circles, radii, distances, used, circles, min_width);
		printf("%.3f\n", min_width);
	}
	return 0;
}

