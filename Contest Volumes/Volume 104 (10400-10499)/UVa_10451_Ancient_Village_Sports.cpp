
/*
	UVa 10451 - Ancient Village Sports

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10451_Ancient_Village_Sports.cpp
*/

/*
	Let r be the radius of a circle that circumscribes the polygon, then:
		r =sqrt(A / (n * sin(pi / n) * cos(pi / n)))
	Area of the circumscribed circle = pi * r^2.
	Area of the inscribed circle = pi * (r cos(pi / n))^2.
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	const double pi = 2.0 * acos(0.0);
	for (int case_nr = 1; ; case_nr++) {
		double n, a;
		cin >> n >> a;
		if (n < 3.0)
			break;
		double r = sqrt(a / (n * sin(pi / n) * cos(pi / n)));
		double h = r * cos(pi / n);
		double spectators_area = pi * r * r - a, officials_area = a - pi * h * h;
		cout << "Case " << case_nr << ": " <<
			fixed << setprecision(5) << spectators_area << ' ' << setprecision(5) << officials_area << endl;
	}
	return 0;
}

