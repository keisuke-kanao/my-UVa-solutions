
/*
	UVa 11677 - Alarm Clock

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11677_Alarm_Clock.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	while (true) {
		const int minutes_per_day = 1440;
		int h1, h2, m1, m2;
		cin >> h1 >> m1 >> h2 >> m2;
		if (!h1 && !m1 && !h2 && !m2)
			break;
		int minutes = (h2 * 60 + m2) - (h1 * 60 + m1);
		if (minutes < 0)
			minutes += minutes_per_day;
		cout << minutes << endl;
	}
	return 0;
}

