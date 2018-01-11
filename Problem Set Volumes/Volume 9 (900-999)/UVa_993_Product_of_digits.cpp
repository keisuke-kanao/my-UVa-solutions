
/*
	UVa 993 - Product of digits

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_993_Product_of_digits.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool get_digits(int n, vector<char>& digits)
{
	int d = 9;
	while (d > 1) {
		if (!(n % d)) {
			digits.push_back('0' + d);
			n /= d;
		}
		else
			d--;
	}
	return (n == 1) ? true : false;
}

int main()
{
	int s;
	cin >> s;
	while (s--) {
		int n;
		cin >> n;
		if (!n)
			cout << 10 << endl;
		else if (n == 1)
			cout << 1 << endl;
		else {
			vector<char> digits;
			if (get_digits(n, digits)) {
				sort(digits.begin(), digits.end());
				for (vector<char>::const_iterator i = digits.begin(), e = digits.end(); i != e; ++i)
					cout << *i;
				cout << endl;
			}
			else
				cout << -1 << endl;
		}
	}
	return 0;
}

