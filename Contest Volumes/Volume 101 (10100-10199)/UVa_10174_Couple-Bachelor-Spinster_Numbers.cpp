
/*
	UVa 10174 - Couple-Bachelor-Spinster Numbers.

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10174_Couple-Bachelor-Spinster_Numbers.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

/*
(n + 1)^2 - n^2 = 2 * n + 1.
Therefore, the difference of two consecutive squares is an odd number.
(n + 2)^2 - n^2 = 4 * (n + 1).
Therefore, a multiple of 4 can be represented by (n + 2)^2 - n^2.

*/

bool get_square_couple_numbers(long long n, int& a, int& b)
{
	if (!n) {
		a = b = 0;
		return true;
	}
	bool negative = false;
	if (n < 0) {
		negative = true;
		n = -n;
	}
	if (n % 2) {
		b = static_cast<int>(n / 2); a = b + 1;
		if (negative)
			swap(a, b);
		return true;
	}
	else {
		if (n % 4)
			return false;
		else {
			n /= 4;
			a = static_cast<int>(n) + 1; b = static_cast<int>(n) - 1;
			if (negative)
				swap(a, b);
			return true;
		}
	}
}

int main()
{
	string s;
	while (getline(cin, s)) {
		istringstream iss(s);
		int n1, n2;
		iss >> n1;
		if (iss >> n2) {
			if (n1 % 2)
				n1++;
			int nr = 0;
			for (int n = n1; n <= n2; n += 2) {
				int a, b;
				if (!get_square_couple_numbers(n, a, b))
					nr++;
			}
			cout << nr << endl;
		}
		else {
			int a, b;
			if (get_square_couple_numbers(n1, a, b))
				cout << a << ' ' << b << endl;
			else if (n1 % 2)
				cout << "Spinster Number.\n";
			else
				cout << "Bachelor Number.\n";
		}
		iss.clear();
	}
	return 0;
}

/*

bool get_square_couple_numbers(long long n, long long& a, long long& b) // first version
{
	bool negative = false;
	if (n < 0) {
		negative = true;
		n = -n;
	}
	long long l = static_cast<long long>(ceil(sqrt(static_cast<double>(n)))), h;
	for (h = l + 1; ; h++) {
		if ((h + 1) * (h + 1) - h * h > n)
			break;
	}
	for (a = h; a >= l; a--)
		for (b = a - 1; b >= 0; b--) {
			long long d = a * a - b * b;
			if (d == n) {
				if (negative)
					swap(a, b);
				return true;
			}
			else if (d > n)
				break;
		}
	return false;
}

long long square_couple(long long a, long long b)
{
	return a * a - b * b;
}

bool get_square_couple_numbers(long long n, long long& a, long long& b) // second version
{
	bool negative = false;
	if (n < 0) {
		negative = true;
		n = -n;
	}
	long long l = static_cast<long long>(ceil(sqrt(static_cast<double>(n))));
	for (a = l; square_couple(a, a - 1) <= n; a++) {
		for (b = a - 1; b >= 0; b--) {
			long long sc = square_couple(a, b);
			if (sc == n) {
				if (negative)
					swap(a, b);
				return true;
			}
			else if (sc > n)
				break;
		}
	}
	return false;
}

bool get_square_couple_numbers(long long n, long long& a, long long& b) // third version
{
	if (!n) {
		a = b = 0;
		return true;
	}
	bool negative = false;
	if (n < 0) {
		negative = true;
		n = -n;
	}
	for (long long i = 1, e = static_cast<long long>(sqrt(static_cast<double>(n))); i <= e; i++)
		if (!(n % i)) {
			long long j = n / i;
			a = j + i; b = j - i;
			if (!(a % 2) && !(b % 2)) {
				a /= 2; b /= 2;
				if (negative)
					swap(a, b);
				return true;
			}
		}
	return false;
}


*/

