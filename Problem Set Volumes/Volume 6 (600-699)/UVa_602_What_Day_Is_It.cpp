
/*
	UVa 602 - What Day Is It?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_602_What_Day_Is_It.cpp
*/

#include <iostream>
using namespace std;

const char* month_names[] = {
	"January", "February", "March", "April", "May", "June",
	"July", "August","September", "October", "November", "December"
};
const char* weekday_names[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
const int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap_year(int year)
{
	if (year <= 1752)
		return !(year % 4);
	else {
		if (!(year % 400))
			return true;
		else if (!(year % 100))
			return false;
		else
			return (!(year % 4));
	}
}

bool is_valid_date(int year, int month, int day)
{
	if (year == 1752 && month == 9 && day >= 3 && day <= 13)
		return false;
	if (month > 12)
		return false;
	int d = month_days[month - 1];
	if (month == 2 && is_leap_year(year))
		d++;
	return (day <= d) ? true : false;
}

const char* day_of_week(int year, int month, int day)
{
/*
	Zeller's congruence is used to calculate the day of the week.
*/
	bool gregorian = true; // true for Gregorian calender, false for Julian calender
	if (year < 1752)
		gregorian = false;
	else if (year == 1752) {
		if (month < 9)
			gregorian = false;
		else if (month == 9) {
			if (day < 14)
				gregorian = false;
		}
	}
	int q = day;
	if (month < 3) {
		year--; month += 12;
	}
	int m = month, k = year % 100, j = year / 100;
	int h = q + 13 * (m + 1) / 5 + k + k / 4;
	if (gregorian)
		h += j / 4 + 5 * j;
	else
		h += 5 + 6 * j;
	return weekday_names[h % 7];
}

int main()
{
	while (true) {
		int month, day, year;
		cin >> month >> day >> year;
		if (!month && !day && !year)
			break;
		if (is_valid_date(year, month, day))
			cout << month_names[month - 1] << ' ' << day << ", " << year << " is a " <<
				day_of_week(year, month, day) << endl;
		else
			cout << month << '/' << day << '/' << year << " is an invalid date.\n";
	}
	return 0;
}

