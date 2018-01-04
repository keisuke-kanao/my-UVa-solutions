
/*
	UVa 12439 - February 29

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12439_February_29.cpp
*/

#include <cstdio>
#include <cstring>

int get_month(const char* s)
{
	const char* months[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	int m;
	for (m = 0; m < static_cast<int>(sizeof(months) / sizeof(const char*)); m++)
		if (!strcmp(s, months[m]))
			break;
	return m;
}

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

int get_leap_years_between(int syear, int eyear) // return the number of leap years between [syear, eyear)
{
	syear--; eyear--;
	int s = syear / 4 - syear / 100 + syear / 400, e = eyear / 4 - eyear / 100 + eyear / 400;
	return e - s;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int syear, smonth, sday, eyear, emonth, eday;
		char s[16];
		scanf("%s %d, %d", s, &sday, &syear);
		smonth = get_month(s);
		scanf("%s %d, %d", s, &eday, &eyear);
		emonth = get_month(s);
		int nr_leap_years = 0;
		if (syear == eyear) {
			if (is_leap_year(syear) && smonth < 3 && (emonth >= 3 || emonth == 2 && eday == 29))
				nr_leap_years = 1;
		}
		else {
			if (is_leap_year(syear) && smonth < 3)
				nr_leap_years++;
			nr_leap_years += get_leap_years_between(syear + 1, eyear);
			if (emonth == 2 && eday == 29 || is_leap_year(eyear) && emonth >= 3)
				nr_leap_years++;
		}
		printf("Case %d: %d\n", t, nr_leap_years);
	}
	return 0;
}

