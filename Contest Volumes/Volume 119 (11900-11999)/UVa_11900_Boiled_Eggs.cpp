
/*
	UVa 11900 - Boiled Eggs

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11900_Boiled_Eggs.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		int n, p, q;
		cin >> n >> p >> q;
		int nr_eggs = 0, sum_of_weights = 0;
		for (int i = 1; i <= n; i++) {
			int weight;
			cin >> weight;
			sum_of_weights += weight;
			if (i <= p && sum_of_weights <= q)
				nr_eggs++;
		}
		cout << "Case " << case_nr << ": " << nr_eggs << endl;
	}
	return 0;
}

