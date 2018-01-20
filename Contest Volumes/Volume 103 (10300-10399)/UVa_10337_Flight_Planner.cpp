
/*
	UVa 10337 - Flight Planner

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10337_Flight_Planner.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const int nr_altitudes = 10;

int flight_planner(int x, const vector< vector<int> >& windstrengths, vector< vector<int> >& fuels)
{
	if (x < 2)
		return 0;
	const int climb = 60, hold = 30, sink = 20;
	fuels[nr_altitudes - 2][1] = climb - windstrengths[nr_altitudes - 1][0];
	for (int j = 2; j < x; j++)
		for (int i = 0; i < nr_altitudes; i++) {
			int upper_left = (i && fuels[i - 1][j - 1]) ?
				fuels[i - 1][j - 1] + sink - windstrengths[i - 1][j - 1] : INT_MAX;
			int left = (fuels[i][j - 1]) ? fuels[i][j - 1] + hold - windstrengths[i][j - 1] : INT_MAX;
			int lower_left = (i < nr_altitudes - 1 && fuels[i + 1][j - 1]) ?
				fuels[i + 1][j - 1] + climb - windstrengths[i + 1][j - 1] : INT_MAX;
			int min_fuel = min(upper_left, left);
			min_fuel = min(min_fuel, lower_left);
			if (min_fuel != INT_MAX)
				fuels[i][j] = min_fuel;
		}
	return fuels[nr_altitudes - 2][x - 1] + sink - windstrengths[nr_altitudes - 2][x - 1];
}

int main(int /* argc */, char** /* argv */)
{
	int nr_cases;
	if (cin >> nr_cases)
		while (nr_cases--) {
			int x; // distance (multiple of 100)
			cin >> x;
			x /= 100;
			vector< vector<int> > windstrengths(nr_altitudes, vector<int>(x));
			for (int i = 0; i < nr_altitudes; i++) // read windstrengths from altitude 9 to zero
				for (int j = 0; j < x; j++)
					cin >> windstrengths[i][j];
			vector< vector<int> > fuels(nr_altitudes, vector<int>(x, 0));
			cout << flight_planner(x, windstrengths, fuels) << endl << endl;
		}
	return 0;
}

