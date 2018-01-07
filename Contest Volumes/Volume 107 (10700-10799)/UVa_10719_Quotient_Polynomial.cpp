
/*
	UVa 10719 - Quotient Polynomial

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10719_Quotient_Polynomial.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int n_max = 10000;
int a[n_max + 1];

int main()
{
	string line;
	istringstream iss;
	while (getline(cin, line)) {
		iss.str(line);
		int k;
		iss >> k;
		iss.clear();
		getline(cin, line);
		iss.str(line);
		int n = 0;
		while (iss >> a[n])
			n++;
		iss.clear();
		if (n == 1) {
			cout << "q(x):\nr = " << a[0] << endl << endl;
		}
		else {
			int b = a[0];
			cout << "q(x): " << b;
			for (int i = 1; i < n - 1; i++) {
				b = a[i] + k * b;
				cout << ' ' << b;
			}
			cout << endl;
			cout << "r = " << a[n - 1] + k * b << endl << endl;
		}
	}
	return 0;
}

