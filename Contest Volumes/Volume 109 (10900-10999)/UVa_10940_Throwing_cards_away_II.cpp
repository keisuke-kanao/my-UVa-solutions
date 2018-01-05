
/*
	UVa 10940 - Throwing cards away II

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10940_Throwing_cards_away_II.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	const double log_2 = log10(2.0);
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		double p = ceil(log10(static_cast<double>(n)) / log_2);
		int power_of_2 = static_cast<int>(pow(2.0, p));
		int last_card = power_of_2 + (n - power_of_2) * 2;
		cout << last_card << endl;
	}
	return 0;
}

