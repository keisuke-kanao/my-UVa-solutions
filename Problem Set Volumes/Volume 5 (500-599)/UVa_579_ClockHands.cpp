
/*
	UVa 579 - ClockHands

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_579_ClockHands.cpp
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;

int main()
{
	int h, m;
	char c;
	while (cin >> dec >> h >> c >> m) {
		if (!h && !m)
			break;
		double h_angle = 30.0 * static_cast<double>(h) + 0.5 * static_cast<double>(m);
		double m_angle = 6.0 * static_cast<double>(m);
		double angle = h_angle - m_angle;
		if (angle < 0.0)
			angle = -angle;
		if (angle > 180.0)
			angle = 360.0 - angle;
		printf("%.3f\n", angle);
	}
	return 0;
}

