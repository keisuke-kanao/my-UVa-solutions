
/*
	UVa 11205 - The broken pedometer

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11205_the_broken_pedometer.cpp

	This solution was accepted on 2015/12/26.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

bool are_symbols_distinguishable(int mask, int mask_max, int nr_symbols, const vector<int>& symbols)
{
	vector<bool> masked_symbols(mask_max, false);
	for (int i = 0; i < nr_symbols; i++) {
		int j = symbols[i] & mask;
		if (masked_symbols[j])
			return false;
		masked_symbols[j] = true;
	}
	return true;
}

int count_leds(int i, int nr_leds)
{
	int count = 0;
	for (int j = 0; j < nr_leds; j++, i >>= 1)
		if (i & 1)
			count++;
	return count;
}

int main()
{
	int nr_problems;
	cin >> nr_problems;
	while (nr_problems--) {
		int nr_leds, nr_symbols;
		cin >> nr_leds >> nr_symbols;
		vector<int> symbols(nr_symbols);
		for (int i = 0; i < nr_symbols; i++) {
			int s = 0;
			for (int j = 0; j < nr_leds; j++) {
				char c;
				cin >> c;
				s <<= 1;
				if (c == '1')
					s |= 1;
			}
			symbols[i] = s;
		}
		int nr = nr_leds;
		if (!nr_symbols)
			nr = 0;
		else if (nr_symbols == 1)
			nr = 0;
		else {
			int min_nr_leds = static_cast<int>(ceil(log10(static_cast<double>(nr_symbols)) / log10(2.0)));
				// min. number of LEDs to distinguish the symbols
			for (int i = 1, i_max = static_cast<int>(pow(2.0, static_cast<double>(nr_leds))); i < i_max; i++)
				if (are_symbols_distinguishable(~i, i_max, nr_symbols, symbols)) {
					nr = min(nr, nr_leds - count_leds(i, nr_leds));
					if (nr == min_nr_leds)
						break;
				}
		}
		cout << nr << endl;
	}
	return 0;
}

