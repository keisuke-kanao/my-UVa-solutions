
/*
	UVa 11616 - Roman Numerals

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11616_Roman_Numerals.cpp
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

const int nr_letters = 26;
const int numeral_values[nr_letters] = {0, 0, 100, 500, 0, 0, 0, 0, 1, 0, 0, 50, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 10, 0, 0};

int parse_roman_numeral(const char* s, int length)
{
	int r = 0, p = -1;
	do {
		int c = numeral_values[*s++ - 'A'];
		if (p != -1 && p < c)
			r -= p * 2;
		r += c;
		p = c;
	} while (--length);
	return r;
}

string parse_numbers(int n)
{
	int d;
	string s;
	for ( ; n >= 1000; n -= 1000)
		s += 'M';
	if (n >= 100) {
		d = n / 100;
		if (d == 9)
			s += "CM";
		else if (d >= 5) {
			s += 'D';
			for (d -= 5; d; d--)
				s += 'C';
		}
		else if (d == 4)
			s += "CD";
		else {
			for ( ; d; d--)
				s += 'C';
		}
		n %= 100;
	}
	if (n >= 10) {
		d = n / 10;
		if (d == 9)
			s += "XC";
		else if (d >= 5) {
			s += 'L';
			for (d -= 5; d; d--)
				s += 'X';
		}
		else if (d == 4)
			s += "XL";
		else {
			for ( ; d; d--)
				s += 'X';
		}
		n %= 10;
	}
	if (n == 9)
		s += "IX";
	else if (n >= 5) {
		s += 'V';
		for (n -= 5; n; n--)
			s += 'I';
	}
	else if (n == 4)
		s += "IV";
	else {
		for ( ; n; n--)
			s += 'I';
	}
	return s;
}

int main()
{
	string s;
	while (cin >> s) {
		const char* p = s.c_str();
		if (isdigit(*p))
			cout << parse_numbers(atoi(p)) << endl;
		else
			cout << parse_roman_numeral(p, s.length()) << endl;
	}
	return 0;
}

