
/*
	UVa 10589 - Area

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10589_Area.cpp
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	while (true) {
		int n;
		double a;
		cin >> n >> a;
		if (!n)
			break;
		double sa = a * a;
		int m = 0;
		for (int i = 0; i < n; i++) {
			double x, y;
			cin >> x >> y;
			if (x * x + y * y <= sa && (x - a) * (x - a) + y * y <= sa &&
				(x - a) * (x - a) + (y - a) * (y - a) <= sa && x * x + (y - a) * (y - a) <= sa)
				m++;
		}
		cout << fixed << setprecision(5) << (sa * m) / n << endl;
	}
	return 0;
}

