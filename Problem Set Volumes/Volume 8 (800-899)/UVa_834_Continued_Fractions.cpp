
/*
	UVa 834 - Continued Fractions

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_834_Continued_Fractions.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int numerator, denominator;
	while (cin >> numerator >> denominator) {
		cout << '[' << numerator / denominator;
		numerator %= denominator;
		if (numerator) {
			cout << ';';
			bool printed = false;
			while (numerator > 1) {
				if (printed)
					cout << ',';
				else
					printed = true;
				cout << denominator / numerator;
				int n = numerator;
				numerator = denominator % numerator;
				denominator = n;
			}
			if (numerator) {
				if (printed)
					cout << ',';
				cout << denominator;
			}
		}
		cout << "]\n";
	}
	return 0;
}

