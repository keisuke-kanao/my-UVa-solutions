
/*
	UVa 10573 - Geometry Paradox

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10573_Geometry_Paradox.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

int main()
{
	const double pi = 2.0 * acos(0.0);
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int n;
	iss >> n;
	iss.clear();
	while (n--) {
		getline(cin, line);
		iss.str(line);
		double r1, r2;
		iss >> r1;
		double area;
		if (iss >> r2) { // r1, r2
			area = 2.0 * pi * r1 * r2;
		}
		else { // t
			// (t / 2)^2 = 4 * r1 * r2
			area = pi * r1 * r1 / 8.0;
		}
		iss.clear();
		cout << fixed << setprecision(4) << area << endl;
	}
	return 0;
}

