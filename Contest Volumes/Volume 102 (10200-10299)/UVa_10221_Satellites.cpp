
/*
	UVa 10221 - Satellites

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10221_Satellites.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

/*
	1 degree = pi / 180, 1 minute = degree / 60 = pi / 10800
	distance = 2 * (s + r) * sin(a / 2), chord = (s + r) * a,  a in radian
*/

int main()
{
	const double pi = 2.0 * acos(0.0);
	const double r = 6440.0;
	int s, a;
	string unit;
	while (cin >> s >> a >> unit) {
		double angle;
		if (unit == "deg") {
			a %= 360;
			if (a > 180)
				a = 360 - a;
			angle = (a * pi) / 180.0;
		}
		else {
			a %= 21600;
			if (a > 10800)
				a = 21600 - a;
			angle = (a * pi) / 10800.0;
		}
		cout << fixed << setprecision(6) << (r + s) * angle << ' ' <<
			setprecision(6) << 2.0 * (r + s) * sin(angle / 2.0) << endl;
	}
	return 0;
}

