
/*
	UVa 11389 - The Buss Driver Problem

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11389_The_Buss_Driver_Problem.cpp
*/

#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

const int n_max = 100;
int morning_routes[n_max], evening_routes[n_max];

int main()
{
	while (true) {
		int n, d, r;
		cin >> n >> d >> r;
		if (!n && !d && !r)
			break;
		for (int i = 0; i < n; i++)
			cin >> morning_routes[i];
		for (int i = 0; i < n; i++)
			cin >> evening_routes[i];
		sort(morning_routes, morning_routes + n);
		sort(evening_routes, evening_routes + n, greater<int>());
		int overtime = 0;
		for (int i = 0; i < n; i++) {
			int total_route = morning_routes[i] + evening_routes[i];
			if (total_route > d)
				overtime += total_route - d;
		}
		cout << overtime * r << endl;
	}
	return 0;
}

