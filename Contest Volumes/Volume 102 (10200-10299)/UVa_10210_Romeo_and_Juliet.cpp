
/*
	UVa 10210 - Romeo and Juliet !

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10210_Romeo_and_Juliet.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	const double pi = 2.0 * acos(0.0);
	double x1, y1, x2, y2, cmd, enf;
	while (cin >> x1 >> y1 >> x2 >> y2 >> cmd >> enf) {
		double h = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		double f = h * sin((180.0 - cmd - enf) * pi / 180.0) / (sin(cmd * pi / 180.0) * sin(enf * pi / 180.0));
		cout << fixed << setprecision(3) << f << endl;
	}
	return 0;
}

