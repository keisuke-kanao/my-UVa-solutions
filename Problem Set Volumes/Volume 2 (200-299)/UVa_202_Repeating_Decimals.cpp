
/*
	UVa 202 - Repeating Decimals

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_202_Repeating_Decimals.cpp
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
	int numerator, denominator;
	while (cin >> numerator >> denominator) {
		int quotient = numerator / denominator;
		cout << numerator << '/' << denominator << " = " << quotient << '.';
		numerator -= quotient * denominator;
		map<int, size_t> remainders;
		vector<int> digits;
		remainders.insert(make_pair(numerator, digits.size()));
		size_t repeat;
		while (true) {
			if (numerator < denominator)
				numerator *= 10;
			int q = numerator / denominator;
			digits.push_back(q);
			numerator -= q * denominator;
			pair<map<int, size_t>::iterator, bool> result = remainders.insert(make_pair(numerator, digits.size()));
			if (!result.second) {
				repeat = result.first->second;
				break;
			}
		}
		size_t nr_repeat = digits.size() - repeat;
		const size_t max_nr_repeat = 50;
		size_t i = 0, j = min(digits.size(), repeat + max_nr_repeat);
		for ( ; i < j; i++) {
			if (i == repeat)
				cout << '(';
			cout << digits[i];
		}
		if (nr_repeat > max_nr_repeat)
			cout << "...";
		cout << ")\n";
		cout << "   " << nr_repeat << " = number of digits in repeating cycle\n\n";
	}
	return 0;
}

