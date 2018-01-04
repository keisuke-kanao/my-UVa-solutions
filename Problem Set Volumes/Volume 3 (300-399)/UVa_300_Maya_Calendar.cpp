
/*
	UVa 300 - Maya Calendar

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_300_Maya_Calendar.cpp
*/

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;

int main()
{
	const int nr_haab_days_per_year = 365, nr_days_per_month = 20, nr_haab_months = 19;
	const char* haab_month_names[nr_haab_months] = {
		"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", "yax",
		"zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", "uayet"
	};
	const int nr_tzolkin_days_per_year = 260, nr_tzolkin_days = 20, nr_tzolkin_periods = 13;
	const char* tzolkin_day_names[nr_tzolkin_days] = {
		"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok",
		"chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"
	};

	map<string, int> haab_months;
	for (int i = 0; i < nr_haab_months; i++)
		haab_months.insert(make_pair(haab_month_names[i], i * 20));
	int n;
	cin >> n;
	cout << n << endl;
	while (n--) {
		int haab_day, haab_year;
		string haab_month;
		char c;
		cin >> haab_day >> c >> haab_month >> haab_year;
		transform(haab_month.begin(), haab_month.end(), haab_month.begin(), (int(*)(int))tolower);
		int nr_days = haab_year * nr_haab_days_per_year + haab_months[haab_month] + haab_day;
#ifdef DEBUG
		cout << nr_days << endl;
#endif
		int tzolkin_year = nr_days / nr_tzolkin_days_per_year;
		int tzolkin_period = nr_days % nr_tzolkin_periods + 1;
		int tzolkin_day = nr_days % nr_tzolkin_days;
		cout << tzolkin_period << ' ' << tzolkin_day_names[tzolkin_day] << ' ' << tzolkin_year << endl;
	}
	return 0;
}

