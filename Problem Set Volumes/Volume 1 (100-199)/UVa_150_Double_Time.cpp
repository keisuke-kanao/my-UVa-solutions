
/*
	UVa 150 - Double Time

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_150_Double_Time.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_chars_max = 15, nr_days_of_week = 7, nr_months = 12;

const char* day_names[nr_days_of_week] = {
	"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

const char* month_names[nr_months] = {
	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
};

int nr_days[2][nr_months] = {
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} // leap year
};

int nr_days_of_year[2][nr_months] = {
	{31, 59, 90,120,151,181,212,243,273,304,334,365},
	{31, 60, 91,121,152,182,213,244,274,305,335,366} // leap year
};

const int start_year = 1582, start_day_of_week = 5 /* Friday */,
	julian_calendar_start_days = 273 + 5 /* 5 October */, gregorian_calendar_start_days = 273 + 15 /* 15 October */;

int get_day_of_week(const char* day)
{
	for (int i = 0; i < nr_days_of_week; i++)
		if (!strcmp(day, day_names[i]))
			return i;
	return -1;
}

int get_month(const char* month)
{
	for (int i = 0; i < nr_months; i++)
		if (!strcmp(month, month_names[i]))
			return i;
	return -1;
}

bool julian_calendar_leap_year(int year)
{
	return !(year % 4);
}

int julian_calendar_number_of_leap_years(int syear, int eyear) // number of leap years between [syear, eyear)
{
	syear--; eyear--;
	return eyear / 4 - syear / 4;
}

int julian_calendar_number_of_days(int year, int month, int day)
{
	int nr_days = (year - start_year) * 365 + julian_calendar_number_of_leap_years(start_year, year) -
		julian_calendar_start_days;
	int leap_year = julian_calendar_leap_year(year) ? 1 : 0;
	if (month)
		nr_days += nr_days_of_year[leap_year][month - 1];
	nr_days += day;
	return nr_days;
}

bool gregorian_calendar_leap_year(int year)
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

int gregorian_calendar_number_of_leap_years(int syear, int eyear) // return the number of leap years between [syear, eyear)
{
	syear--; eyear--;
	return (eyear / 4 - eyear / 100 + eyear / 400) - (syear / 4 - syear / 100 + syear / 400);
}

int gregorian_calendar_number_of_days(int year, int month, int day)
{
	int nr_days = (year - start_year) * 365 + gregorian_calendar_number_of_leap_years(start_year, year) -
		gregorian_calendar_start_days;
	int leap_year = gregorian_calendar_leap_year(year) ? 1 : 0;
	if (month)
		nr_days += nr_days_of_year[leap_year][month - 1];
	nr_days += day;
	return nr_days;
}

int main()
{
	while (true) {
		int day_of_week, day, month, year, leap_year, j_days, g_days;
		char day_name[nr_chars_max + 1], month_name[nr_chars_max + 1];
		scanf("%s", day_name);
		if (day_name[0] == '#')
			break;
		scanf("%d %s %d", &day, month_name, &year);
		day_of_week = get_day_of_week(day_name), month = get_month(month_name);
		j_days = julian_calendar_number_of_days(year, month, day);
		if ((start_day_of_week + j_days) % nr_days_of_week == day_of_week) { // julian calendar
			g_days = j_days + gregorian_calendar_start_days;
			for (year = start_year; ; year++) {
				leap_year = gregorian_calendar_leap_year(year) ? 1 : 0;
				if (g_days <= nr_days_of_year[leap_year][nr_months - 1])
					break;
				g_days -= nr_days_of_year[leap_year][nr_months - 1];
			}
			for (month = 0; ; month++) {
				if (g_days <= nr_days[leap_year][month])
					break;
				g_days -= nr_days[leap_year][month];
			}
			printf("%s %d %s %d\n", day_name, g_days, month_names[month], year);
		}
		else { // gregorian calendar
			g_days = gregorian_calendar_number_of_days(year, month, day);
			j_days = g_days + julian_calendar_start_days;
			for (year = start_year; ; year++) {
				leap_year = julian_calendar_leap_year(year) ? 1 : 0;
				if (j_days <= nr_days_of_year[leap_year][nr_months - 1])
					break;
				j_days -= nr_days_of_year[leap_year][nr_months - 1];
			}
			for (month = 0; ; month++) {
				if (j_days <= nr_days[leap_year][month])
					break;
				j_days -= nr_days[leap_year][month];
			}
			printf("%s %d* %s %d\n", day_name, j_days, month_names[month], year);
		}
	}
	return 0;
}

