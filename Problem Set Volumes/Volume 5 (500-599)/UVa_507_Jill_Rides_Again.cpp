
/*
	UVa 507 - Jill Rides Again

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_507_Jill_Rides_Again.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int b;
	cin >> b;
	for (int r = 1; r <= b; r++) {
		int s;
		cin >> s;
		int max = -1, sum = 0;
		int p = 1, q = 1, start = 1, stop = 1;
		for (int i = 1; i < s; i++) {
			int n;
			cin >> n;
			sum += n;
			if (sum >= 0) {
				q = i + 1;
				if (sum > max || sum == max && q - p > stop - start) {
					max = sum;
					start = p; stop = q;
				}
			}
			else {
				sum = 0;
				p = q = i + 1;
			}
		}
		if (max != -1)
			cout << "The nicest part of route " << r << " is between stops " << start << " and " << stop << endl;
		else
			cout << "Route " << r <<" has no nice parts\n";
	}
	return 0;
}

