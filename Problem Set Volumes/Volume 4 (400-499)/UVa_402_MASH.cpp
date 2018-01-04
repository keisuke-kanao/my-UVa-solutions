
/*
	UVa 402 - M*A*S*H

	To build using Visucal Studio 2008:
		cl -EHsc UVa_402_MASH.cpp

	from ACM South Central Regionals 1995
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_SouthCen/1995/index.html)

	Note that the judges' solution (mash.c) is WRONG.
*/

#include <iostream>
using namespace std;

int main()
{
	const int n_max = 50, nr_cards = 20;
	bool positions[n_max];
	int cards[nr_cards];
	int n, x;
	for (int selection_nr = 1; cin >> n; selection_nr++) {
		cin >> x;
		for (int i = 0; i < nr_cards; i++)
			cin >> cards[i];
		for (int i = 0; i < n; i++)
			positions[i] = true;
		for (int i = 0, n_left = n; i < nr_cards && n_left > x; i++)
			for (int j = 0, k = 0; j < n && n_left > x; j++) {
				if (positions[j]) {
					if (++k == cards[i]) {
						n_left--;
						k = 0;
						positions[j] = false;
					}
				}
			}
		cout << "Selection #" << selection_nr << endl;
		bool printed = false;
		for (int i = 0; i < n; i++)
			if (positions[i]) {
				if (printed)
					cout << ' ';
				else
					printed = true;
				cout << i + 1;
			}
		cout << endl << endl;
	}
	return 0;
}

