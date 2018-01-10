
/*
	UVa 10125 - Sumsets

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10125_Sumsets.cpp
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

bool find_partial_sum(int i, int j, const vector<int>& numbers, const multimap<int, pair<int, int> >& sums)
{
	pair<multimap<int, pair<int, int> >::const_iterator, multimap<int, pair<int, int> >::const_iterator> result =
		sums.equal_range(numbers[i] - numbers[j]);
	for (multimap<int, pair<int, int> >::const_iterator ri = result.first; ri != result.second; ++ri) {
		const pair<int, int>& pn = ri->second;
		if (pn.first != i && pn.second != i && pn.first != j && pn.second != j)
			return true;
	}
	return false;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		vector<int> numbers(n);
		for (int i = 0; i < n; i++)
			cin >> numbers[i];
		multimap<int, pair<int, int> > sums;
			// for each pair of numbers a, b, key is (a + b) and its value is their indices for the vector of numbers
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				sums.insert(make_pair(numbers[i] + numbers[j], make_pair(i, j)));
		int max_sum = numeric_limits<int>::min();
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++) {
				// for each pair of c, d, find any pair of numbers whose sum is (d - c)
				if (find_partial_sum(i, j, numbers, sums))
					max_sum = max(max_sum, numbers[i]);
				if (find_partial_sum(j, i, numbers, sums))
					max_sum = max(max_sum, numbers[j]);
			}
		if (max_sum != numeric_limits<int>::min())
			cout << max_sum << endl;
		else
			cout << "no solution\n";
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

