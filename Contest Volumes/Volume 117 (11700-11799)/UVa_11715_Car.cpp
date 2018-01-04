
/*
	UVa 11715 - Car

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11715_Car.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int n;
		cin >> n;
		if (!n)
			break;
		double u, v, a, t, s;
		switch (n) {
		case 1:
			cin >> u >> v >> t;
			a = (v - u) / t;
			s = u * t + a * t * t / 2.0;
			cout << "Case " << case_nr << ": " << fixed << setprecision(3) << s << ' ' << setprecision(3) << a << endl;
			break;
		case 2:
			cin >> u >> v >> a;
			t = (v - u) / a;
			s = u * t + a * t * t / 2.0;
			cout << "Case " << case_nr << ": " << fixed << setprecision(3) << s << ' ' << setprecision(3) << t << endl;
			break;
		case 3:
			cin >> u >> a >> s;
			t = (-2.0 * u + sqrt(4.0 * u * u + 8.0 * a * s)) / (2.0 * a);
			v = u + a * t;
			cout << "Case " << case_nr << ": " << fixed << setprecision(3) << v << ' ' << setprecision(3) << t << endl;
			break;
		case 4:
			cin >> v >> a >> s;
			t = (2.0 * v - sqrt(4.0 * v * v - 8.0 * a * s)) / (2.0 * a);
			u = v - a * t;
			cout << "Case " << case_nr << ": " << fixed << setprecision(3) << u << ' ' << setprecision(3) << t << endl;
			break;
		}
	}
	return 0;
}

