
/*
	UVa 10057 - A mid-summer night's dream

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10057_A_mid-summer_nights_dream.cpp
*/

#include <iostream>
#include <cstring>
using namespace std;

const int nr_max = 65536;
int counters[nr_max]; // counters[i] is the number of occurrences of i

int main()
{
	int n;
	while (cin >> n) {
		memset(counters, 0, sizeof(counters));
		int i;
		for (i = 0; i < n; i++) {
			int j;
			cin >> j;
			counters[j]++;
		}
		int median = 0, another_median = -1;
		if (n & 1) { // n is odd
			for (i = 0; ; median++) { // scan a median
				i += counters[median]; // accumulate the number of occurrences
				if (i > n / 2)
					break;
			}
		}
		else {
			for (i = 0; ; median++) {
				i += counters[median];
				if (i >= n / 2)
					break;
			}
			if (i < n / 2 + 1) {
				for (another_median = median + 1; ; another_median++)
					if (counters[another_median])
						break;
			}
		}
		if (another_median == -1) // median is unique
			cout << median << ' ' << counters[median] << ' ' << 1 << endl;
		else
			cout << median << ' ' << counters[median] + counters[another_median] << ' ' <<
				another_median - median + 1 << endl;
	}
	return 0;
}

