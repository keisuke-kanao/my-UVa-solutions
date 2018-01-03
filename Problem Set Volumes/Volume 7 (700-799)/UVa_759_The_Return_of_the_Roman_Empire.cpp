
/*
	UVa 759 - The Return of the Roman Empire

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_759_The_Return_of_the_Roman_Empire.cpp
*/

#include <iostream>
#include <string>
using namespace std;

int roman_numeral(const char* s)
{
	int n = 0;
	while (*s) {
		const char* ns = s + 1;
		int d = 0;
		switch (*s) {
		case 'I':
			if (n % 10)
				return -1;
			if (*ns && (*ns == 'V' || *ns == 'X')) {
				d = (*ns == 'V') ? 4 : 9;
				ns++;
			}
			else {
				d++;
				while (*ns && *ns == 'I') {
					if (++ns - s > 3)
						return -1;
					d++;
				}
			}
			break;
		case 'V':
			if (n % 10)
				return -1;
			d = 5;
			while (*ns && *ns == 'I') {
				if (++ns - s > 4)
					return -1;
				d++;
			}
			break;
		case 'X':
			if ((n % 100) / 10 || n % 10)
				return -1;
			if (*ns && (*ns == 'L' || *ns == 'C')) {
				d = (*ns == 'L') ? 40 : 90;
				ns++;
			}
			else {
				d = 10;
				while (*ns && *ns == 'X') {
					if (++ns - s > 3)
						return -1;
					d += 10;
				}
			}
			break;
		case 'L':
			if ((n % 100) / 10 || n % 10)
				return -1;
			d = 50;
			while (*ns && *ns == 'X') {
				if (++ns - s > 4)
					return -1;
				d += 10;
			}
			break;
		case 'C':
			if ((n % 1000) / 100 || n % 100)
				return -1;
			if (*ns && (*ns == 'D' || *ns == 'M')) {
				d = (*ns == 'D') ? 400 : 900;
				ns++;
			}
			else {
				d = 100;
				while (*ns && *ns == 'C') {
					if (++ns - s > 3)
						return -1;
					d += 100;
				}
			}
			break;
		case 'D':
			if ((n % 1000) / 100 || n % 100)
				return -1;
			d = 500;
			while (*ns && *ns == 'C') {
				if (++ns - s > 4)
					return -1;
				d += 100;
			}
			break;
		case 'M':
			if (n / 1000 || n % 1000)
				return -1;
			d = 1000;
			while (*ns && *ns == 'M') {
				if (++ns - s > 3)
					return -1;
				d += 1000;
			}
			break;
		default:
			return -1;
		}
		n += d;
		s = ns;
	}
	return n;
}

int main()
{
	string s;
	while (getline(cin, s)) {
		int n = roman_numeral(s.c_str());
		if (n >= 0)
			cout << n << endl;
		else
			cout << "This is not a valid number\n";
	}
	return 0;
}

