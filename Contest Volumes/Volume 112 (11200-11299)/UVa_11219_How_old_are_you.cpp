
/*
	UVa 11219 - How old are you?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11219_How_old_are_you.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		char c;
		int c_day, c_month, c_year, b_day, b_month, b_year;
		cin >> c_day >> c >> c_month >> c >> c_year;
		cin >> b_day >> c >> b_month >> c >> b_year;
		int age = -1;
		if (c_year > b_year) {
			age = c_year - b_year;
			if (c_month < b_month || c_month == b_month && c_day < b_day)
				age--;
		}
		else if (c_year == b_year) {
			if (c_month > b_month || c_month == b_month && c_day >= b_day)
				age = 0;
		}
		cout << "Case #" << case_nr << ": ";
		if (age == -1)
			cout << "Invalid birth date\n";
		else if (age > 130)
			cout << "Check birth date\n";
		else
			cout << age << endl;
	}
	return 0;
}

