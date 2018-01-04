
/*
	UVa 11413 - Fill the Containers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11413_Fill_the_Containers.cpp
*/

#include <cstdio>
#include <algorithm>
#include <iterator>
using namespace std;

const int n_max = 1000, capacity_max = 1000000;
int capacities[n_max];

int fill_containers(int n, int m, int max_c)
{
	int nc = 1, s = 0;
	for (int i = 0; i < n; i++) {
		if (capacities[i] > max_c)
			return 1;
		else if (s + capacities[i] > max_c) {
			if (++nc > m)
				return 1;
			s = capacities[i];
		}
		else
			s += capacities[i];
	}
	return (nc < m) ? -1 : 0;
}

int main()
{
	int n, m;
	while (scanf("%d %d", &n, &m) != EOF) {
		int low = capacity_max + 1, high = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &capacities[i]);
			low = min(low, capacities[i]);
			high += capacities[i];
		}
		int mid;
		while (low < high) {
			mid = (low + high) / 2;
			int result = fill_containers(n, m, mid);
#ifdef DEBUG
			printf("%d %d %d: %d\n", low, mid, high, result);
#endif
			if (result > 0)
				low = mid + 1;
			else
				high = mid;
/*
			else if (result < 0)
				high = mid - 1;
			else
				break;
*/
		}
		printf("%d\n", high);
	}
	return 0;
}

