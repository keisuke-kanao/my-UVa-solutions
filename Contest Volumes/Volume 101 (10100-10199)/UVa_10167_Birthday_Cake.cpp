
/*
	13.6.5 Birthday Cake
	PC/UVa IDs: 111305/10167, Popularity: C, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10167_Birthday_Cake.cpp
*/

/*
	For each cherry, calculate the angle of the line that connects the center of the cake (0, 0) and 
	its position.
	Calculate the average value for all angles of cherries.
	Find a pair of angles between which the average angle resides.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <cfloat>
#include <cmath>
using namespace std;

// const double pi = 3.14159265358979323846;
const double pi = 2.0 * acos(0.0);

double atan2(int y, int x)
{
	return atan2(static_cast<double>(y), static_cast<double>(x));
}

pair<int, int> get_slopes(double angle, double smaller_angle, double larger_angle)
{
	pair<int, int> slope; // return a pair of integers, first is A, second is B
	if (angle >= -DBL_EPSILON && angle <= DBL_EPSILON || // angle == 0 or pi or -pi
		angle >= pi - DBL_EPSILON && angle <= pi || angle >= -pi && angle <= -pi + DBL_EPSILON)
		slope = pair<int, int>(0, 1);
	else if (angle >= pi * 0.25 - DBL_EPSILON && angle <= pi * 0.25 + DBL_EPSILON || // angle == pi / 4 or -pi * (3 / 4)
		angle >= -pi * 0.75 - DBL_EPSILON && angle <= -pi * 0.75 + DBL_EPSILON)
		slope = pair<int, int>(-1, 1);
	else if (angle >= pi * 0.5 - DBL_EPSILON && angle <= pi * 0.5 + DBL_EPSILON || // angle == pi / 2 or -pi / 2
		angle >= -pi * 0.5 - DBL_EPSILON && angle <= -pi * 0.5 + DBL_EPSILON)
		slope = pair<int, int>(1, 0);
	else if (angle >= pi * 0.75 - DBL_EPSILON && angle <= pi * 0.75 + DBL_EPSILON || // angle == pi * (3 / 4) or -pi / 4
		angle >= -pi * 0.25 - DBL_EPSILON && angle <= -pi * 0.25 + DBL_EPSILON)
		slope = pair<int, int>(1, 1);
	else if (angle > DBL_EPSILON && angle < pi * 0.25 - DBL_EPSILON) { // betwenn 0 and pi / 4
		slope = pair<int, int>(-static_cast<int>(500.0 * tan(angle)), 500);
		if (atan2(-slope.first, slope.second) <= smaller_angle)
			slope.first--;
	}
	else if (angle > pi * 0.25 + DBL_EPSILON && angle < pi * 0.5 - DBL_EPSILON) { // between pi / 4 and pi / 2
		slope = pair<int, int>(-500, static_cast<int>(500.0 / tan(angle)));
		if (atan2(-slope.first, slope.second) >= larger_angle)
			slope.second++;
	}
	else if (angle > pi * 0.5 + DBL_EPSILON && angle < pi * 0.75 - DBL_EPSILON) { // between pi / 2 and pi * (3 / 4)
		slope = pair<int, int>(-500, static_cast<int>(500.0 / tan(angle)));
		if (atan2(-slope.first, slope.second) <= smaller_angle)
			slope.second--;
	}
	else if (angle > pi * 0.75 + DBL_EPSILON && angle < pi - DBL_EPSILON) { // between pi * (3 / 4) and pi
		slope = pair<int, int>(static_cast<int>(500.0 * tan(angle)), -500);
		if (atan2(-slope.first, slope.second) >= larger_angle)
			slope.first--;
	}
	else if (angle > -pi + DBL_EPSILON && angle < -pi * 0.75 - DBL_EPSILON) { // between -pi and -pi * (3 / 4)
		slope = pair<int, int>(static_cast<int>(500.0 * tan(angle)), -500);
		if (atan2(-slope.first, slope.second) <= smaller_angle)
			slope.first++;
	}
	else if (angle > -pi * 0.75 + DBL_EPSILON && angle < -pi * 0.5 - DBL_EPSILON) { // between -pi * (3 / 4) and -pi / 2
		slope = pair<int, int>(500, -static_cast<int>(500.0 / tan(angle)));
		if (atan2(-slope.first, slope.second) >= larger_angle)
			slope.second--;
	}
	else if (angle > -pi * 0.5 + DBL_EPSILON && angle < -pi * 0.45 - DBL_EPSILON) { // between -pi / 2 and -pi / 4
		slope = pair<int, int>(500, -static_cast<int>(500.0 / tan(angle)));
		if (atan2(-slope.first, slope.second) <= smaller_angle)
			slope.second++;
	}
	else { // between -pi / 4 and 0
		slope = pair<int, int>(-static_cast<int>(500.0 * tan(angle)), 500);
		if (atan2(-slope.first, slope.second) >= larger_angle)
			slope.first++;
	}
	return slope;
}

int main(int /* argc */, char** /* argv */)
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		vector< pair<double, double> > positions;
		vector<double> angles;
		for (int i = 0; i < 2 * n; i++) {
			pair<double, double> p;
			cin >> p.first >> p.second;
			positions.push_back(p);
			angles.push_back(atan2(p.second, p.first));
		}
		double average_angle = accumulate(angles.begin(), angles.end(), 0.0) / angles.size();
		int smaller_angle_p = -1, larger_angle_p = -1;
		double smaller_angle = -DBL_MAX, larger_angle = DBL_MAX;
		for (int i = 0; i < positions.size(); i++)
			if (angles[i] > average_angle) {
				if (angles[i] < larger_angle) {
					larger_angle_p = i; larger_angle = angles[i];
				}
			}
			else /* if (angles[i] < average_angle) */ {
				if (angles[i] > smaller_angle) {
					smaller_angle_p = i; smaller_angle = angles[i];
				}
			}
#ifdef DEBUG
		cout << "average angle = " << average_angle << ", between (" << positions[smaller_angle_p].first << ", " <<
			positions[smaller_angle_p].second << ") and (" << positions[larger_angle_p].first << ", " <<
			positions[larger_angle_p].second << ")\n";
#endif
		pair<int, int> slope = get_slopes(average_angle, smaller_angle, larger_angle);
		cout << slope.first << ' ' << slope.second << endl;
	}
	return 0;
}

