
/*
	UVa 10566 - Crossed Ladders

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10566_Crossed_Ladders.cpp
*/

/*
From >Our Quest to Solve the UVa ICPC Online Problem Set :: UVa Solutions #10566 - Crossed Ladders
	(http://www.questtosolve.com/browse.php?pid=10566)

Solution Description: 	Binary search on the width of the road. The initial bounds are 0 and min(x,y).

Given the width of the road, and the length of the ladders, you can find the intersection of the two lines. 
If the y-value of the intersection is greater than c, increase the width of the road. Otherwise, decrease it.
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <cmath>
using namespace std;

int main()
{
	double x, y, c;
	while (cin >> x >> y >> c) {
		double l = 0.0, h = min(x, y), w;
		while (true) {
			w = (l + h) / 2.0;
			double sx = sqrt(x * x - w * w), sy = sqrt(y * y - w * w);
			double m = sx * sy / (sx + sy);
			if (fabs(m - c) < numeric_limits<float>::epsilon())
				break;
			else if (m > c)
				l = w;
			else
				h = w;
		}
		cout << fixed << setprecision(3) << w << endl;
	}
	return 0;
}

