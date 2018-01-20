
/*
	11.6.6 Ferry Loading
	PC/UVa IDs: 111106/10261, Popularity: B, Success rate: low Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10261_Ferry_Loading.recursion.cpp

	This simple recursion version was accepted by UVa Online Judge with the running time = 0.008 seconds.
*/

#include <iostream>
#include <vector>
using namespace std;

enum {port_lane, starboard_lane};

bool partition(const vector<int>& cars, int nr_cars, int port, int starboard, vector<int>& lanes);

bool partition(const vector<int>& cars, int nr_cars, int port, int starboard, vector<int>& lanes)
{
	if (port < 0 || starboard < 0)
		return false;
	else if (!nr_cars) {
		lanes[0] = (port >= 0) ? port_lane : starboard_lane;
		return true;
	}
	else {
		if (partition(cars, nr_cars - 1, port - cars[nr_cars - 1], starboard, lanes)) {
			lanes[nr_cars - 1] = port_lane; return true;
		}
		else if (partition(cars, nr_cars - 1, port, starboard - cars[nr_cars - 1], lanes)) {
			lanes[nr_cars - 1] = starboard_lane; return true;
		}
		else
			return false;
	}
}

int main(int /* argc */, char** /* argv */)
{
	int nr_cases;
	cin >> nr_cases;
	for (int c = 0; c < nr_cases; c++) {
		int ferry;
		cin >> ferry;
		ferry *= 100; // convert the ferry length in units of cm
		vector<int> cars;
		while (true) {
			int car;
			cin >> car;
			if (!car)
				break;
			cars.push_back(car);
		}
		int nr_cars = 0;
		for (int length = 0; nr_cars < cars.size(); length += cars[nr_cars++])
			if (length + cars[nr_cars] > ferry * 2)
				break;
		vector<int> lanes(nr_cars);
		for ( ; nr_cars; nr_cars--)
			if (partition(cars, nr_cars, ferry, ferry, lanes))
				break;
		cout << nr_cars << endl;
		int port = 0, starboard = 0;
		for (int i = 0; i < nr_cars; i++) {
			cout << ((lanes[i] == port_lane) ? "port\n" : "starboard\n");
#ifdef DEBUG
			if (lanes[i] == port_lane)
				port += cars[i];
			else
				starboard += cars[i];
#endif
		}
#ifdef DEBUG
		cout << "port = " << port << ", starboard = " << starboard << endl;
#endif
		if (c < nr_cases - 1)
			cout << endl; // separate the output of two consecutive cases by a blank line
	}
	return 0;
}

