
/*
	UVa 392 - Polynomial Showdown

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_392_Polynomial_Showdown.cpp

	from ACM Mid Central Regionals 1996
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidCen/1996/index.html)
*/

#include <iostream>
#include <cstdlib>
using namespace std;

const int nr_coefficients = 9;

bool read_coefficients(int coefficients[])
{
	for (int i = 0; i < nr_coefficients; i++)
		if (!(cin >> coefficients[i]))
			return false;
	return true;
}

int main()
{
	while (true) {
		int coefficients[nr_coefficients];
		if (!read_coefficients(coefficients))
			break;
		bool exponent_coefficient = false;
		for (int i = 0; i < nr_coefficients; i++) {
			int c = coefficients[i];
			if (c) {
				if (c < 0)
					cout << ((exponent_coefficient) ? " - " : "-");
				else if (i && exponent_coefficient)
					cout << " + ";
				if (i < nr_coefficients - 1 && abs(c) > 1 || i == nr_coefficients - 1)
					cout << abs(c);
				if (i < nr_coefficients - 1) {
					exponent_coefficient = true;
					if (i < nr_coefficients - 2)
						cout << "x^" << nr_coefficients - i - 1;
					else
						cout << 'x';
				}
			}
			else if (i == nr_coefficients - 1 && !exponent_coefficient)
				cout << c;
		}
		cout << endl;
	}
	return 0;
}

