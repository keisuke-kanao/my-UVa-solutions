
/*
	UVa 12602 - Nice Licence Plates

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12602_Nice_Licence_Plates.cpp
*/

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int get_first_part(const char* s)
{
	int n = 0;
	for (const char* p = s; *p != '-'; p++) {
		if (p > s)
			n *= 26;
		n += *p - 'A';
	}
	return n;
}

int get_second_part(const char* s)
{
	int n = 0;
	for (const char* p = s; *p; p++) {
		if (p > s)
			n *= 10;
		n += *p - '0';
	}
	return n;
}

int main()
{
	int n;
	cin >> n;
	while (n--) {
		string s;
		cin >> s;
		cout << ((abs(get_first_part(s.c_str()) - get_second_part(s.c_str() + 4)) <= 100) ? "nice\n" : "not nice\n");
	}
	return 0;
}

