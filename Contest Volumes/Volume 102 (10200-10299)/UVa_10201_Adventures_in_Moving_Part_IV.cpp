
/*
	11.6.8 Adventures in Moving: Part IV
	PC/UVa IDs: 111108/10201, Popularity: A, Success rate: low Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10201_Adventures_in_Moving_Part_IV.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
// #include <cassert>
#include <climits>
using namespace std;

struct gas_station {
	int distance;
	int price;

	gas_station(int _distance, int _price) : distance(_distance), price(_price) {}
};

int move_from_waterloo(int gas_tunk, int initial_gas, int final_gas, const vector<gas_station>& gas_stations)
{
/*
	If the price of gas at the current station is higher than the one at the next station,
	refill the gas tunk with gas necessary to reach the next station.
	Otherwise, refill it with extra gas as long as the current price is the lowest of the subsequent 
	stations and the gas tunk has available space.
*/
	int nr_stations = gas_stations.size();
	int distance = 0, destination = gas_stations[nr_stations - 1].distance;
	int gas = initial_gas, cost = 0;
	for (int i = 0; i < nr_stations; i++) {
		gas -= gas_stations[i].distance - distance;
		if (gas < 0)
			return -1;
		if (i < nr_stations - 1) {
			distance = gas_stations[i].distance;
			int d = gas_stations[i + 1].distance - distance;
			int price = gas_stations[i].price;
			if (gas < d) { // first, refill with gas necessary to reach the next station
				if (gas + d > gas_tunk)
					d = gas_tunk - gas;
				gas += d;
//				assert(gas <= gas_tunk);
				cost += price * d;
			}
			// refill with extra gas as long as its price is the lowest of the subsequent stations
			// and the gas tunk has available space
			d = 0;
			int g_max = min(gas_tunk, final_gas + destination - distance) - gas;
			int j = i + 1;
			if (j == nr_stations - 1)
				d = g_max;
			else {
				for ( ; j < nr_stations /* - 1 */ && price < gas_stations[j].price && d < g_max; j++)
					if ((d += gas_stations[j].distance - gas_stations[j - 1].distance) > g_max)
						d = g_max;
			}
			gas += d;
//			assert(gas <= gas_tunk);
			cost += price * d;
		}
		else if (gas < final_gas)
			return -1;
#ifdef DEBUG
		cout << gas_stations[i].distance << ' ' << gas << ' ' << cost << endl;
#endif
	}
	return cost;
}

int main(int /* argc */, char** /* argv */)
{
	string line;
	istringstream iss;
	// read the number of cases
	if (!getline(cin, line))
		return 0;
	iss.str(line);
	int nr_cases;
	iss >> nr_cases;
	iss.clear();
	if (nr_cases)
		getline(cin, line); // skip a blank line
	for (int c = 0; c < nr_cases; c++) {
		// read the distance
		int distance;
		getline(cin, line);
		iss.str(line);
		iss >> distance;
		iss.clear();
		// read gas station specifications
		vector<gas_station> gas_stations;
		while (true) {
			if (!getline(cin, line) || line.empty()) // a blank line
				break;
			int d, p;
			iss.str(line);
			iss >> d >> p;
			iss.clear();
			if (d <= distance)
				gas_stations.push_back(gas_station(d, p));
		}
		gas_stations.push_back(gas_station(distance, INT_MAX));
		int cost = move_from_waterloo(200, 100, 100, gas_stations);
		if (cost != -1)
			cout << cost << endl;
		else
			cout << "Impossible\n";
		if (c < nr_cases - 1)
			cout << endl; // output of each two consecutive cases is separated by a blank line
	}
	return 0;
}

