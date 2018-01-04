
/*
	UVa 498 - Polly the Polynomial

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_498_Polly_the_Polynomial.cpp
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	string line;
	istringstream iss;
	while (getline(cin, line)) {
		vector<long long> coefficients;
		iss.str(line);
		long long c;
		while (iss >> c)
			coefficients.push_back(c);
		iss.clear();
		int n = coefficients.size();
		getline(cin, line);
		iss.str(line);
		long long x;
		bool printed = false;
		while (iss >> x) {
			long long s = coefficients[0];
			for (int i = 1; i < n; i++) {
				s *= x;
				s += coefficients[i];
			}
			if (printed)
				cout << ' ';
			else
				printed = true;
			cout << s;
		}
		cout << endl;
		iss.clear();
	}
	return 0;
}

