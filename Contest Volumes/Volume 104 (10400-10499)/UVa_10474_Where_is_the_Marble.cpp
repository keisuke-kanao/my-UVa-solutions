
/*
	UVa 10474 - Where is the Marble?

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10474_Where_is_the_Marble.cpp

	running time on Uva Online Judge = 0.516 sec.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int main()
{
	const int number_max = 10000;
	vector<int> counts(number_max + 1);
		// counts[i] is the number of occurrence of i
	vector<int> accumulated_counts(number_max + 1);
		// accumulated_counts[i] is the accumulated counts up to i
	for (int c = 1; ; c++) {
		int n, q;
		cin >> n >> q;
		if (!n && !q)
			break;
		memset(&counts[0], 0, sizeof(int) * (number_max + 1));
		int n_min = number_max + 1, n_max = -1;
		for (int i = 0; i < n; i++) {
			int number;
			cin >> number;
			counts[number]++;
			n_min = min(n_min, number);
			n_max = max(n_max, number);
		}
		for (int i = n_min, ac = 1; i <= n_max; i++) {
			accumulated_counts[i] = ac;
			ac += counts[i];
		}
		cout << "CASE# " << c << ":\n";
		for (int i = 0; i < q; i++) {
			int number;
			cin >> number;
			if (counts[number])
				cout << number << " found at " << accumulated_counts[number] << endl;
			else
				cout << number << " not found\n";
		}
	}
	return 0;
}

