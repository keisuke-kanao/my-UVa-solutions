
/*
	UVa 10101 - Bangla Numbers

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10101_Bangla_Numbers.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

int print_bangla_number(const char* s, int length)
{
	bool printed = false;
	if (length > 7) {
		if (print_bangla_number(s, length - 7)) {
			printed = true;
			cout << " kuti";
		}
	}
	int n = 0;
	for (int i = (length > 7) ? length - 7 : 0; i < length; i++) {
		n *= 10;
		n += s[i] - '0';
	}
	if (n >= 100000) {
		if (printed)
			cout << ' ';
		else
			printed = true;
		cout << n / 100000 << " lakh";
		n %= 100000;
	}
	if (n >= 1000) {
		if (printed)
			cout << ' ';
		else
			printed = true;
		cout << n / 1000 << " hajar";
		n %= 1000;
	}
	if (n >= 100) {
		if (printed)
			cout << ' ';
		else
			printed = true;
		cout << n / 100 << " shata";
		n %= 100;
	}
	if (n) {
		if (printed)
			cout << ' ';
		else
			printed = true;
		cout << n;
	}
	return printed;
}

int main()
{
	string s;
	for (int case_nr = 1; cin >> s; case_nr++) {
		cout << setfill(' ') << setw(4) << case_nr << ". ";
		istringstream iss(s);
		long long n;
		iss >> n;
		if (!n)
			cout << 0;
		else {
			ostringstream oss;
			oss << n;
			string sn = oss.str();
			print_bangla_number(sn.c_str(), sn.length());
		}
		cout << endl;
	}
	return 0;
}

/*

Sample Input

1

3 1 1 1 1 1 1
a = 4
print a
lock
b = 9
print b
unlock
print b
end
a = 3
print a
lock
b = 8
print b
unlock
print b
end
b = 5
a = 17
print a
print b
lock
b = 21
print b
unlock
print b
end

Sample Output

1: 3
2: 3
3: 17
3: 9

*/
