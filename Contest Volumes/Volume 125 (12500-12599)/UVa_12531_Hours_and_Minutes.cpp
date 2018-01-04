
/*
	UVa 12531 - Hours and Minutes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12531_Hours_and_Minutes.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	const int mark_degree = 6; // angle beteeen the two consecutive marks
	const int angle_max = 180, minutes_max = 60 * 6; // 6 hours
	bool degrees[angle_max + 1]; // degrees[i] is true if there are the cases when two hands of the clock is exactly i degree
	memset(degrees, 0, sizeof(degrees));
	for (int m = 0, minute_hand = 0, hour_hand = 0; m <= minutes_max; m++) {
		minute_hand += mark_degree;
		if (m && !(m % 12))
			hour_hand += mark_degree;
		int d = minute_hand - hour_hand;
		if (d < 0)
			d += angle_max * 2;
		if (d > angle_max)
			d = angle_max * 2 - d;
		degrees[d] = true;
	}
	int a;
	while (scanf("%d", &a) != EOF)
		puts((degrees[a]) ? "Y" : "N");
	return 0;
}

