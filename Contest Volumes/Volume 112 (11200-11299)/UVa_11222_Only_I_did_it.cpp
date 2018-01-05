
/*
	UVa 11222 - Only I did it!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11222_Only_I_did_it.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int s_max = 1000;
int first[s_max], second[s_max], third[s_max];
int first_only[s_max], second_only[s_max], third_only[s_max];

int main()
{
	int t;
	cin >> t;
	for (int cn = 1; cn <= t; cn++) {
		int sf, ss, st;
		cin >> sf;
		for (int i = 0; i < sf; i++)
			cin >> first[i];
		cin >> ss;
		for (int i = 0; i < ss; i++)
			cin >> second[i];
		cin >> st;
		for (int i = 0; i < st; i++)
			cin >> third[i];
		sort(first, first + sf);
		sort(second, second + ss);
		sort(third, third + st);
		int sf_only = 0, ss_only = 0, st_only = 0;
		for (int i = 0; i < sf; i++)
			if (!binary_search(second, second + ss, first[i]) &&
				!binary_search(third, third + st, first[i]))
				first_only[sf_only++] = first[i];
		for (int i = 0; i < ss; i++)
			if (!binary_search(first, first + sf, second[i]) &&
				!binary_search(third, third + st, second[i]))
				second_only[ss_only++] = second[i];
		for (int i = 0; i < st; i++)
			if (!binary_search(first, first + sf, third[i]) &&
				!binary_search(second, second + ss, third[i]))
				third_only[st_only++] = third[i];
		int max_only = max(max(sf_only, ss_only), st_only);
		cout << "Case #" << cn << ":\n";
		if (sf_only == max_only) {
			cout << 1 << ' ' << sf_only;
			for (int i = 0; i < sf_only; i++)
				cout << ' ' << first_only[i];
			cout << endl;
		}
		if (ss_only == max_only) {
			cout << 2 << ' ' << ss_only;
			for (int i = 0; i < ss_only; i++)
				cout << ' ' << second_only[i];
			cout << endl;
		}
		if (st_only == max_only) {
			cout << 3 << ' ' << st_only;
			for (int i = 0; i < st_only; i++)
				cout << ' ' << third_only[i];
			cout << endl;
		}
	}
	return 0;
}


