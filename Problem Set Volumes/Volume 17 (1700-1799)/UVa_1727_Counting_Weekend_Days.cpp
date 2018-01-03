
/*
	UVa 1727 - Counting Weekend Days

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_1727_Counting_Weekend_Days.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_days_of_week = 7, nr_months = 12;

int get_day_of_week(const char* d)
{
	const char* days_of_week[] = {
		"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"
	};

	for (int i = 0; i < nr_days_of_week; i++)
		if (!strcmp(d, days_of_week[i]))
			return i;
	return -1;
}

int get_days_of_month(const char* m)
{
	const struct month {
		const char* name_;
		int nr_days_;
	} months[] = {
		{"JAN", 31}, {"FEB", 28}, {"MAR", 31}, {"APR", 30},
		{"MAY", 31}, {"JUN", 30}, {"JUL", 31}, {"AUG", 31},
		{"SEP", 30}, {"OCT", 31}, {"NOV", 30}, {"DEC", 31}
	};

	for (int i = 0; i < nr_months; i++)
		if (!strcmp(m, months[i].name_))
			return months[i].nr_days_;
	return -1;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		char MTH[3 + 1], DAY[3 + 1];
		scanf("%s %s", MTH, DAY);
		int m = get_days_of_month(MTH), d = get_day_of_week(DAY);
		int nr = (m + d) / nr_days_of_week + (m + d + 1) / nr_days_of_week;
		if (d == 6) // "SAT"
			nr--;
		printf("%d\n", nr);
	}
	return 0;
}

