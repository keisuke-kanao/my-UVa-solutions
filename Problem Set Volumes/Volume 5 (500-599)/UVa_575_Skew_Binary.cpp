
/*
	UVa 575 - Skew Binary

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_575_Skew_Binary.cpp
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s;
	while (cin >> s) {
		if (s == "0")
			break;
		int length = s.length();
		const char* p = s.c_str() + length - 1;
		int power_of_2 = 2, n = 0;
		while (length--) {
			n += (*p-- - '0') * (power_of_2 - 1);
			power_of_2 <<= 1;
		}
		cout << n << endl;
	}
	return 0;
}

