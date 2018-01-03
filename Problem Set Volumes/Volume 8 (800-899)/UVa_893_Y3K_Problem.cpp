
/*
	UVa 893 - Y3K Problem

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_893_Y3K_Problem.cpp
*/

#include <iostream>
using namespace std;

inline bool is_leap_year(int year)
{
	if (!(year % 400))
		return true;
	else if (!(year % 100))
		return false;
	else if (!(year % 4))
		return true;
	else
		return false;
}

int get_number_of_days(int year) // return the number of days of given year
{
	return (is_leap_year(year)) ? 366 : 365;
}

int get_number_of_days(int year, int month, int day) // return the number of days from the first day of given year
{
	const int nr_days[] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
		// nr_days[i] is the number of days before the first day of i-th month
	const int nr_days_leap_year[] = {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
		// nr_days[i] is the number of days before the first day of i-th month for leap years
	int nd = day;
	nd += (is_leap_year(year)) ? nr_days_leap_year[month] : nr_days[month];
	return nd;
}

void get_month_day(int year, int nr_days, int& month, int& day) // return the month and day from the number of days of given year
{
	const int nr_month_days[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
		// nr_month_days[i] is the number of days up to i-th month
	const int nr_month_days_leap_year[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};
		// nr_month_days[i] is the number of days up to i-th month for leap years
	const int* month_days = (is_leap_year(year)) ? nr_month_days_leap_year : nr_month_days;
	for (month = 1; ; month++)
		if (month_days[month] >= nr_days)
			break;
	day = nr_days - month_days[month - 1];
}

int main()
{
	while (true) {
		int n, d, m, y;
		cin >> n >> d >> m >> y;
		if (!n && !d && !m && !y)
			break;
		n += get_number_of_days(y, m, d);
		for (int nd = get_number_of_days(y); n > nd; nd = get_number_of_days(++y))
			n -= nd;
		get_month_day(y, n, m, d);
		cout << d << ' ' << m << ' ' << y << endl;
	}
	return 0;
}

