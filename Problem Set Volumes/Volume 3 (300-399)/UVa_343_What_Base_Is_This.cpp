
/*
	UVa 343 - What Base Is This?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_343_What_Base_Is_This.cpp
*/

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
using namespace std;

const int base_min = 2, base_max = 36;

int get_min_base(const string& s)
{
	int base = base_min;
	for (const char* p = s.c_str(); *p; p++) {
		char c = *p;
		int d = (isdigit(c)) ? c - '0' : c - 'A' + 10;
		if (d >= base)
			base = d + 1;
	}
	return base;
}

long long convert_to_decimal_value(const string& s, int base)
{
	long long n = 0;
	for (const char* p = s.c_str(); *p; p++) {
		char c = *p;
		int d = (isdigit(c)) ? c - '0' : c - 'A' + 10;
		n *= base;
		n += d;
	}
	return n;
}

bool find_bases(const string& sx, const string& sy, int& base_x, int& base_y)
{
	int base_x_min = get_min_base(sx), base_y_min = get_min_base(sy);
	long long dys[base_max + 1];
	memset(dys, -1, sizeof(dys));
	for (base_x = base_x_min; base_x <= base_max; base_x++) {
		long long dx = convert_to_decimal_value(sx, base_x);
		for (base_y = base_y_min; base_y <= base_max; base_y++) {
			if (dys[base_y] == -1)
				dys[base_y] = convert_to_decimal_value(sy, base_y);
			if (dx == dys[base_y])
				return true;
		}
	}
	return false;
}

int main()
{
	string sx, sy;
	while (cin >> sx >> sy) {
		int base_x, base_y;
		if (find_bases(sx, sy, base_x, base_y))
			cout << sx << " (base " << base_x << ") = " << sy << " (base " << base_y << ")\n";
		else
			cout << sx << " is not equal to " << sy << " in any base 2..36\n";
	}
	return 0;
}

