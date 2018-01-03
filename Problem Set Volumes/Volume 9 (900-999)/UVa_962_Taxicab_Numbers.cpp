
/*
	UVa 962 - Taxicab Numbers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_962_Taxicab_Numbers.cpp
*/

#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
	const int nr_cubes_max = 1000;
	const int n1_max = 1000000000, rg_max = 100000;
	vector<int> cubes(nr_cubes_max);
	for (int i = 1; i <= nr_cubes_max; i++)
		cubes[i - 1] = i * i * i;
	map<int, int> sums_of_cubes;
	for (int i = 0; i < nr_cubes_max; i++)
		for (int j = i; j < nr_cubes_max; j++) {
			int s = cubes[i] + cubes[j];
			if (s <= n1_max + rg_max) {
				pair<map<int, int>::iterator, bool> result = sums_of_cubes.insert(make_pair(s, 1));
				if (!result.second)
					result.first->second++;
			}
		}
	vector<int> taxicab_numbers;
	for (map<int, int>::const_iterator si = sums_of_cubes.begin(), se = sums_of_cubes.end(); si != se; ++si)
		if (si->second >= 2)
			taxicab_numbers.push_back(si->first);
#ifdef DEBUG
	printf("%d %d\n", taxicab_numbers.size(), taxicab_numbers[taxicab_numbers.size() - 1]);
#endif
	int n1, rg;
	while (scanf("%d %d", &n1, &rg) != EOF) {
		vector<int>::iterator li = lower_bound(taxicab_numbers.begin(), taxicab_numbers.end(), n1),
			ui = upper_bound(taxicab_numbers.begin(), taxicab_numbers.end(), n1 + rg);
		if (li == ui)
			puts("None");
		else {
			for (; ui != li; ++li)
				printf("%d\n", *li);
		}
	}
	return 0;
}

