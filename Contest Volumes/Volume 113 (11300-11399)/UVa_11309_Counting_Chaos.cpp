
/*
	UVa 11309 - Counting Chaos

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11309_Counting_Chaos.cpp
*/

#include <iostream>
using namespace std;

const int hr_max = 24, minutes_max = 60;
const int clock_max = hr_max * minutes_max;
bool palindromic_clocks[clock_max];
	// palindromic_clocks[i] is true if the clock of i minutes (i >= 0) is palindromic
const int divisors[] = {minutes_max * 10, minutes_max, 10};

bool is_palindromic(int m)
{
	char s[4];
	char* p = s;
	for (size_t i = 0; i < sizeof(divisors) / sizeof(divisors[0]); i++) {
		int d = m / divisors[i];
		if (d || p - s)
			*p++ = d + '0';
		m %= divisors[i];
	}
	*p++ = m + '0';
	int length = p - s;
	switch (length) {
	case 1:
		return true;
	case 2: case 3:
		return (s[0] == s[length - 1]) ? true : false;
	default:
		return (s[0] == s[3] && s[1] == s[2]) ? true : false;
	}
}

void print_clock(int m)
{
	char s[5 + 1];
	char* p = s;
	for (size_t i = 0; i < sizeof(divisors) / sizeof(divisors[0]); i++) {
		*p++ = m / divisors[i] + '0';
		m %= divisors[i];
		if (p - s == 2)
			*p++ = ':';
	}
	*p++ = m + '0';
	*p = '\0';
	cout << s << endl;
}

int main()
{
	for (int m = 0; m < clock_max; m++)
		palindromic_clocks[m] = is_palindromic(m);
	int na;
	cin >> na;
	while (na--) {
		int h, m;
		char c;
		cin >> h >> c >> m;
		for (m = h * minutes_max + m + 1; ; m++) {
			if (m == clock_max)
				m = 0;
			if (palindromic_clocks[m])
				break;
		}
		print_clock(m);
	}
	return 0;
}

