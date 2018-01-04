
/*
	UVa 12247 - Jollo

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12247_Jollo.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int nr_cards = 52, nr_rounds = 3;

int main()
{
	while (true) {
		vector<int> princess(nr_rounds), prince(nr_rounds - 1);
		cin >> princess[0] >> princess[1] >> princess[2] >> prince[0] >> prince[1];
		if (!princess[0])
			break;
		sort(princess.begin(), princess.end()); // sort in ascending order
		if (prince[0] < prince[1])
			swap(prince[0], prince[1]); // sort in descending order
		vector<bool> discards(nr_cards + 1, false);

		// first round
		// Prince loses with the pair of cards whose has the minimum positive difference.
		int min_diff = nr_cards, min_i, min_j;
		for (int i = 0; i < nr_rounds; i++)
			for (int j = 0; j < nr_rounds - 1; j++) {
				int diff = princess[i] - prince[j];
				if (diff > 0 && diff < min_diff) {
					min_diff = diff;
					min_i = i; min_j = j;
				}
			}
		if (min_diff == nr_cards) { // Prince will win two rounds with the current set of cards
			for (int i = 0; i < nr_rounds; i++)
				discards[princess[i]] = true;
			for (int i = 0; i < nr_rounds - 1; i++)
				discards[prince[i]] = true;
			for (int i = 1; i <= nr_cards; i++)
				if (!discards[i]) {
					cout << i << endl;
					break;
				}
			continue;
		}
#ifdef DEBUG
		cout << princess[min_i] << ' ' << prince[min_j] << endl;
#endif
		discards[princess[min_i]] = discards[prince[min_j]] = true;
		princess.erase(princess.begin() + min_i); prince.erase(prince.begin() + min_j);

		// 2nd round
		// Prince wins with the pair of remainig cards whos has the maximum negative difference.
		min_diff = 0;
		for (int i = 0; i < nr_rounds - 1; i++) {
			int diff = princess[i] - prince[0];
			if (diff > 0) {
				min_diff = 0; break;
			}
			else if (diff < min_diff) {
				min_diff = diff;
				min_i = i;
			}
		}
		if (!min_diff) { // Prince will lose two rounds with the current set of cards
			cout << -1 << endl;
			continue;
		}

#ifdef DEBUG
		cout << princess[min_i] << ' ' << prince[0] << endl;
#endif
		discards[princess[min_i]] = discards[prince[0]] = true;
		princess.erase(princess.begin() + min_i);

		// 3rd round
		// Prince wins with a card that is greater than the Princess's remaing card, excluding the ones that have already been discarded.
		int p = princess[0] + 1;
		for ( ; p <= nr_cards; p++)
			if (!discards[p])
				break;
		cout << ((p <= nr_cards) ? p : -1) << endl;
	}
	return 0;
}

