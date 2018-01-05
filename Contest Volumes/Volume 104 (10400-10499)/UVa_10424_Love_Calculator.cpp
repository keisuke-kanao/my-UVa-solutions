
/*
	UVa 10424 - Love Calculator

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10424_Love_Calculator.cpp
*/

#include <iostream>
#include <string>
#include <cstdio>
#include <cctype>
using namespace std;

int love_calculator(const string& s)
{
	int n = 0;
	for (const char* p = s.c_str(); *p; p++)
		if (isalpha(*p))
			n += tolower(*p) - 'a' + 1;
	while (n >= 10) {
		int m = 0;
		for ( ; n; n /= 10)
			m += n % 10;
		n = m;
	}
	return n;
}

int main()
{
	string one, other;
	while (getline(cin, one) && getline(cin, other)) {
		double one_value = love_calculator(one), other_value = love_calculator(other);
		double ratio = 0.0;
		if (one_value != 0.0 || other_value != 0.0)
			ratio = (one_value < other_value) ?
				((one_value * 100.0) / other_value) : ((other_value * 100.0) / one_value);
		printf("%.2lf %%\n", ratio);
	}
	return 0;
}

