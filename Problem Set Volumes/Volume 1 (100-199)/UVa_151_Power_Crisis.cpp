
/*
	UVa 151 - Power Crisis

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_151_Power_Crisis.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

const int max_areas = 100;

int get_random_number(int n)
{
	for (int m = 1; ; m++) {
		int nr_turned_offs = 0;
		vector<bool> turned_offs(n + 1, false);
		int i = 1;
		while (true) {
#ifdef DEBUG
			cout << i << ' ';
#endif
			turned_offs[i] = true;
			if (++nr_turned_offs == n) {
#ifdef DEBUG
				cout << endl;
#endif
				if (i == 13)
					return m;
				else
					break;
			}
			int j = m;
			while (true) {
				if (++i > n)
					i = 1;
				if (!turned_offs[i] && !--j)
					break;
			}
		}
	}
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		cout << get_random_number(n) << endl;
	}
	return 0;
}

