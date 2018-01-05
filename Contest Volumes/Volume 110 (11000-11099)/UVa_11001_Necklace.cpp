
/*
	UVa 11001 - Necklace

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11001_Necklace.cpp
*/

#include <iostream>
#include <limits>
#include <cmath>
using namespace std;

int main()
{
	const double eps = numeric_limits<float>::epsilon();
	while (true) {
		int v, v0;
		cin >> v >> v0;
		if (!v && !v0)
			break;
		int i = 1, max_i = 0;
		double dv = static_cast<double>(v), dv0 = static_cast<double>(v0), d, diff, length, max_length = 0.0;
		while (true) {
			d = dv / i - dv0;
			if (d < eps)
				break;
			length = 0.3 * sqrt(d) * i;
#ifdef DEBUG
			cout << i << ' ' << length << endl;
#endif
			diff = length - max_length;
			if (i && fabs(diff) < eps) {
				max_i = 0; break;
			}
			if (diff > eps) {
				max_i = i; max_length = length;
			}
			i++;
		}
		cout << max_i << endl;
	}
	return 0;
}

