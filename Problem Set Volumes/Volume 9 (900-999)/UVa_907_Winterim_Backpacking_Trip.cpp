
/*
	UVa 907 - Winterim Backpacking Trip

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_907_Winterim_Backpacking_Trip.cpp

	Another accepted solution.
*/

#include <algorithm>
#include <limits>
#include <cstdio>
using namespace std;

const int n_max = 601;
int distances[n_max + 1];

bool check_distance(int n, int k, int distance)
{
// see if the campsites can be partitioned by the number of sites that is equal to or less than k
	int d = distance, nr_sites = 0;
	for (int i = 1; i <= n; i++) {
		if (d >= distances[i])
			d -= distances[i];
		else {
			d = distance - distances[i];
			if (d < 0)
				return false;
			if (++nr_sites > k)
				return false;
		}
	}
	return true;
}
 
int main()
{
	int n, k;
	while (scanf("%d %d", &n, &k) != EOF) {
		n++;
		int s = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &distances[i]);
			s += distances[i];
		}
		int left = 0, right = s, min_distance = numeric_limits<int>::max();
		while (left <= right) {
			int mid = (left + right) / 2;
			if (check_distance(n, k, mid)) {
				min_distance = min(min_distance, mid);
				right = mid - 1;
			}
			else
				left = mid + 1;
		}
		printf("%d\n", min_distance);
	}
    return 0;
}

