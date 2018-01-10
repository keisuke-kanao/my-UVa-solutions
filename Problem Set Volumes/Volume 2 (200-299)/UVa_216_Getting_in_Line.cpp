
/*
	UVa 216 - Getting in Line

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_216_Getting_in_Line.cpp
*/

#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <cstdio>
#include <cmath>
using namespace std;

typedef pair<int, int> location;

double euclidean_distance(const location& i, const location& j)
{
	double dx = static_cast<double>(i.first - j.first), dy = static_cast<double>(i.second - j.second);
	return sqrt(dx * dx + dy * dy);
}

void connect_locations(int nr_locations, int previous_location, const vector<location>& locations,
	int nr_connected /* number of locations connected so far */, vector<bool>& connected,
	vector<int>& orders, vector<int>& min_orders, double length, double& min_length)
{
	if (length > min_length) // no need to futher search
		return;
	else if (nr_connected == nr_locations) { // all of the locations have been connected
		if (length < min_length) {
			min_length = length;
			min_orders = orders;
		}
	}
	else {
		for (int i = 0; i < nr_locations; i++)
			if (!connected[i]) {
				connected[i] = true;
				orders[nr_connected] = i;
				double l = (nr_connected) ? euclidean_distance(locations[previous_location], locations[i]) + 16.0 : 0.0;
				connect_locations(nr_locations, i, locations, nr_connected + 1, connected,
					orders, min_orders, length + l, min_length);
				connected[i] = false;
			}
	}
}

int main()
{
	for (int ns = 1; ; ns++) {
		int nr_locations;
		cin >> nr_locations;
		if (!nr_locations)
			break;
		vector<location> locations(nr_locations);
		for (int i = 0; i < nr_locations; i++)
			cin >> locations[i].first >> locations[i].second;
		vector<bool> connected(nr_locations, false);
			// connected[i] is true if locations[i] has already been connected
		vector<int> orders(nr_locations), min_orders(nr_locations);
			// orders[i] is index to locations that is connected in i-th order
		double min_length = numeric_limits<double>::max();
		connect_locations(nr_locations, -1, locations, 0, connected, orders, min_orders, 0.0, min_length);
		printf("**********************************************************\nNetwork #%d\n", ns);
		for (int i = 0; i < nr_locations - 1; i++) {
			const location& current = locations[min_orders[i]];
			const location& next = locations[min_orders[i + 1]];
			printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2lf feet.\n",
				current.first, current.second, next.first, next.second, euclidean_distance(current, next) + 16.0);
		}
		printf("Number of feet of cable required is %.2lf.\n", min_length);
	}
	return 0;
}

