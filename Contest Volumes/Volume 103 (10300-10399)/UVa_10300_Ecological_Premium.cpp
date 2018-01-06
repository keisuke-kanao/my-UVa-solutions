
/*
	UVa 10300 - Ecological Premium

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10300_Ecological_Premium.cpp
*/

#include <iostream>
using namespace std;

int main(int /* argc */, char** /* argv */)
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		int nr_farmers;
		cin >> nr_farmers;
		long long budget = 0;
		for (int i = 0; i < nr_farmers; i++) {
			int fm /* size of the farmyard in square meters */, an /* number of animals */, ef /* environment-friendliness */;
			cin >> fm >> an >> ef;
			budget += static_cast<long long>(fm) * ef; // ((fm / an) * ef) * an
		}
		cout << budget << endl;
	}
	return 0;
}

