
/*
	14.7.2 The Closest Pair Problem
	PC/UVa IDs: 111402/10245, Popularity: A, Success rate: low Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10245_The_Closest_Pair_Problem.cpp
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdio>
#include <cfloat>
#include <cmath>
using namespace std;

double euclidean_distance(const pair<double, double>& i, const pair<double, double>& j)
{
	double dx = i.first - j.first, dy = i.second - j.second;
	return sqrt(dx * dx + dy * dy);
}

bool compare_point(const pair<double, double>& i, const pair<double, double>& j)
{
	return i.first < j.first;
}

int main(int /* argc */, char** /* argv */)
{
	while (true) {
		int nr_points;
		cin >> nr_points;
		if (!nr_points)
			break;
		vector< pair<double, double> > points(nr_points);
		for (int i = 0; i < nr_points; i++)
			cin >> points[i].first >> points[i].second;
		if (nr_points == 1) {
			printf("INFINITY\n");
			continue;
		}
		sort(points.begin(), points.end(), compare_point); // sort the points by non-decreasing x-coordinate
		double min_distance = DBL_MAX;
		for (int i = 0; i < nr_points - 1; i++)
			for (int j = i + 1; j < nr_points; j++) {
				if (points[j].first - points[i].first >= min_distance)
					break;
				min_distance = min(min_distance, euclidean_distance(points[i], points[j]));
			}
		if (min_distance >= 10000.0)
			printf("INFINITY\n");
		else
			printf("%.4f\n", min_distance);
	}
	return 0;
}

