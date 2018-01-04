
/*
	UVa 158 - Calendar

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_158_Calendar.cpp
*/

/*
For clarifying the problem description, see: 
	158 - Calendar - UVa OJ Board - UVa Online Judge
		(https://uva.onlinejudge.org/board/viewtopic.php?t=859).

For a specified date, calculated the number of days from the date and the number of stars ('*') that should be printed 
of each anniversary, and then printed the anniversaries that should be printed (i.e., that have at least one stars).
*/

#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
using namespace std;

const int nr_chars_max = 255;

struct anniversary {
	int i_;
	int d_, m_, p_;
	int nr_days_; // number of days from the specified date
	int nr_stars_; // number of stars that should be printed
	anniversary(int i) : i_(i) {}

	bool operator<(const anniversary& a) const
	{
		if (nr_days_ != a.nr_days_)
			return nr_days_ < a.nr_days_;
		else if (!nr_days_)
			return i_ < a.i_;
		else if (nr_stars_ != a.nr_stars_)
			return nr_stars_ > a.nr_stars_;
		else
			return i_ < a.i_;
	}
};

struct description {
	char s_[nr_chars_max + 1];

	description() {}
};

vector<anniversary> anniversaries;
vector<description> descriptions;

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

int get_number_of_days(int year, int month, int date) // return the number of days from the first day of given year
{
	const int nr_days[] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
		// nr_days[i] is the number of days before the first day of i-th month
	const int nr_days_leap_year[] = {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
		// nr_days[i] is the number of days before the first day of i-th month for leap years
	int nd = date;
	nd += (is_leap_year(year)) ? nr_days_leap_year[month] : nr_days[month];
	return nd;
}

const char* stars[] = {
	" *TODAY* ", " *       ", " **      ", " ***     ",
	" ****    ", " *****   ", " ******  ", " ******* "
};

int main()
{
	int year;
	scanf("%d", &year);
	while (getchar() != '\n')
		;
	char s[nr_chars_max + 1];
	int nr_anniversaries = 0;
	while (true) {
		gets(s);
		if (s[0] != 'A')
			break;
		anniversaries.push_back(anniversary(nr_anniversaries)), descriptions.push_back(description());
		char* p;
		anniversary& a = anniversaries.back();
		a.d_ = strtol(&s[1], &p, 10);
		a.m_ = strtol(p, &p, 10);
		a.p_ = strtol(p, &p, 10);
		while (isspace(*p))
			p++;
		strcpy(descriptions.back().s_, p);
		nr_anniversaries++;
	}
	bool printed = false;
	while (s[0] != '#') {
		if (printed)
			putchar('\n');
		else
			printed = true;
		char* p;
		int date = strtol(&s[1], &p, 10);
		int month = strtol(p, NULL, 10);
		int nr_days = get_number_of_days(year, month, date);
		for (int i = 0; i < nr_anniversaries; i++) {
			anniversary& a = anniversaries[i];
			int nr = (a.m_ < month || a.m_ == month && a.d_ < date) ?
				get_number_of_days(year) + get_number_of_days(year + 1, a.m_, a.d_) : get_number_of_days(year, a.m_, a.d_);
			a.nr_days_ = nr - nr_days;
			a.nr_stars_ = (a.nr_days_ <= 7) ? a.p_ - a.nr_days_ + 1: -1;
		}
		sort(anniversaries.begin(), anniversaries.end());
		printf("Today is:%3d%3d\n", date, month);
		for (int i = 0; i < nr_anniversaries; i++) {
			const anniversary& a = anniversaries[i];
			if (/* a.nr_days_ > 7 || */ a.nr_stars_ <= 0)
				break;
			printf("%3d%3d%s%s\n", a.d_, a.m_, ((a.nr_days_) ? stars[a.nr_stars_] : stars[0]), descriptions[a.i_].s_);
		}
		gets(s);
	}
	return 0;
}

