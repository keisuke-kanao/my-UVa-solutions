
/*
	UVa 1149 - Bin Packing

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_1149_Bin_Packing.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 100000;
int items[n_max];

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		int n, l;
		scanf("%d", &n);
		scanf("%d", &l);
		for (int i = 0; i < n; i++)
			scanf("%d", &items[i]);
		sort(items, items + n);
		int nr_bins = 0;
		for (int i = 0, j = n - 1; i <= j; j--, nr_bins++)
			if (i < j && items[i] + items[j] <= l)
				i++;
		printf("%d\n", nr_bins);
		if (nr_cases)
			putchar('\n');
	}
	return 0;
}

