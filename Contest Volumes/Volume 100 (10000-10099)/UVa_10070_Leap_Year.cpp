
/*
	UVa 10070 - Leap Year or Not Leap Year and ...

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10070_Leap_Year.cpp
*/

#include <iostream>
#include <string>
using namespace std;

bool is_divisible_by_3(const char* s, size_t length)
{
	int n = 0;
	while (*s)
		n += *s++ - '0';
	return !(n % 3);
}

bool is_divisible_by_4(const char* s, size_t length)
{
	// Any number is divisible by 4 if its last two digit is divisible by 4.
	s += length - 2;
	int n = *s++ - '0';
	n *= 10;
	n += *s - '0';
	return !(n % 4);
}

bool is_divisible_by_5(const char* s, size_t length)
{
	const char* p = s + length - 1;
	return *p == '0' || *p == '5';
}

bool is_divisible_by_11(const char* s, size_t length)
{
	const char* p = s + length - 1;
	int n = 0;
	for (int i = 0; p >= s; i++, p--) {
		int j = *p - '0';
		if (i & 1)
			n -= j;
		else
			n += j;
	}
	return !(n % 11);
}

bool is_divisible_by_15(const char* s, size_t length)
{
	return is_divisible_by_3(s, length) && is_divisible_by_5(s, length);
}

bool is_divisible_by_55(const char* s, size_t length)
{
	return is_divisible_by_5(s, length) && is_divisible_by_11(s, length);
}

bool is_divisible_by_100(const char* s, size_t length)
{
	return *(s + length - 1) == '0' && *(s + length - 2) == '0';
}

bool is_divisible_by_400(const char* s, size_t length)
{
	return is_divisible_by_100(s, length) && is_divisible_by_4(s, length - 2);
}

int main()
{
	string year;
	bool printed = false;
	while (cin >> year) {
		if (printed)
			cout << endl;
		const char* s = year.c_str();
		size_t length = year.length();
		bool leap_year = false, huluculu_festival_year = false, bulukulu_festival_year = false;
		if (is_divisible_by_4(s, length) &&
			(!is_divisible_by_100(s, length) || is_divisible_by_400(s, length))) {
			leap_year = true;
			cout << "This is leap year.\n";
		}
		if (is_divisible_by_15(s, length)) {
			huluculu_festival_year = true;
			cout << "This is huluculu festival year.\n";
		}
		if (leap_year && is_divisible_by_55(s, length)) {
			bulukulu_festival_year = true;
			cout << "This is bulukulu festival year.\n";
		}
		if (!leap_year && !huluculu_festival_year && !bulukulu_festival_year)
			cout << "This is an ordinary year.\n";
		printed = true;
	}
	return 0;
}

